#include <Jellyfish3D.hpp>
#include <memory>
#include "Debug.h"
#include "Boids.h"

// Global
// Window size
unsigned int WIDTH = 1980;  // 1280;
unsigned int HEIGHT = 1080; // 720;

#define NUM_BOIDS 500

// -----------------------------------------------------------------------------------
class BoidsApp : public App
{
private:
    GUI gui;
    Renderer renderer;
    Scene scene;
    std::unique_ptr<Boids> boids;
    
    Timer pauseCooldown;
    Timer addsubBoidsCooldown;
    
    bool pause = false;
    int leaderBoidIndex = 0;
    
    // Box dimensions
    float BoxSize = 50.0f;
    float halfBox = BoxSize / 2.0f;
    float halfBoxH = BoxSize / 4.0f;

public:
    BoidsApp() : App("Examples/Boids/"),
                 renderer(RenderMode::PBR),
                 pauseCooldown(5),
                 addsubBoidsCooldown(5)
    {
    }

    void OnStart() override
    {
        INIT_TIMER("Boids")
        
        gui.init(display.getWindow());

        {
            TIME_IT("Load Assets")
            // light model
            assets.loadMesh("resources/simplesphere.obj");
            assets.loadMesh("resources/uvsphere.obj");
            assets.loadMesh("resources/plane.obj");
            assets.loadMesh("resources/newship.obj");
            assets.loadMesh("resources/tower.obj");
            assets.loadMesh("resources/leadership.obj");

            assets.loadMaterial("resources/textures/Silver_Worn", "_2k");
            assets.loadMaterial("resources/textures/blue_painted_planks", "_1k");
            assets.loadMaterial("resources/textures/Gold_Worn", "_2k");
            assets.loadMaterial("resources/textures/floor_tiles_06", "_1k");
            assets.loadMaterial("resources/textures/Plastic_Glossy_red", "_2k");
        }

        {
            TIME_IT("Setup scene")
            
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

        leaderBoidIndex = scene.m_object.size();
        boids = std::make_unique<Boids>(scene.m_object.size(), NUM_BOIDS, scene);
    }

    void OnFixedUpdate() override
    {
        TIME_IT("Clock tick")
        
        // Inputs
        scene.reactToInput(inputs);

        pauseCooldown.tick();
        if (inputs.keys["pause"] && pauseCooldown.isUp())
        {
            pause = !pause;
            pauseCooldown.reset();
        }
        
        // Camera management
        glm::vec3 avgVeldirection = glm::normalize(boids->getAvgVelocity() + glm::vec3(0.000001f, 0.000001f, 0.000001f));
        
        // Camera 1
        scene.m_cams[1].transform.position = glm::vec3(0.0, 0.0, 0.0);
        scene.m_cams[1].pointTo(boids->getAvgPos());

        // Camera 2
        scene.m_cams[2].transform.position = boids->getAvgPos() - 20.0f * avgVeldirection;
        scene.m_cams[2].pointTo(boids->getAvgPos());

        // Camera 3
        scene.m_cams[3].transform.position = boids->getAvgPos() + 20.0f * glm::vec3(-avgVeldirection.z, 0.0f, avgVeldirection.x);
        scene.m_cams[3].pointTo(boids->getAvgPos());

        // Boid control
        addsubBoidsCooldown.tick();
        if (inputs.keys["addboid"] && addsubBoidsCooldown.isUp())
        {
            boids->addBoid();
            addsubBoidsCooldown.reset();
        }

        if (inputs.keys["removeboid"] && addsubBoidsCooldown.isUp())
        {
            boids->removeBoid();
            addsubBoidsCooldown.reset();
        }

        // Update simulation if not paused
        float radius = 10.0f;
        float freq = 0.05f;
        if (!pause)
        {
            scene.m_object[leaderBoidIndex].reactToInput(inputs);
            
            TIME_IT("Update Boids")
            boids->updateAll();
        }
    }

    void OnUpdate() override
    {
        TIME_IT("Whole loop")

        {
            TIME_IT("Clear Buffers")
            display.setClearColor(0.05f, 0.05f, 0.09f, 1.0f);
            display.clear();
        }

        // GUI
        gui.startFrame("Boid Parameters");
        
        gui.text("Limits : ");
        gui.sliderFloat("View Radius", boids->m_viewRad, 0.5, 25.0);
        gui.sliderFloat("View FOV", boids->m_boidsFOV, 10.0f, 359.0);
        gui.sliderFloat("Max Speed", boids->m_maxSpeed, 0.001, 2.0);
        gui.sliderFloat("Max Accel", boids->m_maxAccel, 0.0001, 0.2);
        gui.text("Forces : ");
        gui.sliderFloat("Speed Multiplier", boids->m_speedMultiplier, 0.01, 3.0);
        gui.sliderFloat("Accel Multiplier", boids->m_accelMultiplier, 0.01, 3.0);
        gui.sliderFloat("Align factor", boids->A_fac, 0.001, 2.0);
        gui.sliderFloat("Cohesion factor", boids->C_fac, 0.001, 2.0);
        gui.sliderFloat("Separation factor", boids->S_fac, 0.001, 10.0);
        gui.sliderFloat("Follow factor", boids->F_fac, 0.000, 10.0);

        if (gui.button("Reset"))
        {
            boids->reset();
            scene.m_object[leaderBoidIndex].transform.position = glm::vec3(0.0f);
        }

        if (gui.button("Wireframe"))
        {
            renderer.switchWireframeMode();
        }
        if (gui.button("Skybox"))
            renderer.switchSkybox();

        {
            TIME_IT("Draw calls");
            renderer.draw(scene, *this);
        }

        {
            TIME_IT("Swap Buffers");
            gui.endFrame();
            display.flush();
        }
    }

    void OnShutdown() override
    {
        END_TIMER
    }
};

int main()
{
    BoidsApp app;
    app.Run();
    return 0;
}