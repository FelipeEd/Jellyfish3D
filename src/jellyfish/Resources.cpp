#include <jellyfish\Jellyfish3D.hpp>

Resources::Resources()
{
    Material default_material;
    Mesh default_mesh;

    materials.push_back(default_material);
    meshes.push_back(default_mesh);
}

void Resources::loadMesh(const std::string &fileName)
{
    Mesh newMesh(fileName);
    this->meshes.push_back(newMesh);
}

void Resources::loadMaterial(const std::string &fileName, const std::string &size)
{
    Material newMaterial(fileName, size);
    this->materials.push_back(newMaterial);
}