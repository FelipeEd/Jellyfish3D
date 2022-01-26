#pragma once
#include <jellyfish\Jellyfish3D.hpp>

// Should be used when limiting function calls by framerate
class Clock
{
private:
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    double tickSpeed = 1 / 60; // ! 30 times per second !

public:
    Clock();
    ~Clock(){};

    bool tick();
};