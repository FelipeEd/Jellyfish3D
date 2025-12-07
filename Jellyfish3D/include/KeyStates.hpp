#pragma once

#include <iostream>
#include <map>
#include <string>

#include <GLFW/glfw3.h>

class KeyStates
{
public:
    double m_mouseX;
    double m_mouseY;

    double m_oldMouseX;
    double m_oldMouseY;

    std::map<std::string, bool> keys;

    KeyStates();
    ~KeyStates(){};

    void observeInputs(GLFWwindow *window);
    void resetState();

    void printInputs();
};