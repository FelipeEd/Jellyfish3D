#pragma once

#include <GLFW/glfw3.h>

#include "Display.hpp"
#include "Resources.hpp"
#include "Clock.hpp"
#include "KeyStates.hpp"

class App
{
private:
    std::string m_name;

public:
    Display display;
    Resources assets;
    Clock clock;
    KeyStates inputs;

    App(const std::string name)
    {
        m_name = name;
        assets.set_path(name);
    }

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