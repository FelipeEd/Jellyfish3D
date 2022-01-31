#pragma once

#include "Objects.hpp"
#include "KeyStates.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

class Ship : public Object
{
public:
    void reactToInput(GLFWwindow *window, KeyStates inputs);
};