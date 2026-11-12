#include "Common.hpp"
#include "Features.hpp"
#include "Coop/CoopClient.hpp"

safetyhook::InlineHook XInputGetStateHook;
safetyhook::InlineHook XInputSetStateHook;

static DWORD WINAPI XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	if (dwUserIndex != 0) return ERROR_DEVICE_NOT_CONNECTED;
	unsigned long result = ControllerHelper::PollController(pState, InvertABXYButtons, InvertShoulderTriggers);
	AliceCoop::FilterPadForMusicWatch(pState, &result); // musicwatch2
	return static_cast<DWORD>(result);
}

static DWORD WINAPI XInputSetState_Hook(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
	if (dwUserIndex != 0) return ERROR_DEVICE_NOT_CONNECTED;
	return ControllerHelper::SetVibration(pVibration);
}

void ApplyUseSDLControllerInput()
{
	if (!UseSDLControllerInput) return;

	ControllerHelper::InitializeSDLGamepad();
	XInputGetStateHook = HookHelper::CreateHookAPI(L"XINPUT1_3.dll", "XInputGetState", &XInputGetState_Hook);
	XInputSetStateHook = HookHelper::CreateHookAPI(L"XINPUT1_3.dll", "XInputSetState", &XInputSetState_Hook);
}
