#include <Jellyfish3D.hpp>

// Global
// Window size
unsigned int WIDTH = 1280;
unsigned int HEIGHT = 720;

int main()
{

    App app("Examples/Sandbox/");
    Timer pauseCooldown(10);
    GUI gui;
    gui.init(app.display.getWindow());

    Renderer renderer(RenderMode::PBR);
    // renderer.switchWireframeMode();

    Scene scene;

    // light model
    app.assets.loadMesh("resources/simplesphere.obj");
    app.assets.loadMesh("resources/uvsphere.obj");
    app.assets.loadMesh("resources/plane.obj");
    app.assets.loadMesh("resources/test_ship.obj");

    app.assets.loadMaterial("resources/textures/blue_painted_planks", "_1k");
    app.assets.loadMaterial("resources/textures/white_rough_plaster", "_1k");
    app.assets.loadMaterial("resources/textures/denmin_fabric_02", "_1k");
    // app.assets->loadMaterial("resources/textures/denmin_fabric_02", "_2k");

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

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    while (!app.display.shouldClose())
    {
        // Real loop ------------------------------------------------------------------------------------------

        // Define a cor de fundo da janela e limpa os buffers
        app.display.setClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        app.display.clear();
        gui.startFrame("Boid Parameters");

        if (app.clock.tick())
        {
            app.inputs.observeInputs();
            // scene.setRotation("suzanne", scene.getRotation("suzanne") + glm::vec3(0.0, 0.3, 0.0));
            scene.reactToInput(app.inputs);
            // scene.getActiveCam()->reactToInput(app.inputs);

            gui.sliderFloat("x", x, -360.0f, 360.0f);
            gui.sliderFloat("y", y, -360.0f, 360.0f);
            gui.sliderFloat("z", z, -360.0f, 360.0f);

            if (gui.button("Wireframe"))
                renderer.switchWireframeMode();
            if (gui.button("Skybox"))
                renderer.switchSkybox();

            scene.setRotation("suzanne", glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
        }

        renderer.draw(scene, app);

        gui.endFrame();
        app.inputs.resetState();
        // Faz a troca do framebuffer antigo para o novo (double buffer)
        app.display.swapBuffers();

        // Captura eventos de IO (movimento de mouse, teclas pressionadas, etc)
        app.display.pollEvents();
    }

    return 0;
}