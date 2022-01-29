#pragma once

#include "Camera.hpp"

class Scene
{
private:
    unsigned int activeCam = 0;
    Camera m_cams[4];

public:
    std::vector<Object> m_object; // TODO: Use a better container
    std::vector<Light> m_lights;
    Scene();
    ~Scene(){};

    void addObject(const std::string &name, unsigned int meshID, unsigned int materialId);
    void addLight(const std::string &name, glm::vec3 color, glm::vec3 pos);

    Camera *getActiveCam();

    void setPosition(const std::string &name, glm::vec3 newPos);
    void setRotation(const std::string &name, glm::vec3 newPos);
    void setScale(const std::string &name, glm::vec3 newPos);
    void setScale(const std::string &name, float newPos);

    void setActiveCam(unsigned int i);

    glm::vec3 getPosition(const std::string &name);
    glm::vec3 getRotation(const std::string &name);
    glm::vec3 getScale(const std::string &name);
};