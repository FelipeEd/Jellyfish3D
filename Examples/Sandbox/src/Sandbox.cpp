#include <Jellyfish3D.hpp>

// Global
unsigned int WIDTH = 1280;
unsigned int HEIGHT = 720;

// Your application class - inherits from App
class SandboxApp : public App
{
private:
    GUI gui;
    Renderer renderer;
    Scene scene;
    Timer pauseCooldown;
    
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

public:
    SandboxApp() : App("Examples/Sandbox/"), 
                   renderer(RenderMode::PBR),
                   pauseCooldown(10)
    {
    }

    void OnStart() override
    {
        // Initialize GUI
        gui.init(display.getWindow());
        scene.initCameras(display.getWindow());

        // Load assets
        assets.loadMesh("resources/simplesphere.obj");
        assets.loadMesh("resources/uvsphere.obj");
        assets.loadMesh("resources/plane.obj");
        assets.loadMesh("resources/test_ship.obj");

        assets.loadMaterial("resources/textures/blue_painted_planks", "_1k");
        assets.loadMaterial("resources/textures/white_rough_plaster", "_1k");
        assets.loadMaterial("resources/textures/denmin_fabric_02", "_1k");

        // Setup scene
        scene.addLight("light1", {500, 200, 200}, {5, 2, -1});
        scene.addLight("light3", {1000, 1000, 1000}, {0, 10, 0});

        scene.addObject("ground", 3, 1);
        scene.setScale("ground", 5.0f);

        scene.addObject("sphere", 2, 3);
        scene.setPosition("sphere", {3.0, 2.0, 0.0});

        scene.addObject("sphere2", 2, 0);
        scene.setPosition("sphere2", {-3.0, 2.0, 0.0});

        scene.addObject("suzanne", 4, 2);
        scene.setPosition("suzanne", {1.0, 4.0, 1.0});
    }

    void OnFixedUpdate() override
    {
        // Fixed timestep logic (physics, gameplay)
        scene.reactToInput(inputs);
    }

    void OnUpdate() override
    {
        // Clear screen
        display.setClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        display.clear();

        // GUI
        gui.startFrame("Sandbox Parameters");
        gui.sliderFloat("x", x, -360.0f, 360.0f);
        gui.sliderFloat("y", y, -360.0f, 360.0f);
        gui.sliderFloat("z", z, -360.0f, 360.0f);

        if (gui.button("Wireframe"))
            renderer.switchWireframeMode();
        if (gui.button("Skybox"))
            renderer.switchSkybox();

        // Update object rotation
        scene.setRotation("suzanne", glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));

        // Render
        renderer.draw(scene, *this);

        gui.endFrame();
    }
};

int main()
{
    SandboxApp app;
    app.Run();
    return 0;
}