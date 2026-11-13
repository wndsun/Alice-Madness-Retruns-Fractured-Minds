#pragma once

#include "Coop/Protocol.hpp"

#include <cstdint>
#include <string>

namespace AliceCoop
{
	void Initialize();
	// trailfront1: puts the crash-trail handler in front of the crash
	// reporter; call right after CrashHandler::Install().
	void MoveCrashTrailHandlerToFront();
	// musicwatch2: called from the XInputGetState hook (state = XINPUT_STATE*)
	void FilterPadForMusicWatch(void* state, unsigned long* result);
	void Tick();
	// perf1: the time the coop part of the ProcessEvent hook took.
	long long PerfNow();
	void PerfNoteProcessEvent(long long startCounter);
	// Call from Loop_Hook right BEFORE the original engine tick:
	// drops null entries from the engine's deferred-cleanup list.
	void ScrubPendingCleanupObjects(uintptr_t engineLoop);
	void PumpLifecycleCommands();
	void OnAlicePawnTicked(AAlicePawn* pawn);
	void DrawTuningOverlay(UCanvas* canvas);
	void RecordLocalAction(AliceCoopProtocol::PlayerAction action);
	// AlicePlayerController.TryToCancelMatinee: the local player skipped.
	bool OnLocalCancelMatinee();
	// true: drop the call (a second Start of an open shared board).
	bool TraceUiCall(UObject* object, UFunction* function, void* parameters);
	// Trailer camera (N / 5 / 6): writes the view after
	// AlicePlayerCamera.UpdateCamera.
	void ApplyFreeCamera(void* camera);
	void OnLocalPepperProjectileSpawn(
		APepperGrinderPrimaryProjectile* projectile,
		const FVector& direction);
	// Noted at PostBeginPlay, sent once the game has aimed the bullet.
	void QueueLocalPepperProjectile(
		APepperGrinderPrimaryProjectile* projectile);
	// Script-spawned emitters (jump, float, glide), noted at PostBeginPlay.
	void QueueLocalEmitter(AEmitter* emitter);
	// Teapot Cannon shells, noted at PostBeginPlay and sent once aimed.
	void QueueLocalTeapotProjectile(ATeapotCannonProjectile* projectile);
	// Before every ProcessEvent: a local shot's Destroyed sends where it ended.
	void NoteProjectileProcessEvent(UObject* object, UFunction* function);
	void OnLocalClockBombSpawn(AAliceClonePawn* bomb);
	void OnLocalClockBombDetonate(AAliceClonePawn* bomb);
	void OnLocalClockBombDestroyed(AAliceClonePawn* bomb);
	void ReportClothDriverProbe(uintptr_t configuredRva, uintptr_t moduleBase,
		bool installed);
	void TraceClothDriverRegisters(uintptr_t eax, uintptr_t ecx, uintptr_t edx,
		uintptr_t ebx, uintptr_t esi, uintptr_t edi, uintptr_t ebp);
	void TraceHairSolverCall(const void* solver, const void* returnAddress);
	void TraceClothSolverCall(const void* solver, const void* returnAddress,
		int particleCount);
	void TraceProcessEvent(UObject* object, UFunction* function,
		const void* parameters);
	void TraceWorldProcessEvent(UObject* object, UFunction* function,
		const void* parameters, bool after);
	void HandleSharedCombatProcessEvent(UObject* object,
		UFunction* function, const void* parameters, bool after);
	bool ShouldSuppressSharedPlayerDamage(UObject* object,
		UFunction* function, const void* parameters);
	bool IsApplyingHostProgression();
	void TraceLifecycleProcessEvent(UObject* object,
		UFunction* function, const void* parameters, bool after);
	void RecordHostLoadChapter(std::uint8_t chapter);
	void ObservePauseMenuState(bool open);
	void HandleSharedInteractionProcessEvent(UObject* object,
		const void* parameters, bool after);
	void TraceSequenceOpProcessEvent(UObject* object,
		bool activated, bool after);
	bool ShouldDeferSequenceOpActivation(UObject* object);
	void TraceInterpolationStarted(AActor* actor,
		USeqAct_Interp* action);
	void RepairRemoteVisibilityAfterLocalDodge();
	bool IsEnabled();
	std::string GetOverlayStatusLine();
	bool SetServerEndpoint(const std::string& address, int port);
	bool IsHostInGameplay();
	// true: drop the client's Q (AlicePlayerController.CloneButtonPressed).
	bool ShouldBlockLocalClockBomb();
	std::string GetOverlayDebugDetails();
	void ExecuteDevCommand(int command);
	bool IsActionTraceEnabled();
	// Called for every ProcessEvent so the local Alice's particle notifies can
	// be forwarded to the other player's proxy.
	void CaptureParticleNotify(UObject* object, UFunction* function,
		const void* parameters);
	bool IsWorldTraceEnabled();
	bool ShouldUseUniqueMutex();
	void ObserveSavePath(const wchar_t* effectivePath);
	bool TryRedirectClientSave(const wchar_t* originalPath, std::wstring& redirectedPath);
}
