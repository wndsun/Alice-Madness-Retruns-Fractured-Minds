#include "Common.hpp"
#include "Features.hpp"
#include "Coop/CoopClient.hpp"

#include <atomic>
#include <cstring>

safetyhook::InlineHook Localize;

static uintptr_t Unattached_Collision_Skip = 0;
static uintptr_t FxActorLoopExit = 0;
static uintptr_t ParticleMaterialContinue = 0;
static uintptr_t ParticleMaterialSkip = 0;
static safetyhook::MidHook UnattachedCollisionGuard{};
static safetyhook::MidHook FxActorLoopGuard{};

__declspec(naked) static void ParticleMaterialDeadFlagStub()
{
	__asm
	{
		// UObject::ObjectFlags is at +0x08, RF_BeginDestroyed is bit 0x8000
		test dword ptr[ecx + 8], 8000h
		jnz dead_material

		// Re-run the five bytes replaced by the JMP
		mov edx, [esi + 4]
		mov eax, [ecx]
		jmp dword ptr[ParticleMaterialContinue]

		dead_material:
		// EDX is FLODInfo::Elements.ArrayData
		mov dword ptr[edx + ebx * 4], 0
		jmp dword ptr[ParticleMaterialSkip]
	}
}

static DWORD __cdecl Localize_Hook(DWORD* a1, void* a2, const wchar_t* a3, int a4, wchar_t* String1, int a6)
{
	const bool wantCannon = FixPinballCannonPrompt && a3 && _wcsicmp(a3, L"ACT_OWHH_CANNON_FIRE") == 0;
	const bool wantMatinee = SkipCutscenesWithEnter && a3 && _wcsicmp(a3, L"SKIP_CANCELMATINEE") == 0;
	const bool pcIcons = (wantCannon || wantMatinee) && QueryCalloutPlatform() == 1;

	if (a3 && _wcsicmp(a3, L"FlashUI_Chalkboard_Gryphon_2") == 0 && QueryCalloutPlatform() != 1)
	{
		a3 = L"FlashUI_Chalkboard_Gryphon_2_xbox";
	}

	// Fix a race condition
	static std::mutex locMutex;
	std::lock_guard<std::mutex> lock(locMutex);
	DWORD ret = Localize.unsafe_ccall<DWORD>(a1, a2, a3, a4, String1, a6);

	if (wantCannon && a1[0] && pcIcons)
	{
		std::wstring string(reinterpret_cast<const wchar_t*>(a1[0]));
		size_t pos = string.find(L"%MELEEICON%");

		if (pos != std::wstring::npos)
		{
			string.replace(pos, 11, L"%OBJECTIVEICON%");
			int n = (int)string.size() + 1;

			reinterpret_cast<void(__cdecl*)(void*, int)>(GetAddress(Addr::FStringFree))((void*)a1[0], 1); // free old
			a1[0] = a1[1] = a1[2] = 0;
			reinterpret_cast<void(__thiscall*)(DWORD*, int)>(GetAddress(Addr::FStringAlloc))(a1, n); // alloc
			memcpy((void*)a1[0], string.c_str(), n * sizeof(wchar_t));
			a1[1] = n;
		}
	}
	if (wantMatinee && a1[0] && pcIcons)
	{
		std::wstring string(reinterpret_cast<const wchar_t*>(a1[0]));
		size_t pos = string.find(L"%OBJECTIVEICON%");

		if (pos != std::wstring::npos)
		{
			string.replace(pos, 15, L"%CLICKLSICON%");
			int n = (int)string.size() + 1;
			memcpy((void*)a1[0], string.c_str(), n * sizeof(wchar_t));
			a1[1] = n;
		}
	}

	return ret;
}

// kynapseguard1 (13.11 17:07:23 and 20:02:56, both games, ~1 s into the
// boat chapter (Chapter2_W2_P) chosen after the giant section): Kynapse's
// per-frame update (Steam FUN_00d179f0 -> FUN_00d27b80 -> a virtual ->
// FUN_00d33940) adds an object whose "dirty" flag is set to its world's
// database - and that world is gone: FUN_00d33940 was called with
// this = 0x0000000C (a null world + 0xC) and read +4 of it. It is a
// __thiscall (database, item, bool) that returns 0 when the item could not
// be added; with no database there is nothing to add to, so that is what
// it returns now. The function is found by its prologue (PUSH -1; PUSH its
// own SEH handler) in the two builds seen.
static safetyhook::InlineHook KynapseDatabaseAdd{};
static std::atomic<int> KynapseGuardHits{ 0 };

static int __fastcall KynapseDatabaseAdd_Hook(void* self, void* /*edx*/, int item, int flag)
{
	if (reinterpret_cast<uintptr_t>(self) < 0x10000)
	{
		const int hits = ++KynapseGuardHits;
		if (hits <= 5)
		{
			char text[200];
			sprintf_s(text, "KYNAPSEGUARD an AI object was added to a world that is gone"
				" (database %p, item 0x%08X): skipped, not a crash (kynapseguard1, #%d).",
				self, static_cast<unsigned>(item), hits);
			AliceCoop::LogFromFix(text);
		}
		return 0;
	}
	return KynapseDatabaseAdd.unsafe_thiscall<int>(self, item, flag);
}

static void ApplyKynapseGuard()
{
	const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
	struct Candidate { uintptr_t address; uint32_t handler; };
	// the exe's own addresses (image base 0x400000) and the SEH handler
	// each pushes: Steam (current) and EA
	const Candidate candidates[] = {
		{ 0x00D33940, 0x0105F866 },
		{ 0x00DA7070, 0x010D4916 },
	};
	for (const Candidate& c : candidates)
	{
		const uintptr_t address = base + (c.address - 0x400000);
		uint8_t expected[7] = { 0x6A, 0xFF, 0x68, 0, 0, 0, 0 };
		const uint32_t handler = static_cast<uint32_t>(base + (c.handler - 0x400000));
		std::memcpy(expected + 3, &handler, 4);
		if (!MemoryHelper::IsReadable(reinterpret_cast<const void*>(address), sizeof(expected))
			|| std::memcmp(reinterpret_cast<const void*>(address), expected, sizeof(expected)) != 0)
		{
			continue;
		}
		KynapseDatabaseAdd = HookHelper::CreateHook(reinterpret_cast<void*>(address), &KynapseDatabaseAdd_Hook);
		char text[160];
		sprintf_s(text, "KYNAPSEGUARD installed at exe+0x%X (kynapseguard1).",
			static_cast<unsigned>(address - base));
		AliceCoop::LogFromFix(text);
		return;
	}
	AliceCoop::LogFromFix("KYNAPSEGUARD not installed: the function was not found in this build (kynapseguard1).");
}

static void OnUnattachedCollision(safetyhook::Context& ctx)
{
	*reinterpret_cast<uint32_t*>(ctx.esi + 0x3C) |= 0x80;
	ctx.eax = 0;
	ctx.eip = Unattached_Collision_Skip;
}

static void OnFxActorLoop(safetyhook::Context& ctx)
{
	if (!MemoryHelper::IsReadable(reinterpret_cast<const void*>(ctx.eax), 4))
	{
		ctx.eip = FxActorLoopExit;
	}
}

void ApplyCrashFixes()
{
	ApplyKynapseGuard(); // kynapseguard1: on even without the other crash fixes
	if (!CrashFixes) return;

	// Hash-table race condition (Localize)
	Localize = HookHelper::CreateHook((void*)GetAddress(Addr::Localize), &Localize_Hook);

	// Fix infinite loading screen
	MemoryHelper::MakeNOP(GetAddress(Addr::HashLoop), 2);

	// Unattached-collision panic
	DWORD addr_FixUnattachedCollisionPanic = GetAddress(Addr::FixUnattachedCollisionPanic);
	Unattached_Collision_Skip = addr_FixUnattachedCollisionPanic + 0x1B0B;
	UnattachedCollisionGuard = safetyhook::create_mid(addr_FixUnattachedCollisionPanic + 0x6, OnUnattachedCollision);

	// Hair-curve over-read
	MemoryHelper::WriteMemory<uint8_t>(GetAddress(Addr::FixHairCurveOverRead), 0x73);

	// MMX over-read + spline-prefetch overrun
	MemoryHelper::WriteMemory<uint8_t>(GetAddress(Addr::MmxOverRead), 0x6E);
	MemoryHelper::WriteMemory<uint8_t>(GetAddress(Addr::SplinePrefetchOverrun), 0x73);

	// FaceFX actor teardown: skip the corrupt loop when the container is stale
	FxActorLoopExit = GetAddress(Addr::FaceFxActorLoopExit);
	FxActorLoopGuard = safetyhook::create_mid(GetAddress(Addr::FaceFxActorLoopGuard), OnFxActorLoop);

	// Particle mesh-emitter material destruction race
	DWORD addr_ParticleMaterialDispatchSite = GetAddress(Addr::ParticleMaterialDispatchSite);
	ParticleMaterialContinue = addr_ParticleMaterialDispatchSite + 0x5;
	ParticleMaterialSkip = addr_ParticleMaterialDispatchSite + 0x14;
	MemoryHelper::MakeJMP(addr_ParticleMaterialDispatchSite, reinterpret_cast<uintptr_t>(&ParticleMaterialDeadFlagStub));
}
