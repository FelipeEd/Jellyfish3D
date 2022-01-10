#include <jellyfish\Jellyfish3D.hpp>

// Global
// Window size
unsigned int WIDTH = 1600; //1280;
unsigned int HEIGHT = 900; //720;
bool pbr = true;

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

    Renderer renderer;

    Scene scene;

    // light model
    assets->loadMesh("resources/simplesphere.obj");
    assets->loadMesh("resources/uvsphere.obj");
    assets->loadMesh("resources/plane.obj");
    assets->loadMesh("resources/suzanne.obj");

    assets->loadMaterial("resources/textures/blue_painted_planks", "_1k");
    assets->loadMaterial("resources/textures/white_rough_plaster", "_1k");
    assets->loadMaterial("resources/textures/denmin_fabric_02", "_1k");
    //assets->loadMaterial("resources/textures/denmin_fabric_02", "_2k");

    scene.addLight("light1", {1000, 200, 200}, {5, 2, -1});
    scene.addLight("light3", {1000, 1000, 1000}, {0, 10, 0});

    scene.addObject("ground", 3, 1);
    scene.setScale("ground", 5.0f);

    scene.addObject("sphere", 2, 3);
    scene.setPosition("sphere", {3.0, 2.0, 0.0});

    scene.addObject("sphere2", 2, 0);
    scene.setPosition("sphere2", {-3.0, 2.0, 0.0});

    scene.addObject("suzanne", 4, 2);
    scene.setPosition("suzanne", {0.0, 2.0, 0.0});

    while (!glfwWindowShouldClose(window))
    {
        // Real loop ------------------------------------------------------------------------------------------

        // Define a cor de fundo da janela
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        // Limpa algum buffer específico
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (clock.tick())
        {
            scene.setRotation("suzanne", scene.getRotation("suzanne") + glm::vec3(0.0, 0.3, 0.0));
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