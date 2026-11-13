#pragma once

#include <d3d9.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <wincodec.h>
#include <Xinput.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <cerrno>
#include <cfloat>
#include <cmath>
#include <atomic>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <mutex>
#include "Common.hpp"
#include "Features.hpp"
#include "Coop/CoopClient.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Trailer camera (N) state, defined in Coop/CoopClient.cpp.
namespace AliceCoop { bool IsTrailerHudHidden(); bool IsSpectatingHost(); bool IsWatchingPuzzle(); }

namespace AchievementOverlay
{
    // Config
    inline constexpr bool kBlockGameInputWhileVisible = true;
    inline constexpr unsigned long long kCursorIdleHideMs = 3000;

    // State
    inline IDirect3DDevice9* g_pDevice = nullptr;
    inline IDirect3DDevice9* g_pInitializedDevice = nullptr;
    inline HWND g_hWnd = nullptr;
    inline WNDPROC g_oWndProc = nullptr;
    inline uintptr_t g_devicePtrAddr = 0;

    // Shared tutorial boards (co-op): the host turns the pages.
    // Host: while its board is open, its key presses are collected here and
    // sent to the client. Client: while the host's board is confirmed open,
    // its own key presses and clicks do not reach the game; the host's keys
    // are posted to the window and let through by the pending counters.
    struct CoopBoardKey
    {
        unsigned int vk = 0;
        long lParam = 0;
        bool down = false;
    };
    inline std::atomic<bool> g_coopBoardInputCapture{ false };
    inline std::atomic<bool> g_coopBoardInputBlocked{ false };
    inline std::mutex g_coopBoardKeyMutex;
    inline std::vector<CoopBoardKey> g_coopBoardKeys;
    inline std::atomic<int> g_coopBoardInjectPending[256]{};

    inline bool g_hooksInstalled = false;
    inline bool g_imguiInitialized = false;
    inline bool g_inReset = false;
    inline bool g_deviceLost = false;
    inline bool g_visible = false;
    inline bool g_aliceCoopMenuVisible = false;
    inline bool g_coopDevMode = false;
    inline std::string g_coopDevStatus;
    inline std::string g_coopDevDetails;
    inline std::mutex g_coopDevMutex;
    inline std::atomic<int> g_coopDevCommand{ 0 };

    enum class CoopDevCommand : int
    {
        None = 0,
        TestDodge = 1,
        TestMeleeTrail = 2,
        TestMuzzle = 3,
        TestShrink = 4,
        TestGlide = 5,
        ToggleProxyHidden = 6,
        PreviousVfxAnchor = 7,
        NextVfxAnchor = 8,
        TestWeaponEffect = 9,
        PepperHypothesis1 = 10,
        PepperHypothesis2 = 11,
        PepperHypothesis3 = 12,
        BombHypothesis1 = 13,
        BombHypothesis2 = 14,
        BombHypothesis3 = 15,
        ClearProjectileTests = 16,
    };

    inline float g_uiScale = 1.0f;
    inline float g_pendingScale = 0.0f;

    inline unsigned long long g_lastMouseInputTick = 0;

    // Overlay textures (co-op icons)
    struct Texture
    {
        IDirect3DTexture9* tex = nullptr;
        int w = 0;
        int h = 0;
    };

    inline Texture g_cutsceneWatchTexture;
    // Watching the host in the real world (London): fan-drawn icons
    // images\watch_1.png, watch_2.png, ... (one picked at random per game
    // start, like omega_X); cutsceneWatch2.png if there is none.
    inline Texture g_spectateTexture;
    inline bool g_spectateTextureLoadAttempted = false;
    inline bool g_showCutsceneWatchIcon = false; // icon removed from the mod
    inline bool g_cutsceneWatchTextureLoadAttempted = false;
    inline Texture g_coopWaitTexture;
    inline bool g_coopWaitTextureLoadAttempted = false;
    inline Texture g_soloMinigameTexture;
    inline bool g_soloMinigameTextureLoadAttempted = false;
    inline std::atomic<bool> g_peerWatchingCutscene{ false };
    inline std::atomic<bool> g_coopWaitingForPeer{ false };
    inline std::atomic<bool> g_coopForceCutsceneRequested{ false };
    inline std::atomic<unsigned long long>
        g_soloMinigameWarningUntil{ 0 };
    inline std::atomic<unsigned long long>
        g_coopJoinTeleportHintUntil{ 0 };
    inline std::atomic<bool> g_peerCutsceneScreenPositionValid{ false };
    inline std::atomic<float> g_peerCutsceneScreenX{ 0.0f };
    inline std::atomic<float> g_peerCutsceneScreenY{ 0.0f };
    inline std::atomic<bool> g_coopMenuVisible{ false };
    inline std::atomic<bool> g_coopMenuHostRole{ false };
    inline std::atomic<bool> g_coopMenuRelayConnected{ false };
    inline std::atomic<bool> g_coopMenuPeerConnected{ false };
    inline std::atomic<bool> g_coopMenuCanJoinHost{ false };
    inline std::atomic<bool> g_coopMenuHovered{ false };
    inline std::atomic<bool> g_coopJoinHostRequested{ false };
    inline std::atomic<bool> g_coopPauseVisible{ false };
    inline std::atomic<bool> g_coopPauseHostRole{ false };
    inline std::atomic<bool> g_coopPausePeerConnected{ false };
    inline std::atomic<bool> g_coopPauseHovered{ false };
    inline std::atomic<bool> g_coopMovementTrailsEnabled{ false };
    inline std::atomic<bool> g_coopMovementTrailsToggleRequested{ false };
    inline std::atomic<bool> g_coopSaveSyncAvailable{ false };
    inline std::atomic<bool> g_coopSaveSyncInProgress{ false };
    inline std::atomic<int> g_coopSaveSyncProgress{ 0 };
    inline std::atomic<bool> g_coopSaveSyncRequested{ false };
    inline std::atomic<bool> g_coopSaveSyncWarningVisible{ false };

    inline std::atomic<bool> g_coopSaveSyncConfirmKeyDown{ false };
	inline std::atomic<bool> g_coopSaveSyncShortcutDown{ false };
	inline std::mutex g_coopSaveSyncMutex;
	inline std::string g_coopSaveSyncStatus;
	inline std::string g_coopSaveSyncProfileName;
    inline bool g_coopContextShortcutDown = false;
    inline std::mutex g_coopMenuMutex;
    inline std::string g_coopMenuPeerMap;
    inline std::string g_coopMenuStatus;
    // The achievement system has been removed (achievements window, toasts,
    // Achievements.txt, trophy console hooks). g_visible stays only so the
    // input/cursor plumbing below keeps compiling; nothing turns it on.
    inline bool IsVisible() { return g_visible; }

    // Helpers
    inline IDirect3DDevice9* GetDevice()
    {
        if (g_devicePtrAddr == 0)
            return nullptr;

        return *reinterpret_cast<IDirect3DDevice9**>(g_devicePtrAddr);
    }

    // Initial scale guess from the backbuffer, the runtime scale from io.DisplaySize.y corrects it
    inline float ComputeUiScale(IDirect3DDevice9* dev)
    {
        float renderHeight = 1080.0f;
        IDirect3DSurface9* bb = nullptr;
        if (dev && SUCCEEDED(dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb)) && bb)
        {
            D3DSURFACE_DESC d{};
            if (SUCCEEDED(bb->GetDesc(&d)))
            {
                renderHeight = (float)d.Height;
            }

            bb->Release();
        }

        return (renderHeight > 1080.0f ? renderHeight / 1080.0f : 1.0f);
    }

    // Texture & text loading
    inline bool LoadTextureFromFile(IDirect3DDevice9* dev, const char* path, Texture& out, int targetSize = 0)
    {
        static bool s_comInit = false;
        if (!s_comInit)
        {
            HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
            if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) return false;
            s_comInit = true;
        }

        wchar_t wpath[MAX_PATH];
        if (MultiByteToWideChar(CP_UTF8, 0, path, -1, wpath, MAX_PATH) == 0)
        {
            return false;
        }

        IWICImagingFactory* factory = nullptr;
        if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))))
        {
            return false;
        }

        bool ok = false;
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frame = nullptr;
        IWICBitmapScaler* scaler = nullptr;
        IWICFormatConverter* conv = nullptr;
        IDirect3DTexture9* tex = nullptr;

        if (SUCCEEDED(factory->CreateDecoderFromFilename(wpath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder)) && SUCCEEDED(decoder->GetFrame(0, &frame)) && SUCCEEDED(factory->CreateFormatConverter(&conv)))
        {
            // Scale first, then convert to BGRA
            IWICBitmapSource* src = frame;
            if (targetSize > 0 && SUCCEEDED(factory->CreateBitmapScaler(&scaler)) && SUCCEEDED(scaler->Initialize(frame, targetSize, targetSize, WICBitmapInterpolationModeFant)))
            {
                src = scaler;
            }

            if (SUCCEEDED(conv->Initialize(src, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom)))
            {
                UINT w = 0, h = 0;
                conv->GetSize(&w, &h);
                if (w > 0 && h > 0 && SUCCEEDED(dev->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tex, nullptr)))
                {
                    D3DLOCKED_RECT rect{};
                    if (SUCCEEDED(tex->LockRect(0, &rect, nullptr, 0)))
                    {
                        // CopyPixels honors the destination stride, so it fills the locked rect even when Pitch != w*4.
                        HRESULT cp = conv->CopyPixels(nullptr, (UINT)rect.Pitch, (UINT)rect.Pitch * h, (BYTE*)rect.pBits);
                        tex->UnlockRect(0);
                        if (SUCCEEDED(cp))
                        {
                            out.tex = tex;
                            out.w = (int)w;
                            out.h = (int)h;
                            ok = true;
                        }
                    }
                }
            }
        }

        if (!ok && tex) tex->Release();
        if (conv) conv->Release();
        if (scaler) scaler->Release();
        if (frame) frame->Release();
        if (decoder) decoder->Release();
        factory->Release();
        return ok;
    }

    inline void ReleaseCutsceneWatchTexture()
    {
        if (g_cutsceneWatchTexture.tex)
            g_cutsceneWatchTexture.tex->Release();
        g_cutsceneWatchTexture = {};
        g_cutsceneWatchTextureLoadAttempted = false;
        if (g_coopWaitTexture.tex)
            g_coopWaitTexture.tex->Release();
        g_coopWaitTexture = {};
        g_coopWaitTextureLoadAttempted = false;
        if (g_soloMinigameTexture.tex)
            g_soloMinigameTexture.tex->Release();
        g_soloMinigameTexture = {};
        g_soloMinigameTextureLoadAttempted = false;
    }

    inline void LoadCutsceneWatchTexture(IDirect3DDevice9* dev)
    {
        if (g_cutsceneWatchTexture.tex
            || g_cutsceneWatchTextureLoadAttempted || !dev)
        {
            return;
        }

        g_cutsceneWatchTextureLoadAttempted = true;
        const std::string path = SystemHelper::GetModulePath()
            + "\\AliceCoop\\images\\cutsceneWatch2.png";
        const int target = static_cast<int>(
            58.0f * g_uiScale + 0.5f);
        LoadTextureFromFile(
            dev, path.c_str(), g_cutsceneWatchTexture, target);
    }

    inline void LoadCoopWaitTexture(IDirect3DDevice9* dev)
    {
        if (g_coopWaitTexture.tex
            || g_coopWaitTextureLoadAttempted || !dev)
        {
            return;
        }

        g_coopWaitTextureLoadAttempted = true;
        const std::string path = SystemHelper::GetModulePath()
            + "\\AliceCoop\\images\\aliceWhait.png";
        const int target = static_cast<int>(
            86.0f * g_uiScale + 0.5f);
        LoadTextureFromFile(
            dev, path.c_str(), g_coopWaitTexture, target);
    }

    inline void LoadSoloMinigameTexture(IDirect3DDevice9* dev)
    {
        if (g_soloMinigameTexture.tex
            || g_soloMinigameTextureLoadAttempted || !dev)
        {
            return;
        }

        g_soloMinigameTextureLoadAttempted = true;
        const std::string path = SystemHelper::GetModulePath()
            + "\\AliceCoop\\images\\aliceSoloLevel.png";
        const int target = static_cast<int>(
            82.0f * g_uiScale + 0.5f);
        LoadTextureFromFile(
            dev, path.c_str(), g_soloMinigameTexture, target);
    }

    // ImGui setup
    inline void InitImGui(IDirect3DDevice9* pDevice)
    {
        if (g_imguiInitialized || !pDevice || !g_hWnd)
            return;

        g_uiScale = (g_pendingScale > 0.0f) ? g_pendingScale : ComputeUiScale(pDevice);

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;

        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::StyleColorsDark();
        style.ScaleAllSizes(g_uiScale);
        style.FontScaleDpi = g_uiScale; // scales the font to the render resolution
        style.AntiAliasedLinesUseTex = false; // we render with point sampling, which the textured-line path can't use

        if (g_uiScale < 1.15f)
        {
            io.Fonts->AddFontDefaultBitmap();
        }
        else
        {
            io.Fonts->AddFontDefaultVector();
        }

        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX9_Init(pDevice);

        g_imguiInitialized = true;
        g_pInitializedDevice = pDevice;
    }

    inline void ShutdownImGui()
    {
        if (!g_imguiInitialized) return;

        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        g_imguiInitialized = false;
        g_pInitializedDevice = nullptr;
    }

    // Rendering
    inline void DrawCoopDevModeBadge()
    {
        if (!g_coopDevMode)
            return;

        const float scale = g_uiScale;
        const ImVec2 padding(12.0f * scale, 8.0f * scale);
        const ImVec2 origin(16.0f * scale, 16.0f * scale);
        const char* label = "COOP DEV MODE";
        const ImVec2 textSize = ImGui::CalcTextSize(label);
        const ImVec2 statusSize = ImGui::CalcTextSize(
            g_coopDevStatus.c_str());
        const float contentWidth =
            textSize.x > statusSize.x ? textSize.x : statusSize.x;
        const float statusGap =
            g_coopDevStatus.empty() ? 0.0f : 5.0f * scale;
        const float contentHeight =
            textSize.y + statusGap
            + (g_coopDevStatus.empty() ? 0.0f : statusSize.y);
        const ImVec2 minimum(
            origin.x, origin.y);
        const ImVec2 maximum(
            origin.x + contentWidth + padding.x * 2.0f,
            origin.y + contentHeight + padding.y * 2.0f);
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(
            minimum, maximum, IM_COL32(7, 13, 23, 218),
            5.0f * scale);
        drawList->AddRect(
            minimum, maximum, IM_COL32(80, 190, 255, 230),
            5.0f * scale, 0, 1.0f * scale);
        drawList->AddText(
            ImVec2(origin.x + padding.x,
                origin.y + padding.y),
            IM_COL32(135, 220, 255, 255), label);
        if (!g_coopDevStatus.empty())
        {
            drawList->AddText(
                ImVec2(origin.x + padding.x,
                    origin.y + padding.y + textSize.y + statusGap),
                IM_COL32(205, 218, 228, 245),
                g_coopDevStatus.c_str());
        }
    }

    inline bool IsCoopDevInteractive()
    {
        return g_coopDevMode
            && (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
    }

    inline bool IsCoopWaitInteractive()
    {
        return g_coopWaitingForPeer.load(std::memory_order_acquire)
            && (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
    }

    inline void PollCoopContextShortcut()
    {
		const bool confirmVisible =
			g_coopSaveSyncWarningVisible.load(std::memory_order_acquire);
		const bool yesDown = (GetAsyncKeyState('Y') & 0x8000) != 0;
		const bool noDown = (GetAsyncKeyState('N') & 0x8000) != 0;
		const bool confirmDown = yesDown || noDown;
		if (confirmVisible && confirmDown
			&& !g_coopSaveSyncConfirmKeyDown.load(
				std::memory_order_relaxed))
		{
			g_coopSaveSyncWarningVisible.store(
				false, std::memory_order_release);
			if (yesDown)
				g_coopSaveSyncRequested.store(
					true, std::memory_order_release);
		}
		g_coopSaveSyncConfirmKeyDown.store(
			confirmDown, std::memory_order_relaxed);

        const bool keyDown =
            (GetAsyncKeyState('L') & 0x8000) != 0;
        if (keyDown && !g_coopContextShortcutDown)
        {
            // L is deliberately contextual: outside a visible co-op action it
            // remains an ordinary game key and cannot queue a later command.
            // (readycheck4: L no longer forces a held cutscene to start.)
            if (g_coopMenuVisible.load(std::memory_order_acquire)
                && !g_coopMenuHostRole.load(std::memory_order_acquire)
                && g_coopMenuCanJoinHost.load(std::memory_order_acquire))
            {
                g_coopJoinHostRequested.store(
                    true, std::memory_order_release);
            }
        }
        g_coopContextShortcutDown = keyDown;
    }

    inline void QueueCoopDevCommand(CoopDevCommand command)
    {
        g_coopDevCommand.store(
            static_cast<int>(command), std::memory_order_release);
    }

    // --------------------------------------------------------------
    // In-game AliceCoop settings menu (toggled with 'M'). Reuses the
    // same [Network] keys in AliceCoop.ini that the external launcher
    // already writes, so both stay consistent. Values are only applied
    // on the *next* launch — not live-reconnected mid-session, since
    // that would require rebuilding how the relay connection is set up,
    // which is a separate, riskier piece of work.
    //
    // Uses plain std::string + the ANSI (A-suffixed) ini functions,
    // matching how the rest of this file already builds paths via
    // SystemHelper::GetModulePath() (a narrow std::string) — see the
    // existing texture loading code above for the same
    // pattern.
    // --------------------------------------------------------------
    static char g_menuServerAddress[64] = "127.0.0.1";
    static char g_menuPort[8] = "27018";
    static int g_menuRoleIndex = 0; // 0 = Host, 1 = Client
    static bool g_menuValuesLoaded = false;
    static bool g_menuJustSaved = false;

    // Server-launch verification state. CreateProcess succeeding only means
    // Windows managed to start the executable — it doesn't rule out the
    // server crashing immediately after (e.g. its UDP port already being in
    // use by something else). We keep the process handle open briefly and
    // re-check it a moment later rather than trusting the launch call alone.
    static HANDLE g_menuServerProcessHandle = nullptr;
    static DWORD g_menuServerCheckDeadlineMs = 0;
    static bool g_menuServerCheckPending = false;
    static bool g_menuServerConfirmedRunning = false;
    static bool g_menuServerLaunchFailed = false;

    inline std::string AliceCoopMenu_IniPath()
    {
        return SystemHelper::GetModulePath() + "\\AliceCoop\\AliceCoop.ini";
    }

    inline void AliceCoopMenu_LoadFromIniIfNeeded()
    {
        if (g_menuValuesLoaded)
            return;
        g_menuValuesLoaded = true;

        const std::string iniPath = AliceCoopMenu_IniPath();

        char role[16] = "host";
        GetPrivateProfileStringA("Network", "Role", "host",
            role, sizeof(role), iniPath.c_str());
        g_menuRoleIndex = (_stricmp(role, "client") == 0) ? 1 : 0;

        GetPrivateProfileStringA("Network", "ServerAddress", "127.0.0.1",
            g_menuServerAddress, sizeof(g_menuServerAddress), iniPath.c_str());
        GetPrivateProfileStringA("Network", "Port", "27018",
            g_menuPort, sizeof(g_menuPort), iniPath.c_str());
    }

    // Finds the PID of a running process by its exact executable name, or 0
    // if none is found. Shared by AliceCoopMenu_IsProcessRunning() and
    // AliceCoopMenu_StopServerIfRunning() below.
    //
    // Takes a wide string and uses the plain (non-suffixed) PROCESSENTRY32 /
    // Process32First / Process32Next names rather than forcing the ANSI
    // "...A" variants: this project builds with UNICODE defined, and only
    // the macro-redirected plain names resolve correctly here (the explicit
    // "...A" names failed to compile at all) — so we go along with that
    // instead of fighting it.
    inline DWORD AliceCoopMenu_FindProcessId(const wchar_t* exeName)
    {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE)
            return 0;

        PROCESSENTRY32 entry{};
        entry.dwSize = sizeof(entry);

        DWORD foundPid = 0;
        if (Process32First(snapshot, &entry))
        {
            do
            {
                if (_wcsicmp(entry.szExeFile, exeName) == 0)
                {
                    foundPid = entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &entry));
        }

        CloseHandle(snapshot);
        return foundPid;
    }

    // Checks whether a process with this exact executable name is already
    // running, so clicking Save repeatedly (or already having the server up
    // from a previous session) never launches a second, competing relay
    // fighting over the same UDP port.
    inline bool AliceCoopMenu_IsProcessRunning(const wchar_t* exeName)
    {
        return AliceCoopMenu_FindProcessId(exeName) != 0;
    }

    // Closes AliceCoopServer.exe if it's currently running. Called when the
    // player switches the role selector from Host to Client — if you were
    // hosting and change your mind, there is no reason to leave the relay
    // running in the background with nobody left to serve.
    inline void AliceCoopMenu_StopServerIfRunning()
    {
        const DWORD pid = AliceCoopMenu_FindProcessId(L"AliceCoopServer.exe");
        if (pid == 0)
            return;

        HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if (process)
        {
            TerminateProcess(process, 0);
            CloseHandle(process);
        }
    }

    // Launches AliceCoopServer.exe with no visible console window (in place
    // of the separate cmd/AliceCoop-Server.bat window this used to require).
    // CREATE_NO_WINDOW is the standard flag for exactly this: it still runs
    // as a normal console-subsystem process, just without ever allocating a
    // visible console.
    inline void AliceCoopMenu_StartServerHidden()
    {
        // serverjob1: a server this game did not start (left over from an
        // earlier session, possibly an older build with another protocol) is
        // replaced, so the host always gets a relay of this build.
        static bool startedHere = false;
        if (!startedHere && AliceCoopMenu_IsProcessRunning(L"AliceCoopServer.exe"))
        {
            AliceCoopMenu_StopServerIfRunning();
            for (int wait = 0; wait < 20 && AliceCoopMenu_IsProcessRunning(L"AliceCoopServer.exe"); ++wait)
                Sleep(50);
        }
        if (AliceCoopMenu_IsProcessRunning(L"AliceCoopServer.exe"))
        {
            g_menuServerConfirmedRunning = true;
            g_menuServerLaunchFailed = false;
            g_menuServerCheckPending = false;
            return;
        }

        const std::string exePath = SystemHelper::GetModulePath() + "\\AliceCoop\\AliceCoopServer.exe";
        const std::string workingDir = SystemHelper::GetModulePath() + "\\AliceCoop";

        STARTUPINFOA startupInfo{};
        startupInfo.cb = sizeof(startupInfo);

        // serverjob1: the relay used to outlive the game - closed with
        // Alt+F4, crashed or ended any other way, the game left the hidden
        // AliceCoopServer.exe running (an old one then kept port 27018 and
        // the next start reused it). The server is now put in a job object
        // that kills it when the game's process goes away, however it ends.
        // The job handle is held for the game's lifetime on purpose.
        static HANDLE serverJob = []() -> HANDLE
        {
            HANDLE job = CreateJobObjectA(nullptr, nullptr);
            if (!job)
                return nullptr;
            JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
            limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
            if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation, &limits, sizeof(limits)))
            {
                CloseHandle(job);
                return nullptr;
            }
            return job;
        }();

        PROCESS_INFORMATION processInfo{};
        const BOOL started = CreateProcessA(
            exePath.c_str(),
            nullptr,
            nullptr, nullptr,
            FALSE,
            CREATE_NO_WINDOW | CREATE_SUSPENDED,
            nullptr,
            workingDir.c_str(),
            &startupInfo, &processInfo);

        if (!started)
        {
            g_menuServerConfirmedRunning = false;
            g_menuServerLaunchFailed = true;
            g_menuServerCheckPending = false;
            return;
        }

        if (serverJob)
            AssignProcessToJobObject(serverJob, processInfo.hProcess);
        startedHere = true;
        ResumeThread(processInfo.hThread);
        CloseHandle(processInfo.hThread);

        // Don't verify success yet — hold the process handle and check back
        // in a few hundred milliseconds, once the server has had a real
        // chance to either settle in or crash on startup.
        g_menuServerProcessHandle = processInfo.hProcess;
        g_menuServerCheckDeadlineMs = GetTickCount() + 500;
        g_menuServerCheckPending = true;
        g_menuServerConfirmedRunning = false;
        g_menuServerLaunchFailed = false;
    }

    // Call once per frame while the menu is open. Cheap no-op until the
    // deadline set by AliceCoopMenu_StartServerHidden() actually arrives.
    inline void AliceCoopMenu_PollServerCheck()
    {
        if (!g_menuServerCheckPending)
            return;
        if (GetTickCount() < g_menuServerCheckDeadlineMs)
            return;

        DWORD exitCode = 0;
        const bool stillRunning = g_menuServerProcessHandle
            && GetExitCodeProcess(g_menuServerProcessHandle, &exitCode)
            && exitCode == STILL_ACTIVE;

        g_menuServerConfirmedRunning = stillRunning;
        g_menuServerLaunchFailed = !stillRunning;

        if (g_menuServerProcessHandle)
        {
            CloseHandle(g_menuServerProcessHandle);
            g_menuServerProcessHandle = nullptr;
        }
        g_menuServerCheckPending = false;
    }

    static bool g_menuLiveEndpointApplied = false;

    // Logo (shown above the status line in the settings menu) and the
    // blinking indicator icon (shown when the menu is closed) — both PNGs,
    // loaded once on first use and cached. Load failures are silent: the
    // menu/indicator simply skip drawing the image if the file isn't there
    // yet, rather than breaking anything.
    static Texture g_menuLogoTexture;
    static bool g_menuLogoLoadAttempted = false;
    static Texture g_menuIndicatorTexture;
    static bool g_menuIndicatorLoadAttempted = false;

    inline void AliceCoopMenu_LoadImagesIfNeeded(IDirect3DDevice9* pDevice)
    {
        if (!g_menuLogoLoadAttempted)
        {
            g_menuLogoLoadAttempted = true;
            const std::string path = SystemHelper::GetModulePath() + "\\AliceCoop\\images\\logo.png";
            LoadTextureFromFile(pDevice, path.c_str(), g_menuLogoTexture);
        }
        if (!g_menuIndicatorLoadAttempted)
        {
            g_menuIndicatorLoadAttempted = true;
            // Fan-drawn indicator icons: images\omega_1.png, omega_2.png, ...
            // (as many as there are, counted from 1 until the first gap).
            // One is picked at random once per game start.
            const std::string folder = SystemHelper::GetModulePath() + "\\AliceCoop\\images\\";
            int count = 0;
            while (count < 999)
            {
                const std::string candidate = folder + "omega_" + std::to_string(count + 1) + ".png";
                if (GetFileAttributesA(candidate.c_str()) == INVALID_FILE_ATTRIBUTES)
                    break;
                ++count;
            }
            std::string path;
            if (count > 0)
            {
                LARGE_INTEGER ticks{};
                QueryPerformanceCounter(&ticks);
                const unsigned long long seed = static_cast<unsigned long long>(ticks.QuadPart)
                    ^ (static_cast<unsigned long long>(GetCurrentProcessId()) << 16);
                const int pick = static_cast<int>(seed % static_cast<unsigned long long>(count)) + 1;
                path = folder + "omega_" + std::to_string(pick) + ".png";
            }
            else
            {
                path = folder + "indicator.png"; // old name, if no omega_X is there
            }
            LoadTextureFromFile(pDevice, path.c_str(), g_menuIndicatorTexture);
        }
    }

    inline void AliceCoopMenu_SaveToIni()
    {
        const std::string iniPath = AliceCoopMenu_IniPath();
        const char* roleValue = (g_menuRoleIndex == 1) ? "client" : "host";
        WritePrivateProfileStringA("Network", "Role", roleValue, iniPath.c_str());
        WritePrivateProfileStringA("Network", "ServerAddress", g_menuServerAddress, iniPath.c_str());
        WritePrivateProfileStringA("Network", "Port", g_menuPort, iniPath.c_str());

        // The address/port change applies immediately — g_serverEndpoint is
        // just "where the next packet goes", read fresh on every send, so
        // there's no socket to tear down or reconnect. The Role itself is
        // NOT applied live (switching Host<->Client changes whether a local
        // relay is expected at all, which is a bigger, riskier change to
        // make mid-session) — that part still only takes effect next launch.
        const int portNumber = std::atoi(g_menuPort);
        g_menuLiveEndpointApplied = AliceCoop::SetServerEndpoint(g_menuServerAddress, portNumber);

        // Host needs the relay running; Client just connects to one that's
        // (presumably) already running on the host's machine — nothing to
        // start locally for that role.
        if (g_menuRoleIndex == 0)
        {
            AliceCoopMenu_StartServerHidden();
        }
    }

    // Small blinking indicator + key hint, shown whenever the settings menu
    // is closed — a quiet "the mod is here, press M" signal rather than a
    // full status panel. Hidden while the menu itself is open, and reappears
    // once it's closed again.
    inline void DrawAliceCoopIndicatorIcon(IDirect3DDevice9* pDevice)
    {
        if (g_aliceCoopMenuVisible)
            return;
        // Only on the title/main menu and on the pause menu - never over
        // gameplay. (It used to be drawn whenever the settings menu was
        // closed, i.e. all the time.)
        if (!g_coopMenuVisible.load(std::memory_order_acquire)
            && !g_coopPauseVisible.load(std::memory_order_acquire))
        {
            return;
        }

        AliceCoopMenu_LoadImagesIfNeeded(pDevice);
        if (!g_menuIndicatorTexture.tex)
            return;

        const float scale = g_uiScale;

        // Size follows the image's own proportions rather than forcing a
        // fixed square — the longest side is capped at kMaxIconSize so an
        // unexpectedly large source image never dominates the screen, but
        // nothing stretches or distorts the aspect ratio to fill a box.
        constexpr float kMaxIconSide = 180.0f;
        const float nativeW = static_cast<float>(g_menuIndicatorTexture.w);
        const float nativeH = static_cast<float>(g_menuIndicatorTexture.h);
        const float longestSide = (nativeW > nativeH) ? nativeW : nativeH;
        const float fitRatio = (longestSide > kMaxIconSide) ? (kMaxIconSide / longestSide) : 1.0f;
        const float iconWidth = nativeW * fitRatio * scale;
        const float iconHeight = nativeH * fitRatio * scale;

        // Client only, and only once the HOST is confirmed to actually be
        // in a real level (not just "a relay exists" — that was the bug:
        // AliceCoop::IsHostInGameplay() specifically checks the host's
        // reported map isn't the menu/placeholder level). While that's true
        // and the peer isn't visible yet, blink faster and add a "Press L"
        // hint (L is the mod's existing join/force-cutscene key) — a nudge
        // that the client still needs to press it to actually join. Once a
        // peer is visible, this reverts to the normal slow pulse with just
        // the base "Press M" hint.
        const std::string statusLine = AliceCoop::GetOverlayStatusLine();
        const bool isClient = statusLine.find("CLIENT") != std::string::npos;
        const bool waitingForPeer = statusLine.find("WAITING FOR PEER") != std::string::npos;
        const bool showJoinHint = isClient && waitingForPeer && AliceCoop::IsHostInGameplay();

        const float pulsePeriodMs = showJoinHint ? 700.0f : 2000.0f;
        const float phase = static_cast<float>(GetTickCount() % static_cast<unsigned int>(pulsePeriodMs)) / pulsePeriodMs;
        const float pulse = 0.5f + 0.5f * sinf(phase * 6.2831853f);
        const float alpha = 0.35f + 0.65f * pulse;

        const ImGuiIO& io = ImGui::GetIO();
        const ImVec2 iconMin(
            18.0f * scale,
            io.DisplaySize.y - iconHeight - 46.0f * scale);
        const ImVec2 iconMax(iconMin.x + iconWidth, iconMin.y + iconHeight);

        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddImage(
            reinterpret_cast<ImTextureID>(g_menuIndicatorTexture.tex),
            iconMin, iconMax,
            ImVec2(0, 0), ImVec2(1, 1),
            IM_COL32(255, 255, 255, static_cast<int>(alpha * 255.0f)));

        constexpr const char* hintM = "Press M";
        const ImVec2 hintMSize = ImGui::CalcTextSize(hintM);
        const ImVec2 hintMPos(
            iconMin.x + (iconWidth - hintMSize.x) * 0.5f,
            iconMax.y + 6.0f * scale);
        drawList->AddText(
            hintMPos,
            IM_COL32(235, 220, 225, static_cast<int>(alpha * 255.0f)),
            hintM);

        if (showJoinHint)
        {
            constexpr const char* hintL = "Press L to let a friend join";
            const ImVec2 hintLSize = ImGui::CalcTextSize(hintL);
            const ImVec2 hintLPos(
                iconMin.x + (iconWidth - hintLSize.x) * 0.5f,
                hintMPos.y + hintMSize.y + 4.0f * scale);
            drawList->AddText(
                hintLPos,
                IM_COL32(255, 191, 91, static_cast<int>(alpha * 255.0f)),
                hintL);
        }
    }

    inline void DrawAliceCoopMenu(IDirect3DDevice9* pDevice)
    {
        if (!g_aliceCoopMenuVisible)
            return;

        AliceCoopMenu_LoadFromIniIfNeeded();
        AliceCoopMenu_PollServerCheck();
        AliceCoopMenu_LoadImagesIfNeeded(pDevice);

        const float scale = g_uiScale;
        // menulogo1 (11.11, the new design): the logo (images\logo.png) sits
        // ABOVE the menu panel, outside it and without a frame, centred on
        // the panel; the panel itself is unchanged. Its size follows the
        // image's proportions, at most the panel's width.
        const bool haveLogo = g_menuLogoTexture.tex && g_menuLogoTexture.w > 0 && g_menuLogoTexture.h > 0;
        const float logoAspect = haveLogo
            ? static_cast<float>(g_menuLogoTexture.h) / static_cast<float>(g_menuLogoTexture.w) : 0.0f;
        const float logoMaxWidth = 400.0f * scale;
        const float logoNativeWidth = haveLogo ? static_cast<float>(g_menuLogoTexture.w) * scale : 0.0f;
        const float logoWidth = haveLogo ? (logoNativeWidth < logoMaxWidth ? logoNativeWidth : logoMaxWidth) : 0.0f;
        const float logoHeight = logoWidth * logoAspect;
        const float logoGap = 6.0f * scale;
        // menupos1: on every opening (M) the menu sits at the left, centred
        // vertically together with the logo above it (pivot = the panel's
        // vertical middle, shifted down by half the logo block).
        const ImVec2 display = ImGui::GetIO().DisplaySize;
        const float logoBlock = haveLogo ? logoHeight + logoGap : 0.0f;
        ImGui::SetNextWindowPos(
            ImVec2(16.0f * scale, display.y * 0.5f + logoBlock * 0.5f),
            ImGuiCond_Appearing,
            ImVec2(0.0f, 0.5f));
        ImGui::SetNextWindowSize(
            ImVec2(430.0f * scale, 0.0f),
            ImGuiCond_FirstUseEver);
        constexpr ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_AlwaysAutoResize
            | ImGuiWindowFlags_NoTitleBar;

        // Dark burgundy theme, matching the game's own palette. Pushed
        // before Begin (so the window background itself picks it up) and
        // popped after End — always both, regardless of what Begin returns,
        // since Begin/End must always be paired and the colors need to wrap
        // that whole pair.
        constexpr int kStyleColorCount = 9;
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.03f, 0.04f, 0.97f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.45f, 0.08f, 0.10f, 0.85f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.92f, 0.88f, 0.85f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.35f, 0.08f, 0.10f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.55f, 0.12f, 0.14f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.65f, 0.15f, 0.17f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.16f, 0.06f, 0.07f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.22f, 0.08f, 0.09f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.85f, 0.25f, 0.20f, 1.0f));

        if (ImGui::Begin("AliceFracturedMinds", &g_aliceCoopMenuVisible, flags))
        {
            if (haveLogo)
            {
                // Drawn behind the menu, above its top edge, centred on it.
                const ImVec2 windowPos = ImGui::GetWindowPos();
                const ImVec2 windowSize = ImGui::GetWindowSize();
                const float width = logoWidth;
                const float height = logoHeight;
                ImVec2 logoMin(windowPos.x + (windowSize.x - width) * 0.5f,
                    windowPos.y - height - logoGap);
                if (logoMin.x < 0.0f)
                    logoMin.x = 0.0f;
                if (logoMin.y < 0.0f)
                    logoMin.y = 0.0f;
                ImGui::GetBackgroundDrawList()->AddImage(
                    reinterpret_cast<ImTextureID>(g_menuLogoTexture.tex),
                    logoMin, ImVec2(logoMin.x + width, logoMin.y + height));
            }

            // Re-read every frame the menu is open, so this always reflects
            // the current live state — not a cached snapshot from when the
            // menu was opened.
            const std::string statusLine = AliceCoop::GetOverlayStatusLine();
            if (!statusLine.empty())
            {
                const bool online = statusLine.find("RELAY ONLINE") != std::string::npos;
                ImGui::TextColored(
                    online ? ImVec4(0.4f, 0.9f, 0.4f, 1.0f) : ImVec4(0.9f, 0.7f, 0.3f, 1.0f),
                    "%s", statusLine.c_str());
            }
            else
            {
                ImGui::TextDisabled("Not connected yet.");
            }
            ImGui::Spacing();

            ImGui::TextDisabled("Server address/port apply immediately. Role change needs a restart.");
            ImGui::Spacing();

            ImGui::RadioButton("Host", &g_menuRoleIndex, 0);
            ImGui::SameLine();
            if (ImGui::RadioButton("Client", &g_menuRoleIndex, 1))
            {
                // Just switched to Client — if a relay was running from an
                // earlier Host session, there's no one left for it to serve.
                AliceCoopMenu_StopServerIfRunning();
            }

            ImGui::InputText("Server address", g_menuServerAddress, sizeof(g_menuServerAddress));
            ImGui::InputText("Port", g_menuPort, sizeof(g_menuPort));

            ImGui::Spacing();
            if (ImGui::Button("Save"))
            {
                AliceCoopMenu_SaveToIni();
                g_menuJustSaved = true;
            }

            if (g_menuJustSaved)
            {
                if (!g_menuLiveEndpointApplied)
                {
                    ImGui::TextColored(ImVec4(0.95f, 0.35f, 0.35f, 1.0f),
                        "Saved, but the address wasn't a valid IPv4 address — not applied.");
                }
                else if (g_menuRoleIndex != 0)
                {
                    // Client role never launches a server — nothing further
                    // to verify, the address/port change alone is enough.
                    ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "Saved and applied.");
                }
                else if (g_menuServerCheckPending)
                {
                    ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.4f, 1.0f), "Saved and applied. Starting server...");
                }
                else if (g_menuServerConfirmedRunning)
                {
                    ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "Saved and applied. Server running.");
                }
                else if (g_menuServerLaunchFailed)
                {
                    ImGui::TextColored(ImVec4(0.95f, 0.35f, 0.35f, 1.0f), "Saved and applied. Server failed to start!");
                }
            }
        }
        ImGui::End();
        ImGui::PopStyleColor(kStyleColorCount);
    }

    inline void DrawCoopDevInteractivePanel()
    {
        if (!IsCoopDevInteractive())
            return;

        const float scale = g_uiScale;
        ImGui::SetNextWindowPos(
            ImVec2(16.0f * scale, 92.0f * scale),
            ImGuiCond_Always);
        ImGui::SetNextWindowSize(
            ImVec2(430.0f * scale, 0.0f),
            ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.94f);
        constexpr ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_AlwaysAutoResize;
        if (ImGui::Begin("AliceCoop dev mode",
            nullptr, flags))
        {
            ImGui::TextDisabled(
                "Runtime diagnostics. Hold Alt to keep this panel open.");
            std::string details;
            {
                std::lock_guard<std::mutex> lock(g_coopDevMutex);
                details = g_coopDevDetails;
            }
            if (!details.empty())
                ImGui::TextUnformatted(details.c_str());
            else
                ImGui::TextDisabled("No remote presentation data yet.");
        }
        ImGui::End();
    }

    inline void DrawPeerCutsceneIndicator(IDirect3DDevice9* pDevice)
    {
        // The cutsceneWatch2 icon was removed from the mod (25.10).
        if (!g_showCutsceneWatchIcon
            || !g_peerWatchingCutscene.load(std::memory_order_acquire))
            return;

        LoadCutsceneWatchTexture(pDevice);

        const float scale = g_uiScale;
        const float iconSize = 58.0f * scale;
        const float margin = 18.0f * scale;
        const ImGuiIO& io = ImGui::GetIO();
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        const float preferredIconX =
            io.DisplaySize.x - margin - iconSize;
        const ImVec2 iconMinimum(
            preferredIconX > margin ? preferredIconX : margin,
            margin);
        const ImVec2 iconMaximum(
            iconMinimum.x + iconSize, iconMinimum.y + iconSize);
        if (g_cutsceneWatchTexture.tex)
        {
            drawList->AddImage(
                (ImTextureID)(uintptr_t)g_cutsceneWatchTexture.tex,
                iconMinimum, iconMaximum);
        }
        else
        {
            drawList->AddCircle(
                ImVec2(iconMinimum.x + iconSize * 0.5f,
                    iconMinimum.y + iconSize * 0.5f),
                iconSize * 0.34f,
                IM_COL32(244, 205, 92, 235),
                24, 2.0f * scale);
        }
    }

    inline void DrawSpectateIndicator(IDirect3DDevice9* pDevice)
    {
        // chesswatch1: also while the other player solves a puzzle
        if (!AliceCoop::IsSpectatingHost() && !AliceCoop::IsWatchingPuzzle())
            return;
        if (!g_spectateTextureLoadAttempted && pDevice)
        {
            g_spectateTextureLoadAttempted = true;
            const std::string folder = SystemHelper::GetModulePath() + "\\AliceCoop\\images\\";
            int count = 0;
            while (count < 999)
            {
                const std::string candidate = folder + "watch_" + std::to_string(count + 1) + ".png";
                if (GetFileAttributesA(candidate.c_str()) == INVALID_FILE_ATTRIBUTES)
                    break;
                ++count;
            }
            std::string path = folder + "cutsceneWatch2.png";
            if (count > 0)
            {
                LARGE_INTEGER ticks{};
                QueryPerformanceCounter(&ticks);
                const unsigned long long seed = static_cast<unsigned long long>(ticks.QuadPart)
                    ^ (static_cast<unsigned long long>(GetCurrentProcessId()) << 20);
                const int pick = static_cast<int>(seed % static_cast<unsigned long long>(count)) + 1;
                path = folder + "watch_" + std::to_string(pick) + ".png";
            }
            // watchsize1: the picture is loaded at its own size (no resize)
            LoadTextureFromFile(pDevice, path.c_str(), g_spectateTexture, 0);
        }
        const float scale = g_uiScale;
        const float margin = 18.0f * scale;
        const ImGuiIO& io = ImGui::GetIO();
        // watchsize1 (08.11 request): the watch_X icon is drawn at the size
        // of the image itself (times the UI scale), keeping its proportions;
        // a huge one is limited to a third of the screen height.
        float iconWidth = 58.0f * scale;
        float iconHeight = 58.0f * scale;
        if (g_spectateTexture.tex && g_spectateTexture.w > 0 && g_spectateTexture.h > 0)
        {
            iconWidth = static_cast<float>(g_spectateTexture.w) * scale;
            iconHeight = static_cast<float>(g_spectateTexture.h) * scale;
            const float maxHeight = io.DisplaySize.y / 3.0f;
            if (iconHeight > maxHeight && iconHeight > 0.0f)
            {
                iconWidth *= maxHeight / iconHeight;
                iconHeight = maxHeight;
            }
        }
        const float iconSize = iconHeight < iconWidth ? iconHeight : iconWidth;
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        const float x = io.DisplaySize.x - margin - iconWidth;
        const ImVec2 iconMinimum(x > margin ? x : margin, margin);
        const ImVec2 iconMaximum(iconMinimum.x + iconWidth, iconMinimum.y + iconHeight);
        if (g_spectateTexture.tex)
        {
            drawList->AddImage((ImTextureID)(uintptr_t)g_spectateTexture.tex,
                iconMinimum, iconMaximum);
        }
        else
        {
            drawList->AddCircle(ImVec2(iconMinimum.x + iconSize * 0.5f,
                iconMinimum.y + iconSize * 0.5f), iconSize * 0.34f,
                IM_COL32(244, 205, 92, 235), 24, 2.0f * scale);
        }
    }

    inline void DrawCoopWaitIndicator(IDirect3DDevice9* pDevice)
    {
        if (!g_coopWaitingForPeer.load(std::memory_order_acquire))
            return;

        // No aliceWhait icon any more (removed from the mod): text only.
        (void)pDevice;
        const float scale = g_uiScale;
        const float panelWidth = 445.0f * scale;
        const float panelHeight = 100.0f * scale;
        const float iconSize = 0.0f;
        const float panelTop = 62.0f * scale;
        const float padding = 12.0f * scale;
        const ImGuiIO& io = ImGui::GetIO();
        const ImVec2 panelMinimum(
            (io.DisplaySize.x - panelWidth) * 0.5f,
            panelTop);
        const ImVec2 panelMaximum(
            panelMinimum.x + panelWidth,
            panelMinimum.y + panelHeight);
        const ImVec2 iconMinimum(
            panelMinimum.x + padding,
            panelMinimum.y + (panelHeight - iconSize) * 0.5f);
        const ImVec2 iconMaximum(
            iconMinimum.x + iconSize,
            iconMinimum.y + iconSize);
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(
            panelMinimum, panelMaximum,
            IM_COL32(15, 12, 20, 218),
            9.0f * scale);
        drawList->AddRect(
            panelMinimum, panelMaximum,
            IM_COL32(213, 193, 225, 185),
            9.0f * scale, 0, 1.2f * scale);
        const char* message = "Waiting for the other player...";
        const ImVec2 textSize = ImGui::CalcTextSize(message);
        const ImVec2 textPosition(
            iconMaximum.x + 15.0f * scale,
            panelMinimum.y + 25.0f * scale);
        drawList->AddText(
            textPosition,
            IM_COL32(244, 240, 248, 245),
            message);
        const ImVec2 emergencyPosition(
            textPosition.x,
            textPosition.y + textSize.y + 8.0f * scale);
        const ImVec2 buttonSize(320.0f * scale, 28.0f * scale);
        ImGui::SetNextWindowPos(
            ImVec2(emergencyPosition.x - 6.0f * scale,
                emergencyPosition.y - 5.0f * scale),
            ImGuiCond_Always);
        ImGui::SetNextWindowSize(
            ImVec2(buttonSize.x + 12.0f * scale,
                buttonSize.y + 10.0f * scale),
            ImGuiCond_Always);
        constexpr ImGuiWindowFlags emergencyFlags =
            ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoBackground;
        if (ImGui::Begin(
            "##alicecoop_force_cutscene", nullptr, emergencyFlags))
        {
            constexpr const char* buttonText =
                "Press \"L\"  |  FORCE ACTIVATE FOR BOTH PLAYERS";
            const bool clicked = ImGui::InvisibleButton(
                "##alicecoop_force_cutscene_button", buttonSize);
            const ImVec2 buttonMinimum = ImGui::GetItemRectMin();
            const ImVec2 buttonMaximum = ImGui::GetItemRectMax();
            const bool buttonActive = ImGui::IsItemActive();
            const bool buttonHovered = ImGui::IsItemHovered();
            const ImU32 buttonColour = buttonActive
                ? IM_COL32(255, 224, 92, 255)
                : (buttonHovered
                    ? IM_COL32(255, 235, 122, 255)
                    : IM_COL32(255, 210, 54, 255));
            // The wait panel itself is rendered on ImGui's foreground list.
            // Draw the button there as well so its opaque colours are not
            // composited underneath the panel background.
            ImDrawList* buttonDrawList = ImGui::GetForegroundDrawList();
            buttonDrawList->AddRectFilled(
                buttonMinimum, buttonMaximum, buttonColour,
                5.0f * scale);
            buttonDrawList->AddRect(
                buttonMinimum, buttonMaximum,
                IM_COL32(32, 20, 8, 255),
                5.0f * scale, 0, 2.0f * scale);
            const ImVec2 buttonTextSize =
                ImGui::CalcTextSize(buttonText);
            buttonDrawList->AddText(
                ImVec2(
                    buttonMinimum.x
                        + (buttonSize.x - buttonTextSize.x) * 0.5f,
                    buttonMinimum.y
                        + (buttonSize.y - buttonTextSize.y) * 0.5f),
                IM_COL32(18, 12, 6, 255),
                buttonText);
            if (clicked && IsCoopWaitInteractive())
            {
                g_coopForceCutsceneRequested.store(
                    true, std::memory_order_release);
            }
        }
        ImGui::End();
    }

    inline bool IsSoloMinigameWarningVisible()
    {
        return GetTickCount64()
            < g_soloMinigameWarningUntil.load(
                std::memory_order_acquire);
    }

    inline bool IsCoopJoinTeleportHintVisible()
    {
        return GetTickCount64()
            < g_coopJoinTeleportHintUntil.load(
                std::memory_order_acquire);
    }

    inline void DrawCoopJoinTeleportHint()
    {
        if (!IsCoopJoinTeleportHintVisible())
            return;

        const float scale = g_uiScale;
        const char* heading = "JOIN COMPLETE";
        const char* message =
            "Press \"P\": safe teleport   |   Press \"O\": forced teleport";
        const ImVec2 headingSize = ImGui::CalcTextSize(heading);
        const ImVec2 messageSize = ImGui::CalcTextSize(message);
        const float paddingX = 18.0f * scale;
        const float paddingY = 11.0f * scale;
        const float gap = 5.0f * scale;
        const float panelWidth = (std::max)(headingSize.x, messageSize.x)
            + paddingX * 2.0f;
        const float panelHeight = headingSize.y + messageSize.y + gap
            + paddingY * 2.0f;
        const ImGuiIO& io = ImGui::GetIO();
        const ImVec2 minimum(
            (io.DisplaySize.x - panelWidth) * 0.5f,
            62.0f * scale);
        const ImVec2 maximum(
            minimum.x + panelWidth,
            minimum.y + panelHeight);
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(
            minimum, maximum, IM_COL32(12, 17, 27, 226),
            8.0f * scale);
        drawList->AddRect(
            minimum, maximum, IM_COL32(104, 205, 255, 225),
            8.0f * scale, 0, 1.2f * scale);
        const float textX = minimum.x + paddingX;
        drawList->AddText(
            ImVec2(textX, minimum.y + paddingY),
            IM_COL32(120, 220, 255, 255), heading);
        drawList->AddText(
            ImVec2(textX,
                minimum.y + paddingY + headingSize.y + gap),
            IM_COL32(242, 241, 237, 250), message);
    }

    inline void DrawCoopMainMenuPanel()
    {
        if (!g_coopMenuVisible.load(std::memory_order_acquire))
        {
            g_coopMenuHovered.store(false, std::memory_order_release);
            return;
        }

        std::string peerMap;
        std::string status;
        {
            std::lock_guard<std::mutex> lock(g_coopMenuMutex);
            peerMap = g_coopMenuPeerMap;
            status = g_coopMenuStatus;
        }
        const bool hostRole =
            g_coopMenuHostRole.load(std::memory_order_acquire);
        const bool relayConnected =
            g_coopMenuRelayConnected.load(std::memory_order_acquire);
        const bool peerConnected =
            g_coopMenuPeerConnected.load(std::memory_order_acquire);
        const bool canJoin =
            g_coopMenuCanJoinHost.load(std::memory_order_acquire);

        if (peerMap.size() > 38)
            peerMap = peerMap.substr(0, 35) + "...";
        if (status.size() > 48)
            status = status.substr(0, 45) + "...";

        const float scale = g_uiScale;
        const ImGuiIO& io = ImGui::GetIO();
        const ImVec2 panelSize(
            352.0f * scale,
            (hostRole ? 130.0f : 178.0f) * scale);
        const ImVec2 panelMinimum(
            18.0f * scale,
            io.DisplaySize.y - panelSize.y - 18.0f * scale);
        const ImVec2 panelMaximum(
            panelMinimum.x + panelSize.x,
            panelMinimum.y + panelSize.y);
        const float left = panelMinimum.x + 16.0f * scale;
        const float line = 22.0f * scale;

        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(
            panelMinimum, panelMaximum,
            IM_COL32(17, 15, 23, 226), 8.0f * scale);
        drawList->AddRect(
            panelMinimum, panelMaximum,
            IM_COL32(185, 169, 204, 205),
            8.0f * scale, 0, 1.3f * scale);
        drawList->AddText(
            ImVec2(left, panelMinimum.y + 13.0f * scale),
            IM_COL32(250, 235, 255, 255),
            "ALICE COOP");

        const char* roleText = hostRole ? "ROLE: HOST" : "ROLE: CLIENT";
        drawList->AddText(
            ImVec2(left, panelMinimum.y + 13.0f * scale + line),
            hostRole
                ? IM_COL32(255, 191, 91, 255)
                : IM_COL32(111, 196, 255, 255),
            roleText);
        drawList->AddText(
            ImVec2(left, panelMinimum.y + 13.0f * scale + line * 2.0f),
            relayConnected
                ? IM_COL32(118, 237, 151, 255)
                : IM_COL32(255, 206, 94, 255),
            relayConnected
                ? "RELAY: CONNECTED"
                : "RELAY: CONNECTING...");
        const std::string peerText = peerConnected
            ? "PEER: ONLINE  |  " + (
                peerMap.empty() ? std::string("map unknown") : peerMap)
            : "PEER: OFFLINE";
        drawList->AddText(
            ImVec2(left, panelMinimum.y + 13.0f * scale + line * 3.0f),
            peerConnected
                ? IM_COL32(118, 237, 151, 255)
                : IM_COL32(187, 180, 194, 255),
            peerText.c_str());

        if (!hostRole)
        {
            const ImVec2 buttonMinimum(
                left,
                panelMaximum.y - 45.0f * scale);
            const ImVec2 buttonSize(
                panelSize.x - 32.0f * scale,
                29.0f * scale);
            const ImVec2 buttonMaximum(
                buttonMinimum.x + buttonSize.x,
                buttonMinimum.y + buttonSize.y);

            ImGui::SetNextWindowPos(
                panelMinimum, ImGuiCond_Always);
            ImGui::SetNextWindowSize(
                panelSize, ImGuiCond_Always);
            constexpr ImGuiWindowFlags panelFlags =
                ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_NoBackground;
            if (ImGui::Begin(
                "##alicecoop_main_menu_panel", nullptr, panelFlags))
            {
                g_coopMenuHovered.store(
                    ImGui::IsWindowHovered(
                        ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
                    std::memory_order_release);
                ImGui::SetCursorScreenPos(buttonMinimum);
                const bool clicked = ImGui::InvisibleButton(
                    "##alicecoop_join_host", buttonSize);
                const bool active = ImGui::IsItemActive();
                const bool hovered = ImGui::IsItemHovered();
                const ImU32 fill = !canJoin
                    ? IM_COL32(57, 53, 63, 245)
                    : (active
                        ? IM_COL32(255, 218, 94, 255)
                        : (hovered
                            ? IM_COL32(255, 232, 127, 255)
                            : IM_COL32(247, 204, 70, 255)));
                drawList->AddRectFilled(
                    buttonMinimum, buttonMaximum,
                    fill, 5.0f * scale);
                drawList->AddRect(
                    buttonMinimum, buttonMaximum,
                    IM_COL32(29, 22, 12, 255),
                    5.0f * scale, 0, 1.5f * scale);
                const char* label = canJoin
                    ? "Press \"L\"  |  JOIN HOST CHECKPOINT"
                    : (status.empty()
                        ? "WAITING FOR HOST..."
                        : status.c_str());
                const ImVec2 textSize =
                    ImGui::CalcTextSize(label);
                drawList->AddText(
                    ImVec2(
                        buttonMinimum.x
                            + (buttonSize.x - textSize.x) * 0.5f,
                        buttonMinimum.y
                            + (buttonSize.y - textSize.y) * 0.5f),
                    canJoin
                        ? IM_COL32(22, 15, 8, 255)
                        : IM_COL32(194, 188, 201, 255),
                    label);
                if (clicked && canJoin)
                {
                    g_coopJoinHostRequested.store(
                        true, std::memory_order_release);
                }

				// The host-save overwrite (K) was removed: client progress is
				// kept in its own saves and mirrored back instead.
            }
            ImGui::End();
        }
        else
        {
            g_coopMenuHovered.store(false, std::memory_order_release);
        }
    }

	inline void DrawCoopSaveSyncWarning()
	{
		if (!g_coopSaveSyncWarningVisible.load(
				std::memory_order_acquire))
			return;

		const float scale = g_uiScale;
		const ImGuiIO& io = ImGui::GetIO();
		std::string profileName;
		{
			std::lock_guard<std::mutex> lock(g_coopSaveSyncMutex);
			profileName = g_coopSaveSyncProfileName;
		}
		if (profileName.size() > 40)
			profileName = profileName.substr(0, 37) + "...";
		const ImVec2 size(690.0f * scale, 232.0f * scale);
		const ImVec2 minimum(
			(io.DisplaySize.x - size.x) * 0.5f,
			(io.DisplaySize.y - size.y) * 0.5f);
		const ImVec2 maximum(minimum.x + size.x, minimum.y + size.y);
		ImDrawList* drawList = ImGui::GetForegroundDrawList();
		drawList->AddRectFilled(
			minimum, maximum, IM_COL32(24, 12, 14, 246),
			10.0f * scale);
		drawList->AddRect(
			minimum, maximum, IM_COL32(255, 92, 92, 255),
			10.0f * scale, 0, 2.0f * scale);
		const float left = minimum.x + 24.0f * scale;
		float top = minimum.y + 20.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(255, 91, 91, 255),
			"WARNING: HOST SAVE SYNCHRONIZATION");
		top += 34.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(255, 224, 94, 255),
			("SELECTED CLIENT PROFILE: \"" + profileName
				+ "\" WILL BE OVERWRITTEN.").c_str());
		top += 27.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(255, 240, 240, 255),
			"The HOST's complete saved progress will replace this profile.");
		top += 25.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(255, 194, 174, 255),
			"The client's checkpoints, collectibles, statistics and upgrades will be lost.");
		top += 25.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(213, 205, 216, 255),
			"Use a new empty client profile. Both files are verified before anything is replaced.");
		top += 39.0f * scale;
		drawList->AddText(
			ImVec2(left, top), IM_COL32(255, 224, 94, 255),
			"Press \"Y\" to receive and overwrite   |   Press \"N\" to cancel");
	}

	inline void DrawCoopPauseMenuPanel()
	{
		if (!g_coopPauseVisible.load(std::memory_order_acquire))
		{
			g_coopPauseHovered.store(false, std::memory_order_release);
			return;
		}

		const float scale = g_uiScale;
		const ImGuiIO& io = ImGui::GetIO();
		const ImVec2 panelSize(500.0f * scale, 205.0f * scale);
		const ImVec2 panelMinimum(
			18.0f * scale,
			io.DisplaySize.y - panelSize.y - 18.0f * scale);
		const ImVec2 panelMaximum(
			panelMinimum.x + panelSize.x,
			panelMinimum.y + panelSize.y);
		const float left = panelMinimum.x + 16.0f * scale;
		const float line = 23.0f * scale;
		const bool hostRole =
			g_coopPauseHostRole.load(std::memory_order_acquire);
		const bool peerConnected =
			g_coopPausePeerConnected.load(std::memory_order_acquire);
		bool trails = g_coopMovementTrailsEnabled.load(
			std::memory_order_acquire);

		// Use the foreground list just like the proven main-menu panel. A normal
		// ImGui window can be occluded by Alice's Scaleform pause movie in DX9.
		ImDrawList* drawList = ImGui::GetForegroundDrawList();
		drawList->AddRectFilled(
			panelMinimum, panelMaximum,
			IM_COL32(17, 15, 23, 240), 8.0f * scale);
		drawList->AddRect(
			panelMinimum, panelMaximum,
			IM_COL32(185, 169, 204, 225),
			8.0f * scale, 0, 1.3f * scale);
		drawList->AddText(
			ImVec2(left, panelMinimum.y + 13.0f * scale),
			IM_COL32(250, 235, 255, 255), "ALICE COOP");
		const std::string stateText = std::string("ROLE: ")
			+ (hostRole ? "HOST" : "CLIENT")
			+ "  |  PEER: " + (peerConnected ? "ONLINE" : "OFFLINE");
		drawList->AddText(
			ImVec2(left, panelMinimum.y + 13.0f * scale + line),
			peerConnected
				? IM_COL32(118, 237, 151, 255)
				: IM_COL32(205, 193, 211, 255),
			stateText.c_str());
		drawList->AddText(
			ImVec2(left, panelMinimum.y + 13.0f * scale + line * 2.0f),
			IM_COL32(230, 225, 234, 255),
			"P - safe teleport   |   O - forced teleport");
		drawList->AddText(
			ImVec2(left, panelMinimum.y + 13.0f * scale + line * 3.0f),
			IM_COL32(230, 225, 234, 255),
			"L - visible JOIN / FORCE CUTSCENE action");

		const ImVec2 checkMinimum(
			left, panelMinimum.y + 13.0f * scale + line * 4.25f);
		const float boxSize = 17.0f * scale;
		const ImVec2 checkMaximum(
			checkMinimum.x + boxSize, checkMinimum.y + boxSize);
		g_coopPauseHovered.store(false, std::memory_order_release);

		drawList->AddRectFilled(
			checkMinimum, checkMaximum,
			IM_COL32(48, 43, 56, 255),
			3.0f * scale);
		drawList->AddRect(
			checkMinimum, checkMaximum,
			IM_COL32(203, 186, 219, 255), 3.0f * scale);
		if (trails)
		{
			drawList->AddRectFilled(
				ImVec2(checkMinimum.x + 4.0f * scale,
					checkMinimum.y + 4.0f * scale),
				ImVec2(checkMaximum.x - 4.0f * scale,
					checkMaximum.y - 4.0f * scale),
				IM_COL32(255, 215, 93, 255), 2.0f * scale);
		}
		drawList->AddText(
			ImVec2(checkMaximum.x + 9.0f * scale, checkMinimum.y),
			IM_COL32(240, 232, 244, 255),
			"Keep proxy movement trails (double jump / glide)");
		drawList->AddText(
			ImVec2(left, checkMinimum.y + 27.0f * scale),
			IM_COL32(222, 207, 230, 255),
			"Press T while this pause menu is open to toggle");
		drawList->AddText(
			ImVec2(left, checkMinimum.y + 51.0f * scale),
			IM_COL32(174, 165, 183, 255),
			"Profile sync: return to the main menu and press K.");
	}

    inline void DrawSoloMinigameWarning(
        IDirect3DDevice9* pDevice)
    {
        if (!IsSoloMinigameWarningVisible())
            return;

        // No aliceSoloLevel icon any more (removed from the mod): text only.
        (void)pDevice;
        const float scale = g_uiScale;
        const char* heading = "SOLO MINIGAME";
        const char* message =
            "This section is played separately - share your score with your friend!";
        const ImVec2 headingSize = ImGui::CalcTextSize(heading);
        const ImVec2 messageSize = ImGui::CalcTextSize(message);
        const float iconSize = 0.0f;
        const float iconGap = 0.0f;
        const float paddingX = 18.0f * scale;
        const float paddingY = 13.0f * scale;
        const float gap = 6.0f * scale;
        const float textWidth =
            (std::max)(headingSize.x, messageSize.x);
        const float textHeight =
            headingSize.y + gap + messageSize.y;
        const float panelWidth =
            iconSize + iconGap + textWidth
                + paddingX * 2.0f;
        const float panelHeight =
            (std::max)(iconSize, textHeight)
                + paddingY * 2.0f;
        const ImGuiIO& io = ImGui::GetIO();
        const ImVec2 minimum(
            (io.DisplaySize.x - panelWidth) * 0.5f,
            62.0f * scale);
        const ImVec2 maximum(
            minimum.x + panelWidth,
            minimum.y + panelHeight);
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        drawList->AddRectFilled(
            minimum, maximum,
            IM_COL32(12, 17, 27, 226),
            8.0f * scale);
        drawList->AddRect(
            minimum, maximum,
            IM_COL32(235, 188, 82, 225),
            8.0f * scale, 0, 1.2f * scale);
        const ImVec2 iconMinimum(
            minimum.x + paddingX,
            minimum.y + (panelHeight - iconSize) * 0.5f);
        const ImVec2 iconMaximum(
            iconMinimum.x + iconSize,
            iconMinimum.y + iconSize);
        const float textX =
            iconMaximum.x + iconGap;
        const float textY =
            minimum.y + (panelHeight - textHeight) * 0.5f;
        drawList->AddText(
            ImVec2(textX, textY),
            IM_COL32(255, 210, 105, 255),
            heading);
        drawList->AddText(
            ImVec2(
                textX, textY + headingSize.y + gap),
            IM_COL32(242, 241, 237, 250),
            message);
    }

    // The Win32 backend forces a hardware cursor while the overlay is up, which is wrong when playing
    // on a controller. Keep it hidden unless the mouse moved or clicked in the last few seconds
    inline void UpdateOverlayCursor()
    {
        ImGuiIO& io = ImGui::GetIO();

        bool mouseActive = io.MouseDelta.x != 0.0f || io.MouseDelta.y != 0.0f || io.MouseWheel != 0.0f || ImGui::IsAnyMouseDown();

        if (mouseActive)
            g_lastMouseInputTick = GetTickCount64();

        if (!g_lastMouseInputTick || GetTickCount64() - g_lastMouseInputTick > kCursorIdleHideMs)
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }

    inline void Render(IDirect3DDevice9* pDevice)
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGuiIO& io = ImGui::GetIO();

        float clientW = io.DisplaySize.x;
        float clientH = io.DisplaySize.y;

        float renderW = clientW, renderH = clientH;
        IDirect3DSurface9* bb = nullptr;
        if (SUCCEEDED(pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb)) && bb)
        {
            D3DSURFACE_DESC d{};
            if (SUCCEEDED(bb->GetDesc(&d)) && d.Width > 0 && d.Height > 0)
            {
                renderW = (float)d.Width;
                renderH = (float)d.Height;
            }

            bb->Release();
        }

        io.DisplaySize = ImVec2(renderW, renderH);

        g_pendingScale = (renderH > 1080.0f ? renderH / 1080.0f : 1.0f);

        if (clientW > 0.0f && clientH > 0.0f && (renderW != clientW || renderH != clientH))
        {
            POINT pt;
            if (GetCursorPos(&pt) && ScreenToClient(g_hWnd, &pt))
            {
                io.AddMousePosEvent((float)pt.x * (renderW / clientW), (float)pt.y * (renderH / clientH));
            }
        }

        ImGui::NewFrame();

        if (ImDrawCallback setNearest = ImGui::GetPlatformIO().DrawCallback_SetSamplerNearest)
        {
            ImGui::GetBackgroundDrawList()->AddCallback(setNearest, nullptr);
        }

        // Trailer camera (N): no mod indicators either, only the game view
        // (the AliceCoop menu itself still opens with M).
        const bool trailerClean = AliceCoop::IsTrailerHudHidden();
        if (!trailerClean)
        {
        DrawPeerCutsceneIndicator(pDevice);
        DrawSpectateIndicator(pDevice);
        // readycheck4: the "waiting for the other player" window is gone -
        // the ready label is the game's own HUD prompt.
        DrawSoloMinigameWarning(pDevice);
        // DrawCoopMainMenuPanel() (the "ALICE COOP" branded panel with the
        // Join Host button) has been replaced by DrawAliceCoopIndicatorIcon
        // below — a small blinking icon + key hint instead of a full status
        // panel, per this project's own design.
        DrawAliceCoopIndicatorIcon(pDevice);
        }
        // DrawCoopPauseMenuPanel() (the "ALICE COOP" pause-screen panel with
        // P/O/L teleport hints and the movement-trails checkbox) is also no
        // longer drawn, for the same reason as the main-menu panel above.
        // The underlying hotkeys (P/O/L/T/K) themselves are handled
        // elsewhere and keep working — only this on-screen reminder panel
        // is gone.
		// DrawCoopSaveSyncWarning(): the host-save overwrite was removed.
        DrawAliceCoopMenu(pDevice);

        // menucursor1: the window draws its own cursor while it is open (the
        // game hides the system one), and never hides it for idleness.
        if (g_aliceCoopMenuVisible)
        {
            g_lastMouseInputTick = GetTickCount64();
        }
        else if (g_visible || IsCoopWaitInteractive()
            || g_coopMenuHovered.load(std::memory_order_acquire)
			|| g_coopPauseHovered.load(std::memory_order_acquire)
			|| g_coopSaveSyncWarningVisible.load(std::memory_order_acquire))
        {
            UpdateOverlayCursor();
        }
        else
        {
            g_lastMouseInputTick = 0;
        }

        ImGui::EndFrame();
        ImGui::Render();

        pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
        pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, FALSE);
        pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

    inline LRESULT CALLBACK WndProc_Hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        // Shared tutorial boards: the host's own keys from the other game,
        // posted by the co-op module, pass untouched.
        if ((msg == WM_KEYDOWN || msg == WM_KEYUP) && wParam < 256
            && g_coopBoardInjectPending[wParam].load(std::memory_order_acquire) > 0)
        {
            g_coopBoardInjectPending[wParam].fetch_sub(1, std::memory_order_acq_rel);
            return CallWindowProc(g_oWndProc, hWnd, msg, wParam, lParam);
        }
        if ((msg == WM_KEYDOWN || msg == WM_KEYUP)
            && g_coopBoardInputCapture.load(std::memory_order_acquire)
            && wParam != VK_ESCAPE && wParam != 'M'
            && !(wParam >= VK_F1 && wParam <= VK_F24))
        {
            // Host: this key turns the page here, and on the client too.
            std::lock_guard lock(g_coopBoardKeyMutex);
            if (g_coopBoardKeys.size() < 64)
                g_coopBoardKeys.push_back(CoopBoardKey{
                    static_cast<unsigned int>(wParam),
                    static_cast<long>(lParam), msg == WM_KEYDOWN });
        }
        if (g_coopBoardInputBlocked.load(std::memory_order_acquire))
        {
            // Client: the host turns the pages; releases still pass so no
            // key stays held in the game.
            switch (msg)
            {
                case WM_KEYDOWN: case WM_CHAR:
                case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
                case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
                case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
                case WM_MOUSEWHEEL: case WM_MOUSEHWHEEL:
                    return 0;
                default: break;
            }
        }
        const bool coopMenuVisible =
            g_coopMenuVisible.load(std::memory_order_acquire);
        const bool coopMenuHovered =
            g_coopMenuHovered.load(std::memory_order_acquire);
		const bool coopPauseVisible =
			g_coopPauseVisible.load(std::memory_order_acquire);
		const bool coopPauseHovered =
			g_coopPauseHovered.load(std::memory_order_acquire);
        const bool captureInput =
            g_visible || g_aliceCoopMenuVisible || IsCoopWaitInteractive()
			|| coopMenuHovered || coopPauseHovered
			|| g_coopSaveSyncWarningVisible.load(
				std::memory_order_acquire);
        if (g_imguiInitialized
            && (captureInput || coopMenuVisible || coopPauseVisible)
            && !g_deviceLost)
        {
            ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
            // menucursor1: M itself still reaches nothing else; Escape and
            // the other keys go to the window while it is open.

            if (kBlockGameInputWhileVisible && captureInput)
            {
                switch (msg)
                {
                    case WM_KEYUP: case WM_SYSKEYUP:
                    case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP:
                        break;

                    case WM_SYSKEYDOWN:
                        if (wParam == VK_F4 || wParam == VK_TAB) break;
                        return TRUE;

                    case WM_MOUSEMOVE:
                    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
                    case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
                    case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
                    case WM_MOUSEWHEEL: case WM_MOUSEHWHEEL:
                    case WM_KEYDOWN: case WM_CHAR:
                        return TRUE;

                    default: break;
                }
            }
        }

        return CallWindowProc(g_oWndProc, hWnd, msg, wParam, lParam);
    }

    // Device
    inline bool InstallHooks(IDirect3DDevice9* pDevice)
    {
        if (g_hooksInstalled || !pDevice)
            return g_hooksInstalled;

        D3DDEVICE_CREATION_PARAMETERS cp{};
        if (FAILED(pDevice->GetCreationParameters(&cp)) || !cp.hFocusWindow)
        {
            return false;
        }

        g_pDevice = pDevice;
        g_hWnd = cp.hFocusWindow;

        g_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProc_Hook)));

        g_hooksInstalled = true;
        return true;
    }

    inline bool PollDeviceHealth(IDirect3DDevice9* pDevice)
    {
        if (!pDevice) return false;

        HRESULT coop = pDevice->TestCooperativeLevel();
        if (coop != D3D_OK)
        {
            if (g_imguiInitialized && !g_deviceLost)
            {
                ImGui_ImplDX9_InvalidateDeviceObjects();
                g_deviceLost = true;
            }

            return false;
        }

        if (g_imguiInitialized && (g_deviceLost || g_inReset))
        {
            ImGui_ImplDX9_CreateDeviceObjects();
            g_deviceLost = false;
            g_inReset = false;
        }

        return true;
    }

    // Public API
    inline void Init(uintptr_t devicePtrAddr)
    {
        g_devicePtrAddr = devicePtrAddr;
    }

    inline void SetCoopDevMode(bool enabled)
    {
        g_coopDevMode = enabled;
    }

    inline void SetCoopDevStatus(const std::string& status)
    {
        g_coopDevStatus = status;
    }

    inline void SetCoopDevDetails(const std::string& details)
    {
        std::lock_guard<std::mutex> lock(g_coopDevMutex);
        g_coopDevDetails = details;
    }

    inline void SetPeerWatchingCutscene(
        bool watching, bool hasScreenPosition = false,
        float screenX = 0.0f, float screenY = 0.0f)
    {
        g_peerCutsceneScreenX.store(
            screenX, std::memory_order_relaxed);
        g_peerCutsceneScreenY.store(
            screenY, std::memory_order_relaxed);
        g_peerCutsceneScreenPositionValid.store(
            watching && hasScreenPosition,
            std::memory_order_release);
        g_peerWatchingCutscene.store(
            watching, std::memory_order_release);
    }

    inline void SetCoopWaitingForPeer(bool waiting)
    {
        g_coopWaitingForPeer.store(
            waiting, std::memory_order_release);
        if (!waiting)
        {
            g_coopForceCutsceneRequested.store(
                false, std::memory_order_release);
        }
    }

    inline void SetCoopMainMenuState(
        bool visible, bool hostRole,
        bool relayConnected, bool peerConnected,
        const std::string& peerMap,
        bool canJoinHost,
        const std::string& status)
    {
        {
            std::lock_guard<std::mutex> lock(g_coopMenuMutex);
            g_coopMenuPeerMap = peerMap;
            g_coopMenuStatus = status;
        }
        g_coopMenuHostRole.store(
            hostRole, std::memory_order_relaxed);
        g_coopMenuRelayConnected.store(
            relayConnected, std::memory_order_relaxed);
        g_coopMenuPeerConnected.store(
            peerConnected, std::memory_order_relaxed);
        g_coopMenuCanJoinHost.store(
            canJoinHost, std::memory_order_relaxed);
        g_coopMenuVisible.store(
            visible, std::memory_order_release);
        if (!visible)
        {
            g_coopMenuHovered.store(
                false, std::memory_order_release);
            g_coopJoinHostRequested.store(
                false, std::memory_order_release);
			g_coopSaveSyncWarningVisible.store(
				false, std::memory_order_release);
        }
    }

    inline bool ConsumeCoopJoinHostRequest()
    {
        return g_coopJoinHostRequested.exchange(
            false, std::memory_order_acq_rel);
    }

	inline void SetCoopPauseMenuState(
		bool visible, bool hostRole, bool peerConnected,
		bool movementTrailsEnabled)
	{
		g_coopPauseHostRole.store(hostRole, std::memory_order_relaxed);
		g_coopPausePeerConnected.store(
			peerConnected, std::memory_order_relaxed);
		g_coopMovementTrailsEnabled.store(
			movementTrailsEnabled, std::memory_order_relaxed);
		g_coopPauseVisible.store(visible, std::memory_order_release);
		if (!visible)
			g_coopPauseHovered.store(false, std::memory_order_release);
	}

	inline bool ConsumeCoopMovementTrailsToggle(bool& enabled)
	{
		if (!g_coopMovementTrailsToggleRequested.exchange(
				false, std::memory_order_acq_rel))
			return false;
		enabled = g_coopMovementTrailsEnabled.load(
			std::memory_order_acquire);
		return true;
	}

	inline void SetCoopSaveSyncState(
		bool available, bool inProgress, int progress,
		const std::string& status, const std::string& profileName)
	{
		{
			std::lock_guard<std::mutex> lock(g_coopSaveSyncMutex);
			g_coopSaveSyncStatus = status;
			g_coopSaveSyncProfileName = profileName;
		}
		g_coopSaveSyncAvailable.store(
			available, std::memory_order_relaxed);
		g_coopSaveSyncInProgress.store(
			inProgress, std::memory_order_relaxed);
		g_coopSaveSyncProgress.store(
			std::clamp(progress, 0, 100), std::memory_order_release);
	}

	inline bool ConsumeCoopSaveSyncRequest()
	{
		return g_coopSaveSyncRequested.exchange(
			false, std::memory_order_acq_rel);
	}

    inline bool ConsumeCoopForceCutsceneRequest()
    {
        return g_coopForceCutsceneRequested.exchange(
            false, std::memory_order_acq_rel);
    }

    inline void ShowSoloMinigameWarning(
        unsigned int durationMilliseconds)
    {
        g_soloMinigameWarningUntil.store(
            GetTickCount64() + durationMilliseconds,
            std::memory_order_release);
    }

    inline void HideSoloMinigameWarning()
    {
        g_soloMinigameWarningUntil.store(
            0, std::memory_order_release);
    }

    inline void ShowCoopJoinTeleportHint(
        unsigned int durationMilliseconds)
    {
        g_coopJoinTeleportHintUntil.store(
            GetTickCount64() + durationMilliseconds,
            std::memory_order_release);
    }

    inline void HideCoopJoinTeleportHint()
    {
        g_coopJoinTeleportHintUntil.store(
            0, std::memory_order_release);
    }

    inline int ConsumeCoopDevCommand()
    {
        return g_coopDevCommand.exchange(
            static_cast<int>(CoopDevCommand::None),
            std::memory_order_acq_rel);
    }

    inline void OnPresent(IDirect3DDevice9* pDevice)
    {
        if (!pDevice)
            return;

        if (!g_hooksInstalled)
        {
            InstallHooks(pDevice);
        }

        if (!PollDeviceHealth(pDevice))
        {
            return;
        }

        if (g_imguiInitialized && pDevice != g_pInitializedDevice)
        {
            ReleaseCutsceneWatchTexture();
            ShutdownImGui();
        }

        else if (g_imguiInitialized && g_pendingScale > 0.0f && ((g_pendingScale > g_uiScale ? g_pendingScale - g_uiScale : g_uiScale - g_pendingScale) > 0.01f))
        {
            ReleaseCutsceneWatchTexture(); // resolution changed: reload icons and re-bake the font
            ShutdownImGui();
        }

        if (!g_imguiInitialized)
        {
            InitImGui(pDevice);
        }

        if (!g_imguiInitialized
            || (!g_visible
                && !g_peerWatchingCutscene.load(
                    std::memory_order_acquire)
                && !g_coopWaitingForPeer.load(
                    std::memory_order_acquire)
                && !IsSoloMinigameWarningVisible()
                && !g_coopMenuVisible.load(
                    std::memory_order_acquire)
				&& !g_coopPauseVisible.load(
					std::memory_order_acquire)
				&& !g_coopSaveSyncWarningVisible.load(
					std::memory_order_acquire)
                // watchicon1 (10.11): the watch_X icon was drawn only when some
                // other overlay was up (the pause menu); watching is enough now
                && !AliceCoop::IsSpectatingHost()
                && !AliceCoop::IsWatchingPuzzle()))
            return;

        ImGui::GetIO().MouseDrawCursor =
            g_visible || g_aliceCoopMenuVisible || IsCoopWaitInteractive()
			|| g_coopPauseVisible.load(std::memory_order_acquire)
			|| g_coopSaveSyncWarningVisible.load(
				std::memory_order_acquire);

        IDirect3DStateBlock9* stateBlock = nullptr;
        if (FAILED(pDevice->CreateStateBlock(D3DSBT_ALL, &stateBlock)))
        {
            stateBlock = nullptr;
        }

        if (stateBlock)
        {
            stateBlock->Capture();
        }

        IDirect3DSurface9* prevRT = nullptr;
        IDirect3DSurface9* bb = nullptr;

        D3DVIEWPORT9 prevViewport{};
        RECT prevScissor{};
        const bool haveViewport = SUCCEEDED(pDevice->GetViewport(&prevViewport));
        const bool haveScissor = SUCCEEDED(pDevice->GetScissorRect(&prevScissor));

        if (SUCCEEDED(pDevice->GetRenderTarget(0, &prevRT)) && prevRT && SUCCEEDED(pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb)) && bb && SUCCEEDED(pDevice->SetRenderTarget(0, bb)))
        {
            DWORD prevColorWrite = 0;
            pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &prevColorWrite);
            pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

            HRESULT sceneHr = pDevice->BeginScene(); // if already open, skip our EndScene below
            Render(pDevice);

            if (SUCCEEDED(sceneHr))
            {
                pDevice->EndScene();
            }

            pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, prevColorWrite);
            pDevice->SetRenderTarget(0, prevRT);

            if (haveViewport)
            {
                pDevice->SetViewport(&prevViewport);
            }

            if (haveScissor)
            {
                pDevice->SetScissorRect(&prevScissor);
            }
        }

        if (stateBlock)
        {
            stateBlock->Apply();
            stateBlock->Release();
        }

        if (bb)
        {
            bb->Release();
        }

        if (prevRT)
        {
            prevRT->Release();
        }
    }

    inline void OnPresent()
    {
        OnPresent(GetDevice());
    }

    inline void OnDeviceLost()
    {
        g_inReset = true;
        if (g_imguiInitialized)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
        }
    }

    inline void OnDeviceReset(IDirect3DDevice9* pDevice)
    {
        if (g_imguiInitialized)
        {
            ImGui_ImplDX9_CreateDeviceObjects();
        }

        g_inReset = false;
    }

    inline void OnDeviceReset()
    {
        OnDeviceReset(GetDevice());
    }

    inline void Toggle()
    {
        // Achievements window removed: nothing to toggle.
    }

    inline void Update(IDirect3DDevice9* pDevice)
    {
        if (!g_hooksInstalled)
        {
            InstallHooks(pDevice);
        }

        PollDeviceHealth(pDevice);

        PollCoopContextShortcut();

        // menucursor1 (07.11 request): M opens the AliceFracturedMinds window
        // only on the main menu or the pause menu (where the "M" icon is),
        // and while it is open the mouse cursor is shown and the window takes
        // the mouse and keyboard, so the IP / port can be edited. M again (or
        // leaving the menu / resuming the game) closes it and gives the
        // input back to the game.
        const bool inMenu = g_coopMenuVisible.load(std::memory_order_acquire)
            || g_coopPauseVisible.load(std::memory_order_acquire);
        if (GetAsyncKeyState('M') & 1)
        {
            if (g_aliceCoopMenuVisible)
                g_aliceCoopMenuVisible = false;
            else if (inMenu)
                g_aliceCoopMenuVisible = true;
        }
        if (g_aliceCoopMenuVisible && !inMenu)
            g_aliceCoopMenuVisible = false;
        if (g_aliceCoopMenuVisible)
            ClipCursor(nullptr);
    }
}
