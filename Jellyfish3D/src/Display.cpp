#include <Display.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

// Called everytime the window is resized
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

Display::Display()
{
    // inicialização e configuração de contexto
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //  MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);
    // criação da janela e verificação de erros
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Jellyfish 3D", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Falha na criacao da janela" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // GLAD: Carregamento dos ponteiros de funções para utilizar OpenGL moderno
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Falha na inicializacao do GLAD" << std::endl;
        glfwTerminate();
    }

    glfwSwapInterval(1);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glEnable(GL_FRAMEBUFFER_SRGB);
}

Display::~Display()
{
    // printf("Destroing Display");
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void Display::processInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
    }

    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
    }

    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
    }

    if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
    {
    }
}

bool Display::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Display::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Display::pollEvents()
{
    glfwPollEvents();
}

void Display::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Display::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::clearColor()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::clearDepth()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Display::flush()
{
    glFlush();
}
