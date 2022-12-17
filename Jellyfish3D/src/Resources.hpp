#pragma once

#include <string>

#include "Mesh.hpp"
#include "Material.hpp"
// A class that stores all the Meshes and Materials that the application will use
// The "0" position is defined to have the default objects
class Resources
{
private:
    std::string m_path;

public:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;

    // Loads a Mesh from a obj file into the resources
    void loadMesh(const std::string &fileName);

    // Loads a texture and sets the material
    void loadMaterial(const std::string &fileName, const std::string &size);
    void set_path(const std::string path) { m_path = path; };
    Resources();
    ~Resources();
};