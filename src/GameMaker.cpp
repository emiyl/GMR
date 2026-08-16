#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>

#include "GameMaker.h"
#include "MemoryManager.h"
#include "Graphics_Perf.h"
#include "globals.h"

int GraphicsPerf::ms_DisplayFlags = 0;
int GraphicsPerf::ms_MinimisedFlags = 0;

bool DebugMode = false;
bool ExtDisabled = false;
bool option_displayerrors = true;

enum class WallpaperDisplayMode
{
    Main,
    Monitor,
    Span
};

WallpaperDisplayMode g_WallpaperDisplayMode = WallpaperDisplayMode::Main;

static void YYError(const char* message)
{
    (void)message;
}

static void CopyToken(const char* src, char* dst, std::size_t dstSize)
{
    if (dst == nullptr || dstSize == 0)
        return;

    std::size_t i = 0;
    while (src[i] != '\0' && i + 1 < dstSize)
    {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

static const char* SkipWhitespace(const char* text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r' || *text == '\n')
        ++text;
    return text;
}

static bool MatchOption(const char* arg, const char* option)
{
    return std::strcmp(arg, option) == 0;
}

static char* DuplicateString(const char* src)
{
    if (src == nullptr)
        return nullptr;

    const std::size_t length = std::strlen(src) + 1u;
    char* copy = static_cast<char*>(std::malloc(length));
    if (copy != nullptr)
        std::memcpy(copy, src, length);
    return copy;
}

void ProcessCommandLine(char* param_1)
{
    if (param_1 == nullptr)
    {
        g_fInAWindow = false;
        ExtDisabled = false;
        g_IO_Record = false;
        g_IO_Playback = false;
        g_fNoAudio = false;
        g_fVMUse = true;
        GraphicsPerf::ms_DisplayFlags = 0;
        DebugMode = false;
        return;
    }

    g_fVMUse = true;
    GraphicsPerf::ms_DisplayFlags = 0;
    DebugMode = false;
    ExtDisabled = false;
    g_IO_Record = false;
    g_IO_Playback = false;
    g_fNoAudio = false;
    g_fInAWindow = false;

    const char* cursor = SkipWhitespace(param_1);
    while (*cursor != '\0')
    {
        const char* argStart = cursor;
        while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
            ++cursor;

        const std::size_t argLen = static_cast<std::size_t>(cursor - argStart);
        if (argLen >= sizeof(g_CmdBuffer))
            break;

        CopyToken(argStart, g_CmdBuffer, sizeof(g_CmdBuffer));

        if (MatchOption(g_CmdBuffer, "-debug"))
        {
            g_fVMDebug = true;
        }
        else if (MatchOption(g_CmdBuffer, "-trace"))
        {
            g_fVMTrace = true;
        }
        else if (MatchOption(g_CmdBuffer, "-displayerrors"))
        {
            option_displayerrors = false;
        }
        else if (MatchOption(g_CmdBuffer, "-vmuse"))
        {
            g_fVMUse = false;
        }
        else if (MatchOption(g_CmdBuffer, "-noaudio"))
        {
            g_fNoAudio = true;
        }
        else if (MatchOption(g_CmdBuffer, "-window"))
        {
            g_fInAWindow = true;
        }
        else if (MatchOption(g_CmdBuffer, "-minidump"))
        {
            g_fCreateMiniDump = true;
            g_fFullMiniDump = false;
        }
        else if (MatchOption(g_CmdBuffer, "-fullminidump"))
        {
            g_fCreateMiniDump = true;
            g_fFullMiniDump = true;
        }
        else if (MatchOption(g_CmdBuffer, "-debugoutput"))
        {
            g_OutputDebugOutput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-extdisabled"))
        {
            ExtDisabled = true;
        }
        else if (MatchOption(g_CmdBuffer, "-game"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pGameName != nullptr)
                {
                    std::free(g_pGameName);
                    g_pGameName = nullptr;
                }
                g_pGameName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-exitgame"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pExitGame_CMD != nullptr)
                {
                    std::free(g_pExitGame_CMD);
                    g_pExitGame_CMD = nullptr;
                }
                g_pExitGame_CMD = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-yydebugpath"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pYYDebugPath != nullptr)
                {
                    std::free(g_pYYDebugPath);
                    g_pYYDebugPath = nullptr;
                }
                g_pYYDebugPath = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-exitdir"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pExitDir_CMD != nullptr)
                {
                    std::free(g_pExitDir_CMD);
                    g_pExitDir_CMD = nullptr;
                }
                g_pExitDir_CMD = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-io_record"))
        {
            g_IO_Record = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pIO_RecordFileName != nullptr)
                {
                    std::free(g_pIO_RecordFileName);
                    g_pIO_RecordFileName = nullptr;
                }
                g_pIO_RecordFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-steam"))
        {
            g_SteamWorkshop = true;
        }
        else if (MatchOption(g_CmdBuffer, "-fullscreen"))
        {
            GraphicsPerf::ms_DisplayFlags |= 0x40000010;
        }
        else if (MatchOption(g_CmdBuffer, "-debugnetwork"))
        {
            g_DebugNetworkOutput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-playback"))
        {
            g_IO_Playback = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pIO_RecordFileName != nullptr)
                {
                    std::free(g_pIO_RecordFileName);
                    g_pIO_RecordFileName = nullptr;
                }
                g_pIO_RecordFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-debugconsole"))
        {
            g_ConsoleOutput = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_DebugConsoleOutputFileName != nullptr)
                {
                    std::free(g_DebugConsoleOutputFileName);
                    g_DebugConsoleOutputFileName = nullptr;
                }
                g_DebugConsoleOutputFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-headless"))
        {
            g_fHeadless = true;
            g_fExitAfterFirstRoomCreationCode = true;
            g_fNoErrorWindow = true;
            g_fDisableWindow = true;
            g_fCreateMiniDump = true;
            g_fFullMiniDump = false;
            g_fDoGC = false;
        }
        else if (MatchOption(g_CmdBuffer, "-profile"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_ProfileDumpFileName != nullptr)
                {
                    std::free(g_ProfileDumpFileName);
                    g_ProfileDumpFileName = nullptr;
                }
                g_ProfileDumpFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
            const char* intervalStart = SkipWhitespace(cursor);
            if (*intervalStart != '\0')
            {
                g_ProfileDumpInterval = std::atoi(intervalStart);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-sleepmargin"))
        {
            const char* value = SkipWhitespace(cursor);
            if (*value != '\0')
            {
                g_SleepMargin = std::atoi(value);
                g_OverrideSleepMargin = true;
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-overridevbmethod"))
        {
            g_OverrideVBmethod = true;
        }
        else if (MatchOption(g_CmdBuffer, "-wallpaper"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (std::strcmp(next, "main") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Main;
                else if (std::strcmp(next, "monitor") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Monitor;
                else if (std::strcmp(next, "span") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Span;
                else if (std::strcmp(next, "monitor") == 0)
                    g_Monitor = std::atoi(next);

                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-manualvsync"))
        {
            g_ManualVSync = true;
        }
        else if (MatchOption(g_CmdBuffer, "-nodirectinput"))
        {
            g_NoDirectInput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-wallpaperon"))
        {
            g_fDoWallpaper = true;
        }
        else if (MatchOption(g_CmdBuffer, "-sethighpriority"))
        {
            g_bSetHighProcessPriority = false;
        }

        cursor = SkipWhitespace(cursor);
    }
}

