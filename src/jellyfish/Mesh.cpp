#include <jellyfish/Jellyfish3D.hpp>

// For now it will only work with cubes
Mesh::Mesh()
{

    glm::vec4 cubeColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Cube centered at Origin
    float half = 0.5f;

    // m_vertexData =
    //     {
    //         // Pos, color;
    //         // Front face
    //         {glm::vec3(half, half, 0.0f), cubeColor},
    //         {glm::vec3(-half, half, 0.0f), cubeColor},
    //         {glm::vec3(-half, -half, 0.0f), cubeColor},
    //     };
    // m_vetexIndex = {0, 1, 2};

    m_vertexData =
        {
            // Pos, color;
            // Front face
            {glm::vec3(-half, -half, half), cubeColor},
            {glm::vec3(-half, -half, -half), cubeColor},
            {glm::vec3(half, -half, -half), cubeColor},
            {glm::vec3(half, -half, half), cubeColor},
            // Back face
            {glm::vec3(-half, half, half), cubeColor},
            {glm::vec3(-half, half, -half), cubeColor},
            {glm::vec3(half, half, -half), cubeColor},
            {glm::vec3(half, half, half), cubeColor}};

    m_vetexIndex =
        {
            // Down face
            0, 1, 2,
            0, 2, 3,

            //Up face
            4, 5, 6,
            4, 6, 7,

            //Right face
            0, 3, 7,
            0, 4, 7,

            //left face
            1, 2, 6,
            1, 6, 5,

            //back face
            0, 5, 4,
            0, 1, 5,

            //front face
            3, 2, 6,
            3, 6, 7};

    this->genBuffer();
    m_nvertex = m_vertexData.size();
    m_nindices = m_vetexIndex.size();
}

void Mesh::genBuffer()
{

    // Generating the vertex array which the element and vertex buffers will be binded
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // The buffers
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    // Vertex buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vertex), &m_vertexData[0], GL_STATIC_DRAW);

    // Element Buffer Object

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vetexIndex.size() * sizeof(unsigned int), &m_vetexIndex[0], GL_STATIC_DRAW);

    // Layout of VAO
    // (location, size, GL_datatype, normalize, stride, pointer_to_start)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
}

void Mesh::bindBuffer()
{
    glBindVertexArray(m_vao);
}

unsigned int Mesh::getNVertex() { return m_nvertex; };
unsigned int Mesh::getNIndices() { return m_nindices; };
