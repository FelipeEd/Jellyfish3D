#include <Clock.hpp>

Clock::Clock()
{
    crntTime = prevTime = glfwGetTime();
    timeDiff = 0;
    lastFrameTime = glfwGetTime();
    deltaTime = 0.0;
}

bool Clock::tick()
{
    crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;

    if (timeDiff >= tickSpeed)
    {
        prevTime = crntTime;
        return true;
    }
    else
        return false;
}

void Clock::updateDeltaTime()
{
    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
}

/*if (timeDiff >= 1.0 / 120.0)
    {

        std::string FPS = std::to_string((1.0 / timeDiff) * counter);
        std::string ms = std::to_string((timeDiff / counter) * 1000);
        std::string newTitle = "N A V - " + FPS + "FPS /" + ms + "ms";
        glfwSetWindowTitle(window, newTitle.c_str());
        prevTime = crntTime;
        counter = 0;
    }
*/
