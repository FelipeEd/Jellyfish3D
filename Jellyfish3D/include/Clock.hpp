#pragma once

#include <GLFW/glfw3.h>

// Should be used when limiting function calls by framerate
class Clock
{
private:
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    double tickSpeed = 1 / 60; // ! 30 times per second !
    double lastFrameTime = 0.0;
    double deltaTime = 0.0;

public:
    Clock();
    ~Clock(){};

    bool tick();
    void updateDeltaTime();
    double getDeltaTime() const { return deltaTime; }
};