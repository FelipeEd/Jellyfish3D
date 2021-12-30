#include <jellyfish\Jellyfish3D.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Global
// Window size
unsigned int WIDTH = 1600; //1280;
unsigned int HEIGHT = 900; //720;

Resources *assets;

int main()
{
    // inicialização e configuração de contexto
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // criação da janela e verificação de erros
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Jellyfish 3D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Falha na criacao da janela" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD: Carregamento dos ponteiros de funções para utilizar OpenGL moderno
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Falha na inicializacao do GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //-------------------------------------------------

    // Resources
    Resources res_aux;
    assets = &res_aux;

    Clock clock;
    Renderer renderer;
    Object test;
    Camera camera;

    while (!glfwWindowShouldClose(window))
    {
        // Real loop ------------------------------------------------------------------------------------------

        // Define a cor de fundo da janela
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // Limpa algum buffer específico
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (clock.tick())
        {
            test.m_transform.setRotation(glm::vec3(test.m_transform.getRotation().x + 1.0f, test.m_transform.getRotation().y + 0.5f, test.m_transform.getRotation().z));

            test.reactToInput(window);
            camera.reactToInput(window);
        }

        renderer.draw(test, camera);

        // Faz a troca do framebuffer antigo para o novo (double buffer)
        glfwSwapBuffers(window);

        // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)
        glfwPollEvents();
    }

    // Desalocar memória dos objetos instanciados
    glfwTerminate(); // Faz a limpeza dos recursos utilizados pelo GLFW
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
    }
}

// Called everytime the window is resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{

    glViewport(0, 0, width, height);
}
