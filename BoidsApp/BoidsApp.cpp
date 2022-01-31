#include <jellyfish\Jellyfish3D.hpp>
#include "classes\Debug.h"
#include "classes\Boids.h"

// Global
// Window size
unsigned int WIDTH = 1980;  //1280;
unsigned int HEIGHT = 1080; //720;
bool pbr = true;

#define NUM_BOIDS 500

// -----------------------------------------------------------------------------------
int main()
{
    INIT_TIMER("Boids")

    App app;

    // When using opengl
    GLFWwindow *window = app.display.getWindow();
    Timer pauseCooldown(5);
    Timer addsubBoidsCooldown(5);

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
        app.assets.loadMesh("resources/newship.obj");
        app.assets.loadMesh("resources/tower.obj");
        app.assets.loadMesh("resources/leadership.obj");

        app.assets.loadMaterial("resources/textures/Silver_Worn", "_2k");
        //assets->loadMaterial("resources/textures/denmin_fabric_02", "_1k");
        app.assets.loadMaterial("resources/textures/blue_painted_planks", "_1k");
        //assets->loadMaterial("resources/textures/concrete_floor_02", "_1k");
        app.assets.loadMaterial("resources/textures/Gold_Worn", "_2k");
        app.assets.loadMaterial("resources/textures/floor_tiles_06", "_1k");
        app.assets.loadMaterial("resources/textures/Plastic_Glossy_red", "_2k");
    }

    {
        TIME_IT("Setup scene")
        // Box size
        float BoxSize = 50;
        float halfBox = BoxSize / 2.0;
        float halfBoxH = BoxSize / 4.0;

        scene.addLight("light1", glm::vec3(5000), {0, halfBoxH, 0});
        scene.addLight("light2", {1000, 1000, 100}, {10, -5, 10});
        scene.addLight("light3", {1000, 1000, 100}, {-10, -5, 10});
        scene.addLight("light4", {1000, 1000, 1000}, {0, -5, -10});

        scene.addObject("ground", 3, 4);
        scene.setPosition("ground", {0.0, -halfBoxH, 0.0});
        scene.setScale("ground", halfBox);

        scene.addObject("tower", 5, 3);
        scene.setScale("tower", halfBoxH / 1.8);

        scene.addObject("tower2", 5, 3);
        scene.setScale("tower2", halfBoxH / 1.8);
        scene.setPosition("tower2", glm::vec3(BoxSize / 3.0, 0.0, 0.0));

        scene.addObject("tower3", 5, 3);
        scene.setScale("tower3", halfBoxH / 1.8);
        scene.setPosition("tower3", glm::vec3(-BoxSize / 3.0, 0.0, 0.0));

        for (int i = 0; i < 8; i++)
        {
            float x = 1;
            float y = 1;
            float z = 1;

            scene.addObject("sphere" + std::to_string(i), 1, 0);
            x = pow(-1, i % 2);
            y = pow(-1, (i / 2) % 2);
            z = pow(-1, (i / 4) % 2);
            scene.setPosition("sphere" + std::to_string(i), {x * halfBox, y * halfBoxH, z * halfBox});
        }
    }

    int leaderBoidIndex = scene.m_object.size();
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
                // Inputs---------------------------------------------------------------------------------------------------
                app.inputs.observeInputs(window);
                //app.inputs.printInputs();
                scene.reactToInput(window, app.inputs);

                pauseCooldown.tick();
                if (app.inputs.keys["pause"] && pauseCooldown.isUp())
                {
                    pause = !pause;
                    pauseCooldown.reset();
                }
                // Camera management
                // Camera 0
                glm::vec3 avgVeldirection = glm::normalize(boids.getAvgVelocity() + glm::vec3(0.000001f, 0.000001f, 0.000001f));
                // Camera 1
                scene.m_cams[1].transform.position = glm::vec3(0.0, 0.0, 0.0);
                scene.m_cams[1].pointTo(boids.getAvgPos());

                // Camaera 2
                scene.m_cams[2].transform.position = boids.getAvgPos() - 20.0f * avgVeldirection;
                scene.m_cams[2].pointTo(boids.getAvgPos());

                // Camaera 2
                scene.m_cams[3].transform.position = boids.getAvgPos() + 20.0f * glm::vec3(-avgVeldirection.z, 0.0f, avgVeldirection.x);
                scene.m_cams[3].pointTo(boids.getAvgPos());

                // Boid control
                addsubBoidsCooldown.tick();
                if (app.inputs.keys["addboid"] && addsubBoidsCooldown.isUp())
                {
                    boids.addBoid();
                    addsubBoidsCooldown.reset();
                }

                if (app.inputs.keys["removeboid"] && addsubBoidsCooldown.isUp())
                {
                    boids.removeBoid();
                    addsubBoidsCooldown.reset();
                }

                //----------------------------------------------------------------------------------------------------------
                // User interface
                gui.text("Limits : ");
                gui.sliderFloat("View Radius", boids.m_viewRad, 0.5, 25.0);
                gui.sliderFloat("View FOV", boids.m_boidsFOV, 10.0f, 359.0);
                gui.sliderFloat("Max Speed", boids.m_maxSpeed, 0.001, 2.0);
                gui.sliderFloat("Max Accel", boids.m_maxAccel, 0.0001, 0.2);
                gui.text("Forces : ");
                gui.sliderFloat("Speed Multiplier", boids.m_speedMultiplier, 0.01, 3.0);
                gui.sliderFloat("Accel Multiplier", boids.m_accelMultiplier, 0.01, 3.0);
                gui.sliderFloat("Align factor", boids.A_fac, 0.001, 2.0);
                gui.sliderFloat("Cohesion factor", boids.C_fac, 0.001, 2.0);
                gui.sliderFloat("Separation factor", boids.S_fac, 0.001, 10.0);
                gui.sliderFloat("Follow factor", boids.F_fac, 0.000, 10.0);

                if (gui.button("Reset"))
                {
                    boids.reset();
                    scene.m_object[leaderBoidIndex].transform.position = glm::vec3(0.0f);
                }

                if (gui.button("Wireframe"))
                {
                    renderer.switchWireframeMode();
                }
                if (gui.button("Skybox"))
                    renderer.switchSkybox();

                float radius = 10.0f;
                float freq = 0.05f;
                if (!pause)
                {
                    {
                        //TIME_IT("Find Target")
                        //scene.setPosition("Target", {radius * glm::cos(glfwGetTime() * freq), 0.0f, radius * glm::sin(glfwGetTime() * freq)});
                        scene.m_object[leaderBoidIndex].reactToInput(window, app.inputs);

                        {
                            TIME_IT("Update Boids")
                            boids.updateAll();
                        }
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

            app.inputs.resetState();
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