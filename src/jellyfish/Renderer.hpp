#pragma once

class Renderer
{
private:
    Skybox skybox;

    bool wireframeMode = false;
    bool toggleSkybox = true;
    void drawObjects(Scene &scene, App &app);
    void drawLights(Scene &scene, App &app);
    void drawSkybox(Scene &scene, App &app);

public:
    Shader m_objectShader;
    Shader m_lightShader;
    Shader m_skyboxShader;

    Renderer();
    ~Renderer();

    void draw(Scene &scene, App &app);
    void switchWireframeMode();
    void switchSkybox();
};