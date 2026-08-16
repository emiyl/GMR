#include <windows.h>
#include <cstring>
#include <filesystem>
#include <string>
#include <cstdarg>
#include <new>

#include "GameMaker.h"
#include "MemoryManager.h"
#include "globals.h"

struct tagYYGUID { unsigned char bytes[16]{}; };

enum LibraryInitState
{
    PreInit = 0,
    Init = 1,
    PostQuit = 2
};

enum yyal_result_t
{
    YYAL_ERR_NONE = 0,
    YYAL_ERR_CRIT = 1,
    YYAL_ERR_INIT = 2,
    YYAL_ERR_PTR = 3,
    YYAL_ERR_OP = 4,
    YYAL_ERR_IDX = 5,
    YYAL_ERR_INST = 6,
    YYAL_ERR_VAL = 7,
    YYAL_ERR_DONE = 8
};

bool Run_Running = true;
int Game_Id = 0;
tagYYGUID Game_GUID{};
LibraryInitState s_yyalInitState = LibraryInitState::PreInit;
void* Score_Caption = nullptr;
void* Lives_Caption = nullptr;
void* Health_Caption = nullptr;
void* Load_GameName = nullptr;

inline void YYInfo(const char* /*fmt*/, ...) {}
inline void YYWarning(const char* /*fmt*/, ...) {}
inline void YYError(const char* /*fmt*/, ...) {}
inline bool InitRuntime() { return true; }
inline void Quit() {}
inline void RunGame() {}
inline void Run_EndGame() {}
inline void EndOfGame() {}
inline void MainLoop_Process() {}
inline void ProcessMessages() {}
inline HWND PlaceholderSetFocus(HWND hWnd) { return hWnd; }
inline void HookMouseStartTimer() {}
inline void BeginToEnd() {}
inline void SetSchedulerResolution(int) {}
inline void timeEndPeriod(int) {}
inline void DoGenerationalGC(int) {}
inline void ProcessObjectDisposeList() {}
inline void ResetObjectGCList() {}
inline void CheckYYAL(yyal_result_t) {}
inline yyal_result_t YYAL_Quit() { return YYAL_ERR_NONE; }
inline void* exception_handler = nullptr;
inline void* runtime_check_handler = nullptr;
inline void _RTC_SetErrorFunc(void*) {}
inline void* AvSetMmThreadCharacteristicsA(const char*, DWORD*) { return nullptr; }
inline BOOL AvSetMmThreadPriority(HANDLE, int) { return TRUE; }
inline void* SetUnhandledExceptionFilter(void*) { return nullptr; }
inline UINT SetErrorMode(UINT) { return 0; }
const int AVRT_PRIORITY_CRITICAL = 5;

static std::string WideToUtf8(const std::wstring& text)
{
    if (text.empty())
        return {};

    const int required = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (required <= 0)
        return {};

    std::string out(static_cast<size_t>(required) - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1, out.data(), required, nullptr, nullptr);
    return out;
}

static char* DuplicateCString(const char* value)
{
    if (value == nullptr)
        return nullptr;

    const size_t length = std::strlen(value) + 1u;
    char* copy = new char[length];
    std::memcpy(copy, value, length);
    return copy;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    g_ReturnCode = 0;
    g_MainThreadId = GetCurrentThreadId();
    g_hInstance = hInstance;

    SetProcessDPIAware();

    const std::wstring commandLineW = GetCommandLineW();
    const std::string commandLineA = WideToUtf8(commandLineW);
    if (g_pCommandLine != nullptr)
    {
        delete[] g_pCommandLine;
        g_pCommandLine = nullptr;
    }
    g_pCommandLine = DuplicateCString(commandLineA.c_str());

    ProcessCommandLine(g_pCommandLine);

    if (g_fCreateMiniDump)
    {
        const UINT previousMode = SetErrorMode(SEM_FAILCRITICALERRORS);
        SetErrorMode(previousMode | SEM_FAILCRITICALERRORS);
        SetUnhandledExceptionFilter(exception_handler);
        _RTC_SetErrorFunc(runtime_check_handler);
    }

    wchar_t modulePath[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, modulePath, MAX_PATH);

    const std::filesystem::path basePath(modulePath);
    const std::filesystem::path dataWinPath = basePath.parent_path() / L"data.win";

    if (g_pGameName != nullptr)
    {
        delete[] g_pGameName;
        g_pGameName = nullptr;
    }

    if (std::filesystem::exists(dataWinPath))
    {
        const std::string gameNameUtf8 = WideToUtf8(dataWinPath.wstring());
        g_pGameName = DuplicateCString(gameNameUtf8.c_str());
    }

    if (!InitRuntime())
        return 0;

    timeGetDevCaps(&g_TimeCaps, sizeof(g_TimeCaps));
    SetSchedulerResolution(g_TimeCaps.wPeriodMin);

    if (g_bSetHighProcessPriority)
    {
        const HANDLE processHandle = GetCurrentProcess();
        if (SetPriorityClass(processHandle, HIGH_PRIORITY_CLASS))
        {
            YYInfo("Set process priority to HIGH_PRIORITY_CLASS\n");
        }
        else if (SetPriorityClass(processHandle, ABOVE_NORMAL_PRIORITY_CLASS))
        {
            YYInfo("Set process priority to ABOVE_NORMAL_PRIORITY_CLASS\n");
        }

        const HANDLE threadHandle = GetCurrentThread();
        if (SetThreadPriority(threadHandle, THREAD_PRIORITY_HIGHEST))
        {
            YYInfo("Set main thread priority to HIGHEST\n");
        }

        DWORD powerState = 1;
        const BOOL powerSet = SetProcessInformation(processHandle, ProcessPowerThrottling, &powerState, sizeof(powerState));
        if (!powerSet)
            YYInfo("!!! Couldn't set process power settings\n");

        DWORD taskIndex = 0;
        HANDLE mmcss = AvSetMmThreadCharacteristicsA("Games", &taskIndex);
        if (mmcss == nullptr)
        {
            YYInfo("Couldn\'t set main thread characteristics with AvSetMmThreadCharacteristicsA()\n");
        }
        else
        {
            YYInfo("Registered with MMCSS 'Games' task\n");
            if (AvSetMmThreadPriority(mmcss, AVRT_PRIORITY_CRITICAL) == FALSE)
                YYInfo("!!! Couldn\'t set MMCSS thread priority to CRITICAL\n");
            else
                YYInfo("Set MMCSS thread priority to CRITICAL\n");
        }
    }

    BeginToEnd();
    PlaceholderSetFocus(g_pMainWindow);
    HookMouseStartTimer();

    while (!g_fExitAfterFirstRoomCreationCode && Run_Running)
    {
        // Main loop body preserved from the decompilation.
        if (!g_fWallpaperMouseTimerMethod)
        {
            MainLoop_Process();
        }
        else
        {
            DWORD flags = MWMO_INPUTAVAILABLE;
            MsgWaitForMultipleObjectsEx(1, &g_hHookMouseTimer, 0, 0x1cff, flags);
        }

        ProcessMessages();
    }

    if (!Run_Running)
        Run_EndGame();

    EndOfGame();

    if (s_yyalInitState != LibraryInitState::PostQuit && !g_fNoAudio)
    {
        if (s_yyalInitState == LibraryInitState::Init)
        {
            const yyal_result_t audioResult = YYAL_Quit();
            CheckYYAL(audioResult);
            s_yyalInitState = LibraryInitState::PostQuit;
        }
        else
        {
            YYWarning("Warning: Prevented call into an uninitialised yyal\n");
        }
    }

    PostMessageW(g_pMainWindow, WM_QUIT, 0, 0);
    Quit();
    RunGame();

    // Cleanup and shutdown sequence from the decompiled routine.
    if (Score_Caption != nullptr) { MemoryManager::Free(Score_Caption, false); Score_Caption = nullptr; }
    if (Lives_Caption != nullptr) { MemoryManager::Free(Lives_Caption, false); Lives_Caption = nullptr; }
    if (Health_Caption != nullptr) { MemoryManager::Free(Health_Caption, false); Health_Caption = nullptr; }
    if (Load_GameName != nullptr) { MemoryManager::Free(Load_GameName, false); Load_GameName = nullptr; }
    if (g_pGameName != nullptr) { MemoryManager::Free(g_pGameName, false); g_pGameName = nullptr; }
    if (g_pWorkingDirectory != nullptr) { MemoryManager::Free(g_pWorkingDirectory, false); g_pWorkingDirectory = nullptr; }
    if (g_pFilePrePend != nullptr) { MemoryManager::Free(g_pFilePrePend, false); g_pFilePrePend = nullptr; }

    const bool doGc = g_fDoGC;
    Game_GUID = {};
    Game_Id = 0;
    g_ApplicationSurface = -0x1112153;
    g_ApplicationWidth = -1;
    g_ApplicationHeight = -1;
    g_Application_Surface_Autodraw = true;
    g_NewApplicationWidth = -1;
    g_NewApplicationHeight = -1;
    g_NewApplicationSize = false;
    g_CurrViewSurfaceTexture = nullptr;
    g_pGlobal = nullptr;
    g_pGCObjectContainer = nullptr;

    if (!g_fHeadless)
    {
        g_fDoGC = true;
        DoGenerationalGC(4);
        if (g_UseMultithreadedGC)
        {
            while (g_ObjectGCcleanframe < g_ObjectGCbuildframe) {}
            ProcessObjectDisposeList();
            ResetObjectGCList();
        }
    }

    g_fDoGC = doGc;

    if (!g_ReStart)
    {
        if (g_TimePeriodSet)
        {
            timeEndPeriod(g_TimeCurrentPeriod);
            g_TimePeriodSet = false;
            YYInfo("Unsetting previous scheduler resolution of %d\n", g_TimeCurrentPeriod);
            g_SleepMargin = g_OriginalSleepMargin;
        }
        return g_ReturnCode;
    }

    while (g_ReStart)
    {
        g_ReStart = false;
        // This loop matches the restart behavior seen in the decompilation.
        continue;
    }

    return g_ReturnCode;
}

