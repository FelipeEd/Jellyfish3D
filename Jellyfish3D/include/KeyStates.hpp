#pragma once

#include <iostream>
#include <map>
#include <string>

// Forward declaration to hide GLFW
struct GLFWwindow;

class KeyStates
{
private:
    GLFWwindow *m_window;

public:
    double m_mouseX;
    double m_mouseY;

    double m_oldMouseX;
    double m_oldMouseY;

    std::map<std::string, bool> keys;

    KeyStates();
    ~KeyStates(){};

    void setWindow(GLFWwindow *window) { m_window = window; }
    void observeInputs();
    void resetState();

    void printInputs();
};