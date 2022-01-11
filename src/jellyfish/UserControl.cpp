#include <jellyfish\Jellyfish3D.hpp>

comp_UserControl::comp_UserControl()
{
    // ! bad bad ...
    // Test inputs "b" stads for box
    m_inputs["bleft"] = false;
    m_inputs["bright"] = false;
    m_inputs["bup"] = false;
    m_inputs["bdown"] = false;

    // Test camera imputs
    m_inputs["camleft"] = false;
    m_inputs["camright"] = false;
    m_inputs["camfront"] = false;
    m_inputs["camback"] = false;
    m_inputs["camup"] = false;
    m_inputs["camdown"] = false;
    m_inputs["camrot"] = false;
    m_inputs["camaccel"] = false;

    m_inputs["pause"] = false;
}

void comp_UserControl::observeInputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        m_inputs["camrot"] = true;
    }

    // Test cube
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_inputs["bleft"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_inputs["bright"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_inputs["bup"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_inputs["bdown"] = true;
    }

    // Cam
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_inputs["camright"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_inputs["camleft"] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_inputs["camfront"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_inputs["camback"] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_inputs["camup"] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        m_inputs["camdown"] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_inputs["camaccel"] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        m_inputs["pause"] = true;
    }
}

void comp_UserControl::resetState()
{
    for (auto &x : m_inputs)
    {
        x.second = false;
    }
}

void comp_UserControl::printInputs()
{
    for (const auto &[key, value] : m_inputs)
    {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}
