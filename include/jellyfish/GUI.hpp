#pragma once

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

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
};
