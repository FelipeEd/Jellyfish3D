#pragma once

// A class that stores all the Meshes and Materials that the application will use
// The "0" position is defined to have the default objects
class Resources
{
public:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;

    // Loads a Mesh from a obj file into the resources
    void loadMesh(const std::string &fileName);

    // Loads a texture and sets the material
    void loadMaterial(const std::string &fileName, const std::string &size);

    Resources();
    ~Resources();
};