#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
