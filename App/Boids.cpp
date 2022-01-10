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

    assets->loadMaterial("resources/textures/blue_painted_planks", "_1k");
    assets->loadMaterial("resources/textures/white_rough_plaster", "_1k");
    assets->loadMaterial("resources/textures/denmin_fabric_02", "_1k");
    //assets->loadMaterial("resources/textures/denmin_fabric_02", "_2k");

    // Box size
    float BoxSize = 50;
    float halfBox = BoxSize / 2.0;

    scene.addLight("light1", {1000, 200, 200}, {5, 2, -1});
    scene.addLight("light3", {10000, 10000, 10000}, {0, BoxSize, 0});

    scene.addObject("ground", 3, 1);
    scene.setScale("ground", 5.0f);

    for (int i = 0; i < 8; i++)
    {
        float x = 1;
        float y = 1;
        float z = 1;

        scene.addObject("sphere" + std::to_string(i), 2, 0);
        x = pow(-1, i % 2);
        y = pow(-1, (i / 2) % 2);
        z = pow(-1, (i / 4) % 2);
        scene.setPosition("sphere" + std::to_string(i), {x * halfBox, y * halfBox, z * halfBox});
    }

    scene.addObject("sphereExtra", 2, 3);
    scene.setPosition("sphereExtra", {3.0, 2.0, 0.0});

    scene.addObject("sphereExtra2", 2, 2);
    scene.setPosition("sphereExtra2", {-3.0, 2.0, 0.0});

    while (!glfwWindowShouldClose(window))
    {
        // Real loop ------------------------------------------------------------------------------------------

        // Define a cor de fundo da janela
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        // Limpa algum buffer específico
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (clock.tick())
        {

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