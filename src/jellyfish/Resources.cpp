#include <jellyfish\Jellyfish3D.hpp>

Resources::Resources()
{
    Material default_material;
    Mesh default_mesh;

    materials.push_back(default_material);
    meshes.push_back(default_mesh);
}

void Resources::loadMesh(const char *fileName)
{
    Mesh newMesh(fileName);
    this->meshes.push_back(newMesh);
}

void Resources::loadMaterial(const char *fileName)
{
    Material newMaterial(fileName);
    this->materials.push_back(newMaterial);
}