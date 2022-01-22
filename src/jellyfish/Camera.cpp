#include <jellyfish/Jellyfish3D.hpp>

void Camera::reactToInput(GLFWwindow *window)
{
    m_userControl.observeInputs(window);
    float walkSpeed = 0.15;
    if (m_userControl.m_inputs["camaccel"])
        walkSpeed = 0.7;

    if (m_userControl.m_inputs["camright"])
    {
        transform.position = transform.position + walkSpeed * glm::normalize(glm::cross(m_orientation, Up));
    }
    if (m_userControl.m_inputs["camleft"])
    {
        transform.position = transform.position - walkSpeed * glm::normalize(glm::cross(m_orientation, Up)); //glm::vec3(-walkSpeed, 0.0f, 0.0f));
    }

    if (m_userControl.m_inputs["camfront"])
    {
        transform.position = transform.position + walkSpeed * m_orientation;
    }
    if (m_userControl.m_inputs["camback"])
    {
        transform.position = transform.position - walkSpeed * m_orientation;
    }

    if (m_userControl.m_inputs["camup"])
    {
        transform.position = transform.position + walkSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if (m_userControl.m_inputs["camdown"])
    {
        transform.position = transform.position - walkSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    }

    m_rotatingCooldown.tick();
    if (m_userControl.m_inputs["camrot"] && m_rotatingCooldown.isUp())
    {
        isRotating = !isRotating;
        m_rotatingCooldown.reset();
    }

    if (isRotating)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees
        float sensitivity = 100.0f;
        double mouseX = m_userControl.m_mouseX;
        double mouseY = m_userControl.m_mouseY;

        float rotX = sensitivity * (float)(mouseY - (HEIGHT / 2)) / HEIGHT;
        float rotY = sensitivity * (float)(mouseX - (WIDTH / 2)) / WIDTH;

        glm::vec3 newOrientation = m_orientation;

        // Sets the maximum speed of the camera turn verticaly
        if (fabs(rotX) >= 5)
            rotX = rotX * 5 / fabs(rotX);

        if (glm::angle(m_orientation, Up) <= glm::radians(174.0f) && glm::angle(m_orientation, Up) >= glm::radians(6.0f))
        {
            // Calculates upcoming vertical change in the Orientation
            newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), glm::normalize(m_cameraRight));
        }
        else
        {
            rotX = rotX / fabs(rotX);
            newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), glm::normalize(m_cameraRight));
        }

        // Checks if the Orientation and the up vector are not to close
        //if (glm::length(newOrientation - Up) >= 1.001 && glm::length(newOrientation + Up) >= 1.001)
        if (glm::angle(newOrientation, Up) <= glm::radians(179.0f) && glm::angle(newOrientation, Up) >= glm::radians(1.0f))
        {
            m_orientation = newOrientation;
        }

        // Rotates the Orientation left and right
        m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), Up);
        m_cameraRight = glm::rotate(m_cameraRight, glm::radians(-rotY), Up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    m_userControl.resetState();
}

glm::mat4 Camera::getViewMatrix()
{
    // Initializes matrices since otherwise they will be the null matrix
    glm::vec3 orientation = m_orientation;

    orientation = glm::rotateX(orientation, glm::radians(transform.rotation.x));
    orientation = glm::rotateY(orientation, glm::radians(transform.rotation.y));
    orientation = glm::rotateZ(orientation, glm::radians(transform.rotation.z));

    // Makes camera look in the right direction from the right position
    return glm::lookAt(transform.position, transform.position + m_orientation, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(m_FOV), (float)WIDTH / HEIGHT, m_nearPlane, m_farPlane);
}