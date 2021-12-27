#include <jellyfish\Jellyfish3D.hpp>

Resources::Resources()
{
    Material default_material;
    Mesh default_mesh;

    materials.push_back(default_material);
    meshes.push_back(default_mesh);
}