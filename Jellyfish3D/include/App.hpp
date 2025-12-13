#pragma once

#include <Display.hpp>
#include <Resources.hpp>
#include <Clock.hpp>
#include <KeyStates.hpp>

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
        inputs.setWindow(display.getWindow());
    }
    virtual ~App() = default;

    double getTime() const;

    // Lifecycle methods - override these in your application
    virtual void OnStart() {}        // Called once at startup
    virtual void OnUpdate() {}       // Called every frame (frame-rate locked)
    virtual void OnFixedUpdate() {}  // Called every fixed timestep
    virtual void OnShutdown() {}     // Called before application closes

    // Main loop - call this to run your application
    void Run();
};