#include <jellyfish\Jellyfish3D.hpp>
#include "classes\Boids.h"

// Global
// Window size
unsigned int WIDTH = 1280; //1280;
unsigned int HEIGHT = 720; //720;
bool pbr = true;
bool debug = false; //if(debug)

// -----------------------------------------------------------------------------------
int main()
{
    App app;

    // When using opengl
    GLFWwindow *window = app.display.getWindow();
    Timer pauseCooldown(10);
    GUI gui;
    gui.init(window);

    Renderer renderer;
    Scene scene;

    bool pause = false;

    // light model
    app.assets.loadMesh("resources/simplesphere.obj");
    app.assets.loadMesh("resources/uvsphere.obj");
    app.assets.loadMesh("resources/plane.obj");
    app.assets.loadMesh("resources/test_ship.obj");

    app.assets.loadMaterial("resources/textures/test_ship", "_1k");
    //assets->loadMaterial("resources/textures/denmin_fabric_02", "_1k");
    app.assets.loadMaterial("resources/textures/blue_painted_planks", "_1k");
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

    Boids boids = Boids(scene.m_object.size(), 1000, scene);

    if (debug)
        Instrumentor::Get().BeginSession("Main Loop"); // Begin session
    {

        while (!glfwWindowShouldClose(window))
        {
            if (debug)
                InstrumentationTimer timer("Whole loop");

            // Define a cor de fundo da janela
            glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
            // Limpa algum buffer específico
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            gui.startFrame("Boid Parameters");

            {
                if (debug)
                    InstrumentationTimer timer("Clock tick");

                if (app.clock.tick())
                {

                    scene.getActiveCam()->reactToInput(window);

                    app.inputs.observeInputs(window);
                    pauseCooldown.tick();
                    if (app.inputs.m_inputs["pause"] && pauseCooldown.isUp())
                    {
                        pause = !pause;
                        pauseCooldown.reset();
                    }
                    app.inputs.m_inputs["pause"] = false;

                    //gui.sliderFloat()

                    {
                        if (debug)
                            InstrumentationTimer timer("Update Boids");

                        if (!pause)
                        {
                            boids.updateAll();
                        }
                    }
                }
            }

            {
                if (debug)
                    InstrumentationTimer timer("Draw calls");

                renderer.draw(scene, app);
            }
            {
                if (debug)
                    InstrumentationTimer timer("Swap Buffers");

                gui.endFrame();
                // Faz a troca do framebuffer antigo para o novo (double buffer)
                glfwSwapBuffers(window);
                glFlush();
            }

            // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)
            glfwPollEvents();
        }
    }
    if (debug)
        Instrumentor::Get().EndSession();

    return 0;
}