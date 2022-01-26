#include <jellyfish\Jellyfish3D.hpp>
#include "classes\Debug.h"
#include "classes\Boids.h"

// Global
// Window size
unsigned int WIDTH = 1280; //1280;
unsigned int HEIGHT = 720; //720;
bool pbr = true;

#define NUM_BOIDS 600

// -----------------------------------------------------------------------------------
int main()
{
    INIT_TIMER("Boids")

    App app;

    // When using opengl
    GLFWwindow *window = app.display.getWindow();
    Timer pauseCooldown(10);
    GUI gui;
    gui.init(window);

    Renderer renderer;
    Scene scene;

    bool pause = false;
    {
        TIME_IT("Load Assets")
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
    }

    {
        TIME_IT("Setup scene")
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
    }

    Boids boids = Boids(scene.m_object.size(), NUM_BOIDS, scene);

    while (!glfwWindowShouldClose(window))
    {

        TIME_IT("Whole loop")

        {
            TIME_IT("Clear Buffers")

            // Define a cor de fundo da janela
            glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
            // Limpa algum buffer específico
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        {
            TIME_IT("Clock tick")

            gui.startFrame("Boid Parameters");

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

                gui.text("Limits : ");
                gui.sliderFloat("View Radius", boids.m_viewRad, 0.5, 25.0);
                gui.sliderFloat("Max Speed", boids.m_maxSpeed, 0.001, 2.0);
                gui.sliderFloat("Max Accel", boids.m_maxAccel, 0.0001, 0.2);
                gui.text("Forces : ");
                gui.sliderFloat("Speed Multiplier", boids.m_speedMultiplier, 0.01, 3.0);
                gui.sliderFloat("Speed Accel", boids.m_accelMultiplier, 0.01, 3.0);
                gui.sliderFloat("Align factor", boids.A_fac, 0.001, 2.0);
                gui.sliderFloat("Cohesion factor", boids.C_fac, 0.001, 2.0);
                gui.sliderFloat("Separation factor", boids.S_fac, 0.001, 10.0);
                gui.sliderFloat("Follow factor", boids.F_fac, 0.000, 10.0);

                if (gui.button("Reset"))
                    boids.reset();

                if (gui.button("Wireframe"))
                {
                    renderer.switchWireframeMode();
                }
                if (gui.button("Skybox"))
                    renderer.switchSkybox();
                float radius = 10.0f;
                float freq = 0.5f;
                {
                    TIME_IT("Find Target")
                    scene.setPosition("Target", {radius * glm::cos(glfwGetTime() * freq), 0.0f, radius * glm::sin(glfwGetTime() * freq)});
                }
                {
                    TIME_IT("Update Boids")

                    if (!pause)
                    {
                        boids.updateAll();
                    }
                }
            }
        }

        {
            TIME_IT("Draw calls");

            renderer.draw(scene, app);
        }

        {
            TIME_IT("Swap Buffers");

            gui.endFrame();
            // Faz a troca do framebuffer antigo para o novo (double buffer)
            glfwSwapBuffers(window);
            glFlush();
        }

        // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)
        glfwPollEvents();
    }

    END_TIMER

    return 0;
}