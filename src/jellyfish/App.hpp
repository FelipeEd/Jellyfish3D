#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App
{
private:
public:
    Display display;
    Resources assets;
    Clock clock;
    KeyStates inputs;

    double getTime()
    {
        return glfwGetTime();
    }

    // Runs once
    void OnStart() {}
    // locked by the framerate
    void PerFrame() {}
    // Run as fast as possible
    void PerLoop() {}
};