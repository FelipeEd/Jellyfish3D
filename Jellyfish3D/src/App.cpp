#include <App.hpp>
#include <GLFW/glfw3.h>

double App::getTime() const
{
    return glfwGetTime();
}
