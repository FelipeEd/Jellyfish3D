#include <jellyfish\Jellyfish3D.hpp>
#include "classes\Boids.h"

// Global
// Window size
unsigned int WIDTH = 1280; //1280;
unsigned int HEIGHT = 720; //720;
bool pbr = true;

Resources *assets;

// -----------------------------------------------------------------------------------
int main()
{
    Display display;
    comp_UserControl inputControl;

    Clock clock;
    Timer pauseCooldown(10);
    // Resources
    Resources res_aux;
    assets = &res_aux;
    // When using opengl
    GLFWwindow *window = display.getWindow();
    Renderer renderer;
    Scene scene;
    bool pause = false;

    // light model
    assets->loadMesh("resources/simplesphere.obj");
    assets->loadMesh("resources/uvsphere.obj");
    assets->loadMesh("resources/plane.obj");
    assets->loadMesh("resources/test_ship.obj");

    assets->loadMaterial("resources/textures/test_ship", "_1k");
    //assets->loadMaterial("resources/textures/denmin_fabric_02", "_1k");
    assets->loadMaterial("resources/textures/blue_painted_planks", "_1k");
    //assets->loadMaterial("resources/textures/concrete_floor_02", "_1k");
    //assets->loadMaterial("resources/textures/square_floor", "_1k");

    // Box size
    float BoxSize = 50;
    float halfBox = BoxSize / 2.0;

    scene.addLight("light1", glm::vec3(5000), {0, halfBox, 0});
    scene.addLight("light2", {1000, 1000, 100}, {10, 0, 10});
    scene.addLight("light3", {1000, 1000, 100}, {-10, 0, 10});
    scene.addLight("light4", {1000, 1000, 1000}, {0, 0, -10});

    scene.addObject("ground", 3, 2);
    scene.setPosition("ground", {0.0, -halfBox, 0.0});
    scene.setScale("ground", halfBox);

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

    Boids boids = Boids(scene.m_object.size(), 10000, scene);

    Instrumentor::Get().BeginSession("Main Loop"); // Begin session
    {

        while (!glfwWindowShouldClose(window))
        {
            InstrumentationTimer timer("Whole loop");
            // Real loop ------------------------------------------------------------------------------------------
            auto start = high_resolution_clock::now();
            // Define a cor de fundo da janela

            glClearColor(0.005f, 0.005f, 0.009f, 1.0f);
            // Limpa algum buffer específico
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            {
                InstrumentationTimer timer("Clock tick");
                if (clock.tick())
                {

                    scene.getActiveCam()->reactToInput(window);

                    inputControl.observeInputs(window);
                    pauseCooldown.tick();
                    if (inputControl.m_inputs["pause"] && pauseCooldown.isUp())
                    {
                        pause = !pause;
                        pauseCooldown.reset();
                    }
                    inputControl.m_inputs["pause"] = false;

                    {
                        InstrumentationTimer timer("Update Boids");
                        auto startboid = high_resolution_clock::now();
                        if (!pause)
                        {
                            boids.updateAll();
                        }
                        auto stopboid = high_resolution_clock::now();

                        auto duration = duration_cast<microseconds>(stopboid - startboid);
                        std::cout << "Times:\n Boid: "
                                  << duration.count() / 1000000.0 << " s ";
                    }
                }
            }
            {
                InstrumentationTimer timer("Draw calls");
                auto startdraw = high_resolution_clock::now();
                renderer.draw(scene);
                auto stopdraw = high_resolution_clock::now();
                auto drawduration = duration_cast<microseconds>(stopdraw - startdraw);
                std::cout << "Draw: "
                          << drawduration.count() / 1000000.0 << " s ";
            }
            {
                InstrumentationTimer timer("Swap Buffers");
                // Faz a troca do framebuffer antigo para o novo (double buffer)
                glfwSwapBuffers(window);
            }
            // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)

            glfwPollEvents();

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            std::cout << "Total: "
                      << duration.count() / 1000000.0 << " s " << std::endl;
        }
    }
    Instrumentor::Get().EndSession();
    return 0;
}