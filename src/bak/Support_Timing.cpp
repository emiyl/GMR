#include <atomic>

struct GameTimer
{
    std::atomic<int64_t> elapsed_micros;
    std::atomic<double>  fps;
    std::atomic<int64_t> last_micros;
    std::atomic<int64_t> delta_micros;
    std::atomic<bool>    fixed_tick;
    bool                 paused;
};

long long Timing_Time();

GameTimer g_GameTimer;

class CTimingSource
{
public:
    double GetFPS()
    {
        if (g_GameTimer.fps > 0.0 && g_GameTimer.fixed_tick)
            return g_GameTimer.fps;

        if (g_GameTimer.delta_micros > 0)
            return 1000000.0 / static_cast<double>(g_GameTimer.delta_micros);

        return 30.0;
    }

    void SetFrameRate(double fps)
    {
        g_GameTimer.elapsed_micros = 0;
        g_GameTimer.fps = fps;

        int64_t lastMicros = 0;
        if (fps > 0.0)
            lastMicros = Timing_Time();

        g_GameTimer.last_micros = lastMicros;
        g_GameTimer.delta_micros = 0;
        g_GameTimer.paused = false;
    }
};