#pragma once

class App
{
private:
public:
    Display display;
    Resources assets;
    Clock clock;
    comp_UserControl inputs;

    // Runs once
    void OnStart() {}
    // locked by the framerate
    void PerFrame() {}
    // Run as fast as possible
    void PerLoop() {}
};