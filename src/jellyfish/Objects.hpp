#pragma once

class Object
{
protected:
    unsigned int m_mesh;
    unsigned int m_material;
    std::string m_name;

public:
    comp_Transform transform;
    Object();
    Object(const std::string &name, unsigned int mesh, unsigned int material);
    ~Object(){};

    void reactToInput(GLFWwindow *window, KeyStates input);

    glm::mat4 getScaleMatrix();
    glm::mat4 getRotateMatrix();
    glm::mat4 getTranslateMatrix();
    glm::mat4 getModelMatrix();

    unsigned int getMeshId();
    unsigned int getMaterialId();
    std::string getName();

    void setMeshId(unsigned int id) { m_mesh = id; }
};