#pragma once

#include <GLFW/glfw3.h>

// #include "AuxFunctions.hpp"

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

// For now handles opengl init stuff
class Display
{
private:
    GLFWwindow *m_window;
    void processInput(GLFWwindow *window);

public:
    Display();
    ~Display();

    GLFWwindow *getWindow() { return m_window; }
};
