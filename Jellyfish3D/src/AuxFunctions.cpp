#include "AuxFunctions.hpp"

std::vector<Vertex> loadOBJ(const char *file_name)
{
    // Vertex portions
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    // Face vectors
    std::vector<GLint> vertex_position_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    // Vertex array
    std::vector<Vertex> vertices;

    std::stringstream ss;
    std::ifstream in_file(file_name);
    std::string line = "";
    std::string prefix = "";
    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint = 0;

    // File open error check
    if (!in_file.is_open())
    {
        std::cout << "ERROR::OBJLOADER::Could not open file." << std::endl;
    }

    // Read one line at a time
    while (std::getline(in_file, line))
    {
        // Get the prefix of the line
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if (prefix == "#")
        {
        }
        else if (prefix == "o")
        {
        }
        else if (prefix == "s")
        {
        }
        else if (prefix == "use_mtl")
        {
        }
        else if (prefix == "v") // Vertex position
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        }
        else if (prefix == "vt")
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        }
        else if (prefix == "vn")
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
        }
        else if (prefix == "f")
        {
            int counter = 0;
            while (ss >> temp_glint)
            {
                // Pushing indices into correct arrays
                if (counter == 0)
                    vertex_position_indicies.push_back(temp_glint);
                else if (counter == 1)
                    vertex_texcoord_indicies.push_back(temp_glint);
                else if (counter == 2)
                    vertex_normal_indicies.push_back(temp_glint);

                // Handling characters
                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                // Reset the counter
                if (counter > 2)
                    counter = 0;
            }
        }
        else
        {
        }
    }

    // Build final vertex array (mesh)
    vertices.resize(vertex_position_indicies.size(), Vertex());

    // Load in all indices
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
        vertices[i].texCoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
        vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
        vertices[i].color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    // DEBUG
    std::cout << "Number of vertices: " << vertices.size() << "\n";

    // Loaded success
    std::cout << "OBJ file loaded!" << std::endl;
    return vertices;
}

// Retorna o int da textura que foi alocada
unsigned int createTexture(const std::string &textureName)
{
    unsigned int texture;
    // Textura-----------------------------------------------------------------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int tex_width, tex_height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(textureName.c_str(), &tex_width, &tex_height, &nrChannels, 0);

    if (data)
    {
        GLenum formatin;
        if (nrChannels == 1)
        {
            formatin = GL_RED;
        }
        else if (nrChannels == 3)
        {
            formatin = GL_RGB;
        }
        else if (nrChannels == 4)
        {
            formatin = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, formatin, tex_width, tex_height, 0, formatin, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << textureName << std::endl;
    }
    stbi_image_free(data);

    // glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
    //-------------------------------------------------------------------------
}

// Cria o VAO e VBO Unicos
void createBuffers(unsigned int &vao, unsigned int &vbo, Shader &shaderProgram)
{

    shaderProgram = Shader("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");

    // Centrado na origem
    float vertexData[] = {
        //   Posições           //  texture coorinates
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // left bottom
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // right bottom
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right

        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // top right
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f // left bottom
    };

    // Buffers-----------------------------------------------------------------
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    // 1- bind the Vertex Array Object
    // 2- bind and set vertex buffer(s)
    // 3- configure vertex attributes(s)
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // (location, size, GL_datatype, normalize, stride, pointer_to_start)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //-------------------------------------------------
}

void print(const char *msg)
{
    std::cout << msg << std::endl;
}
