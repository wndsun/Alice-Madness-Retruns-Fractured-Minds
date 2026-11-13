#include "Common.hpp"
#include "Features.hpp"

static safetyhook::MidHook SkipMovie{};
safetyhook::InlineHook FFullScreenMovieBink_PlayMovie;

static bool shouldSkipMovie = false;
// introskip3 (13.11 18:33:50 Steam client, 18:53:12 EA host, both ~14 s
// after launch: binkw32 BinkDoFrameAsyncWait wrote past a frame buffer on
// Bink's own decode thread, filling it with 0x10 - the first frame being
// set up). The skip cut the intro off at its very first check, while that
// first frame was still being decoded. It now waits until the intro has
// played for a moment, as when a player presses the skip key.
static ULONGLONG skipArmedAt = 0;

static unsigned int __fastcall FFullScreenMovieBink_PlayMovie_Hook(int* thisp, int, int a2, const wchar_t* MovieFilename, int a4, int a5, int a6, int a7, unsigned int a8, int a9, WORD* Src)
{
	if (MovieFilename)
	{
		if (_wcsicmp(MovieFilename, L"LoadingMovie.bik\x00") == 0)
		{
			(void)FFullScreenMovieBink_PlayMovie.disable();
			(void)SkipMovie.disable();
		}
		else if (SkipEAIntro && _wcsicmp(MovieFilename, L"Intro_EA.bik\x00") == 0)
		{
			shouldSkipMovie = true;
			skipArmedAt = GetTickCount64();
		}
		else if (SkipSHIntro && _wcsicmp(MovieFilename, L"Intro_SH.bik\x00") == 0)
		{
			shouldSkipMovie = true;
			skipArmedAt = GetTickCount64();
		}
		else if (SkipUEIntro && _wcsicmp(MovieFilename, L"TechLogo_Short.bik\x00") == 0)
		{
			shouldSkipMovie = true;
			skipArmedAt = GetTickCount64();
		}
	}

	return FFullScreenMovieBink_PlayMovie.unsafe_thiscall<unsigned int>(thisp, a2, MovieFilename, a4, a5, a6, a7, a8, a9, Src);
}

static void OnSkipMovie(safetyhook::Context& ctx)
{
	if (shouldSkipMovie && GetTickCount64() - skipArmedAt >= 600)
	{
		ctx.eax = 0;
		shouldSkipMovie = false;
	}
}

void ApplyIntroSkip()
{
	if (!SkipEAIntro && !SkipSHIntro && !SkipUEIntro) return;

	FFullScreenMovieBink_PlayMovie = HookHelper::CreateHook((void*)GetAddress(Addr::PlayMovie), &FFullScreenMovieBink_PlayMovie_Hook);
	SkipMovie = safetyhook::create_mid(GetAddress(Addr::SkipMovie), OnSkipMovie);
}
