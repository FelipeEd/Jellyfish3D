#pragma once

#include <iostream>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <string>

class GUI
{

public:
    GUI() {}
    ~GUI();

    void init(GLFWwindow *window);
    void startFrame(const std::string &windowName);
    void endFrame();

    void sliderFloat(const std::string &variableName, float &a, float min, float max);
    void sliderInt(const std::string &variableName, int &a, int min, int max);
    bool button(const std::string &buttonName);
    void text(const std::string &text);
    void checkbox(const std::string &label, bool &value);
    void separator();
    bool collapsingHeader(const std::string &label);
};
