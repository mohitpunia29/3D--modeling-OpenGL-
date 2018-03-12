#ifndef TIMER_H
#define TIMER_H

#include<time.h>

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        clock_t startedAt;
        clock_t pausedAt;
        bool started;
        bool paused;

        bool isStarted();
        bool isStopped();
        bool isPaused();

        void Pause();

        void Resume();
        void Stop();
        void Start();
        void Reset();

        clock_t GetTicks();


    protected:

    private:
};

#endif // TIMER_H
