#include <raylib.h>

typedef struct timer_s {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} timer_s;

void timer_start(timer_s *timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool timer_done(timer_s timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double timer_elapsed(timer_s timer)
{
    return GetTime() - timer.startTime;
}