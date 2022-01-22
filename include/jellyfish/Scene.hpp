#pragma once

#include "Camera.hpp"

class Scene
{
private:
    Camera m_cam1; // Must have 3 cams later on
public:
    std::vector<Object> m_object; // TODO: Use a better container
    std::vector<Light> m_lights;
    Scene();
    ~Scene(){};

    void addObject(std::string name, unsigned int meshID, unsigned int materialId);
    void addLight(std::string name, glm::vec3 color, glm::vec3 pos);

    Camera *getActiveCam() { return &m_cam1; };

    void setPosition(std::string name, glm::vec3 newPos);
    void setRotation(std::string name, glm::vec3 newPos);
    void setScale(std::string name, glm::vec3 newPos);
    void setScale(std::string name, float newPos);

    glm::vec3 getPosition(std::string name);
    glm::vec3 getRotation(std::string name);
    glm::vec3 getScale(std::string name);
};