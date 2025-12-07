#pragma once

// Must be used inside a function that runs inside the clock
class Timer
{
private:
    unsigned int m_alarm;
    unsigned int m_framesLeft;

public:
    // After this many frames it will wake up
    Timer(unsigned int alarm);
    bool isUp();
    void tick();
    void reset();
};