#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "AuxFunctions.hpp"
#include "PrimitiveStructs.hpp"

class Mesh
{
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    // unsigned int m_ebo;
    unsigned int m_nvertex;
    // unsigned int m_nindices;

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
    // unsigned int getNIndices();
};
