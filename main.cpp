#include <jellyfish\Jellyfish3D.hpp>

// Global
// Window size
unsigned int WIDTH = 1600; //1280;
unsigned int HEIGHT = 900; //720;

Resources *assets;

int main()
{

    Display display;
    Clock clock;

    // When using opengl
    // Resources
    Resources res_aux;
    assets = &res_aux;

    GLFWwindow *window = display.getWindow();

    assets->loadMesh("resources/ground.obj");
    assets->loadMesh("resources/caesar.obj");
    assets->loadMesh("resources/suzanne.obj");
    assets->loadMesh("resources/ship.obj");

    assets->loadMaterial("resources/ground.png");
    assets->loadMaterial("resources/caesar.png");
    assets->loadMaterial("resources/hitbox.png");
    assets->loadMaterial("resources/ship.png");

    Renderer renderer;
    Scene scene;

    // Name, Mesh ID, Material ID
    scene.addObject("ground", 1, 1);
    scene.addObject("cube", 0, 0);
    scene.addObject("caesar", 2, 2);
    scene.addObject("suzanne", 3, 0);
    scene.addObject("ship", 4, 4);

    scene.setPosition("ground", {0.0f, -2.0f, 0.0f});
    scene.setPosition("caesar", {2.0f, 0.0f, 0.0f});
    scene.setPosition("suzanne", {-2.0f, 0.0f, 0.0f});
    scene.setPosition("ship", {4.0f, 0.0f, 0.0f});

    scene.setScale("ship", 0.5f);

    while (!glfwWindowShouldClose(window))
    {
        // Real loop ------------------------------------------------------------------------------------------

        // Define a cor de fundo da janela
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        // Limpa algum buffer específico
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (clock.tick())
        {
            // testing transforms
            scene.setRotation("ship", glm::vec3(scene.getRotation("ship").x + 1.0f, scene.getRotation("ship").y + 0.5f, scene.getRotation("ship").z));
            scene.setScale("suzanne", fabs(glm::cos(glfwGetTime())));
            scene.setPosition("cube", {4 * glm::sin(glfwGetTime()), 4 * glm::cos(glfwGetTime()), 0.0f});

            // TODO Find a better way to do this
            scene.m_object[0].reactToInput(window);

            scene.getActiveCam()->reactToInput(window);
        }

        renderer.draw(scene);

        // Faz a troca do framebuffer antigo para o novo (double buffer)
        glfwSwapBuffers(window);

        // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)
        glfwPollEvents();
    }

    return 0;
}