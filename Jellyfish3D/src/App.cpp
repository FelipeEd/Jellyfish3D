#include <App.hpp>
#include <GLFW/glfw3.h>

double App::getTime() const
{
    return glfwGetTime();
}

void App::Run()
{
    // Call OnStart once
    OnStart();

    // Main loop
    while (!display.shouldClose())
    {
        // Update inputs
        inputs.observeInputs();

        // Fixed timestep update (if clock ticked)
        if (clock.tick())
        {
            OnFixedUpdate();
        }

        // Per-frame update (always)
        OnUpdate();

        // Reset input state
        inputs.resetState();

        // Swap buffers and poll events
        display.swapBuffers();
        display.pollEvents();
    }

    // Call OnShutdown
    OnShutdown();
}
