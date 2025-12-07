#pragma once

#include <App.hpp>
#include <Scene.hpp>
#include <Skybox.hpp>

enum class RenderMode
{
    Standard,
    PBR
};

class Renderer
{
private:
    Skybox skybox;
    RenderMode m_renderMode;

    bool wireframeMode = false;
    bool toggleSkybox = true;
    void drawObjects(Scene &scene, App &app);
    void drawLights(Scene &scene, App &app);
    void drawSkybox(Scene &scene, App &app);

public:
    Shader m_objectShader;
    Shader m_lightShader;
    Shader m_skyboxShader;

    Renderer(RenderMode mode = RenderMode::PBR);
    ~Renderer();

    void draw(Scene &scene, App &app);
    void switchWireframeMode();
    void switchSkybox();
};