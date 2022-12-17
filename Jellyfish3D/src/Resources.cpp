#include "Resources.hpp"

Resources::Resources()
{
    Material default_material;
    Mesh default_mesh;

    materials.push_back(default_material);
    meshes.push_back(default_mesh);
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
    Mesh newMesh(m_path + fileName);
    this->meshes.push_back(newMesh);
}

void Resources::loadMaterial(const std::string &fileName, const std::string &size)
{
    Material newMaterial(m_path + fileName, size);
    this->materials.push_back(newMaterial);
}