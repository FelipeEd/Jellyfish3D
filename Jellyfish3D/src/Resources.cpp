#include <Resources.hpp>

Resources::Resources()
{
    materials.emplace_back();
    meshes.emplace_back();
}

Resources::~Resources()
{
    for (auto var : meshes)
    {
        var.deleteBuffers();
    }
    for (auto var : materials)
    {
        var.deleteTextures();
    }
}

void Resources::loadMesh(const std::string &fileName)
{
    // std::cout << "teste: " << m_path + fileName << std::endl;
    this->meshes.emplace_back(m_path + fileName);
}

void Resources::loadMaterial(const std::string &fileName, const std::string &size)
{
    this->materials.emplace_back(m_path + fileName, size);
}