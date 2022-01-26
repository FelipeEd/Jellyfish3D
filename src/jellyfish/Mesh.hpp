#pragma once

#include <vector>
#include <string>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Mesh
{
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    //unsigned int m_ebo;
    unsigned int m_nvertex;
    //unsigned int m_nindices;

    std::vector<Vertex> m_vertexData;
    std::vector<unsigned int> m_vetexIndex;

public:
    Mesh(); // Cube place holder
    Mesh(const std::string &objName);
    ~Mesh();

    void genBuffers();
    void deleteBuffers();
    void bindBuffer();
    void unbindBuffer();

    unsigned int getNVertex();
    //unsigned int getNIndices();
};
