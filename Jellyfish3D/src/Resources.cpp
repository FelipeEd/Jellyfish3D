#include <Resources.hpp>

Resources::Resources()
{
    materials.emplace_back();
    meshes.emplace_back();
}

Resources::~Resources()
{
    // Destrutores de Mesh e Material agora cuidam automaticamente da limpeza
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