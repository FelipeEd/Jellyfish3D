#include <jellyfish/Jellyfish3D.hpp>

Scene::Scene()
{
    //m_cam1 = Camera();
}

void Scene::addObject(const std::string &name, unsigned int meshID, unsigned int materialId)
{
    Object newObj = Object(name, meshID, materialId);
    m_object.push_back(newObj);
}

void Scene::addLight(const std::string &name, glm::vec3 color, glm::vec3 pos)
{
    Light light(name, color, pos);
    this->m_lights.push_back(light);
}

void Scene::setPosition(const std::string &name, glm::vec3 newPos) //! Bad implementation O(n) its not necessary to see every element
{
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.position = newPos;
    }
}

void Scene::setRotation(const std::string &name, glm::vec3 newRot)
{
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.rotation = newRot;
    }
}

void Scene::setScale(const std::string &name, glm::vec3 newScale)
{
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            m_object[i].transform.scale = newScale;
    }
}

void Scene::setScale(const std::string &name, float newScale)
{
    for (int i = 0; i < m_object.size(); i++)
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
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.position;
    }
    return glm::vec3(0);
}

glm::vec3 Scene::getRotation(const std::string &name)
{
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.rotation;
    }
    return glm::vec3(0);
}

glm::vec3 Scene::getScale(const std::string &name)
{
    for (int i = 0; i < m_object.size(); i++)
    {
        if (m_object[i].getName() == name)
            return m_object[i].transform.scale;
    }
    return glm::vec3(0);
}