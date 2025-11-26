#include "Scene.hpp"

Scene::Scene()
{
    m_cams[0].transform.position = glm::vec3(0.0, 0.0, 50.0);
}

void Scene::addObject(const std::string &name, unsigned int meshID, unsigned int materialId)
{
    Object newObj = Object(name, meshID, materialId);
    m_object.push_back(newObj);
}

void Scene::removeLastObject()
{
    m_object.pop_back();
}

void Scene::addLight(const std::string &name, glm::vec3 color, glm::vec3 pos)
{
    Light light(name, color, pos);
    this->m_lights.push_back(light);
}

void Scene::reactToInput(GLFWwindow *window, KeyStates input)
{
    if (input.keys["selectcam0"])
        this->activeCam = 0;
    if (input.keys["selectcam1"])
        this->activeCam = 1;
    if (input.keys["selectcam2"])
        this->activeCam = 2;
    if (input.keys["selectcam3"])
        this->activeCam = 3;

    m_cams[this->activeCam].reactToInput(window, input);
}

void Scene::setPosition(const std::string &name, glm::vec3 newPos) //! Bad implementation O(n) its not necessary to see every element
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.position = newPos;
    }
}

void Scene::setRotation(const std::string &name, glm::vec3 newRot)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.rotation = newRot;
    }
}

void Scene::setScale(const std::string &name, glm::vec3 newScale)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.scale = newScale;
    }
}

void Scene::setScale(const std::string &name, float newScale)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.scale = glm::vec3(newScale);
    }
}

void Scene::setActiveCam(unsigned int i)
{
    if (i < 2)
        activeCam = i;
}

Camera *Scene::getActiveCam()
{
    return &m_cams[activeCam];
}

glm::vec3 Scene::getPosition(const std::string &name)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.position;
    }
    return glm::vec3(0);
}

glm::vec3 Scene::getRotation(const std::string &name)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.rotation;
    }
    return glm::vec3(0);
}

glm::vec3 Scene::getScale(const std::string &name)
{
    for (size_t i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.scale;
    }
    return glm::vec3(0);
}