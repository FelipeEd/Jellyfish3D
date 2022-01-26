#include <jellyfish/Jellyfish3D.hpp>

// For now it will only work with cubes
Mesh::Mesh()
{

    glm::vec4 cubeColor(0.8f, 0.8f, 0.8f, 1.0f);

    // Cube centered at Origin
    float half = 0.5f;

    std::vector<Vertex> fake_vertexData =
        {
            // Pos, color texCoord normal;
            // Front face
            {glm::vec3(half, half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},   // 0
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},  // 1
            {glm::vec3(-half, -half, half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)}, // 2
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},  // 3
            // Back face
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},   // 4
            {glm::vec3(-half, half, -half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},  // 5
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)}, // 6
            {glm::vec3(half, -half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)}}; // 7

    std::vector<unsigned int> fake_index =
        {
            // Down face
            3, 2, 6,
            3, 6, 7,

            //Top face
            4, 5, 1,
            4, 1, 0,

            //Right face
            4, 0, 3,
            4, 3, 7,

            //left face
            1, 5, 6,
            1, 6, 2,

            //back face
            5, 4, 7,
            5, 7, 6,

            //front face
            0, 1, 2,
            0, 2, 3};

    m_vertexData =
        {
            // Down face
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            {glm::vec3(-half, -half, half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(0.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            {glm::vec3(half, -half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, -1.f, 0.0f)},
            // Top face
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            {glm::vec3(-half, half, -half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            {glm::vec3(half, half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 1.f, 0.0f)},
            // Right face
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 0.f, 0.0f)},
            {glm::vec3(half, half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 1.f), glm::vec3(1.f, 0.f, 0.0f)},
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.0f)},
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 0.f, 0.0f)},
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.0f)},
            {glm::vec3(half, -half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.0f)},
            // Left face
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, 0.f, 0.0f)},
            {glm::vec3(-half, half, -half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(1.f, 1.f), glm::vec3(-1.f, 0.f, 0.0f)},
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.0f)}, // 6
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, 0.f, 0.0f)},   // 1
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.0f)}, // 6
            {glm::vec3(-half, -half, half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 0.f, 0.0f)},  // 2
            // Back face
            {glm::vec3(-half, half, -half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},  // 5
            {glm::vec3(half, half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},   // 4
            {glm::vec3(half, -half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)},  // 7
            {glm::vec3(-half, half, -half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},  // 5
            {glm::vec3(half, -half, -half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)},  // 7
            {glm::vec3(-half, -half, -half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)}, // 6
            // Front face
            {glm::vec3(half, half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},   // 0
            {glm::vec3(-half, half, half), glm::vec3(0.7f, 0.3f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},  // 1
            {glm::vec3(-half, -half, half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)}, // 2
            {glm::vec3(half, half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},   // 0
            {glm::vec3(-half, -half, half), glm::vec3(0.5f, 0.7f, 0.3f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)}, // 2
            {glm::vec3(half, -half, half), glm::vec3(0.3f, 0.5f, 0.7f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},  // 3
        };

    this->genBuffers();
    m_nvertex = m_vertexData.size();
    //m_nindices = m_vetexIndex.size();
}

Mesh::Mesh(const std::string &objName)
{
    m_vertexData = loadOBJ(objName.c_str());
    this->genBuffers();
    m_nvertex = m_vertexData.size();
    //m_nindices = m_vetexIndex.size();
}

Mesh::~Mesh()
{
}

void Mesh::genBuffers()
{

    // Generating the vertex array which the element and vertex buffers will be binded
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // The buffers
    glGenBuffers(1, &m_vbo);
    //glGenBuffers(1, &m_ebo);

    // Vertex buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vertex), &m_vertexData[0], GL_STATIC_DRAW);

    // Element Buffer Object

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vetexIndex.size() * sizeof(unsigned int), &m_vetexIndex[0], GL_STATIC_DRAW);

    // Layout of VAO
    // (location, size, GL_datatype, normalize, stride, pointer_to_start)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);
}

void Mesh::deleteBuffers()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    //glDeleteBuffers(1, &m_ebo);
}

void Mesh::bindBuffer()
{
    glBindVertexArray(m_vao);
}
void Mesh::unbindBuffer()
{
    glBindVertexArray(0);
}

unsigned int Mesh::getNVertex() { return m_nvertex; };
//unsigned int Mesh::getNIndices() { return m_nindices; };
