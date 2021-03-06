#include <jellyfish\Jellyfish3D.hpp>

KeyStates::KeyStates()
{
    // ! bad bad ...
    // Test inputs "b" stads for box
    keys["shipleft"] = false;
    keys["shipright"] = false;
    keys["shipup"] = false;
    keys["shipdown"] = false;

    // Test camera imputs
    keys["camleft"] = false;
    keys["camright"] = false;
    keys["camfront"] = false;
    keys["camback"] = false;
    keys["camup"] = false;
    keys["camdown"] = false;
    keys["camrot"] = false;
    keys["camaccel"] = false;
    keys["addboid"] = false;
    keys["removeboid"] = false;

    keys["selectcam0"] = false;
    keys["selectcam1"] = false;
    keys["selectcam2"] = false;
    keys["selectcam3"] = false;

    keys["pause"] = false;
}

void KeyStates::observeInputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        keys["camrot"] = true;

    // Cam
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        keys["camright"] = true;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        keys["camleft"] = true;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        keys["camfront"] = true;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        keys["camback"] = true;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        keys["camup"] = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        keys["camdown"] = true;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        keys["camaccel"] = true;

    // Control App stte
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        keys["pause"] = true;
    // Boids control
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        keys["addboid"] = true;
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        keys["removeboid"] = true;

    //Select current camera
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        keys["selectcam0"] = true;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        keys["selectcam1"] = true;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        keys["selectcam2"] = true;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        keys["selectcam3"] = true;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        keys["shipleft"] = true;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        keys["shipright"] = true;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        keys["shipup"] = true;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        keys["shipdown"] = true;
}

void KeyStates::resetState()
{
    for (auto &x : keys)
    {
        x.second = false;
    }
}

void KeyStates::printInputs()
{
    for (const auto &[key, value] : keys)
    {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}
