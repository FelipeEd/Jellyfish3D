#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <Camera.hpp>
#include <Light.hpp>
#include <Timer.hpp>

struct GLFWwindow;

class Scene
{
private:
    unsigned int activeCam = 0;
    Timer m_camSelectCooldown = Timer(5);

public:
    Camera m_cams[4];
    std::vector<Object> m_object; // TODO: Use a better container
    std::vector<Light> m_lights;
    Scene();
    ~Scene(){};

    void initCameras(GLFWwindow* window);

    void addObject(const std::string &name, unsigned int meshID, unsigned int materialId);
    void addLight(const std::string &name, glm::vec3 color, glm::vec3 pos);
    void removeLastObject();

    void reactToInput(KeyStates input);

    void setPosition(const std::string &name, glm::vec3 newPos);
    void setRotation(const std::string &name, glm::vec3 newPos);
    void setScale(const std::string &name, glm::vec3 newPos);
    void setScale(const std::string &name, float newPos);
    void setActiveCam(unsigned int i);

    glm::vec3 getPosition(const std::string &name) const;
    glm::vec3 getRotation(const std::string &name) const;
    glm::vec3 getScale(const std::string &name) const;
    Camera *getActiveCam() { return &m_cams[activeCam]; }
};