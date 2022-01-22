#pragma once

class Renderer
{
private:
public:
    Shader m_shader;
    Shader m_lightShader;
    Renderer();
    ~Renderer(){};

    void draw(Scene &scene, App &app);
};