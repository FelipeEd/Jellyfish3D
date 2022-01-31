#pragma once

class Skybox
{
private:
    unsigned int skyboxVAO, skyboxVBO;

public:
    unsigned int m_texSkybox, m_texIrrad, m_texRad;
    Skybox();
    ~Skybox();
    void bindBuffer();

    //! Must only be used by object rendering
    void setUniforms(Shader &shader);
};