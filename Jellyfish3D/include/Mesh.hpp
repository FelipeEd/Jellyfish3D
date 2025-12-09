#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include <AuxFunctions.hpp>
#include <PrimitiveStructs.hpp>

class Mesh
{
private:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    // unsigned int m_ebo;
    unsigned int m_nvertex = 0;
    // unsigned int m_nindices;

    std::vector<Vertex> m_vertexData;
    std::vector<unsigned int> m_vetexIndex;

public:
    Mesh(); // Cube place holder
    Mesh(const std::string &objName);
    ~Mesh();
    
    // Move semantics
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    
    // Prevent copying
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void genBuffers();
    void deleteBuffers();
    void bindBuffer() const;
    void unbindBuffer() const;

    unsigned int getNVertex() const { return m_nvertex; }
    // unsigned int getNIndices() const noexcept { return m_nindices; }
};
