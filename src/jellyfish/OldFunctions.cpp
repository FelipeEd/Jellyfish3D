#include <jellyfish/Jellyfish3D.hpp>

// Retorna o int da textura que foi alocada
unsigned int createTexture(const char *textureName)
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
    unsigned char *data = stbi_load(textureName, &tex_width, &tex_height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
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

/*
Sprite::Sprite() {}

Sprite::Sprite(float w, float h, unsigned int intexture, int nframes)
{

    //Shader shaderProgram("bin/shaders/vertex.glsl", "bin/shaders/fragment.glsl");
    this->shader = shaderProgram;
    this->scale.x = w;
    this->scale.y = h;

    this->nFrames = nframes;
    this->shader = shaderProgram;
    this->texture = intexture;
}

void Sprite::draw(Point position)
{
    // Desenhar o triangulo
    // 1- ativar shader
    // 2- vincular VAO (pode ser feito uma vez fora do loop, caso exista apenas 1 VAO)
    // 3- usar glDrawArrays para desenhar conteudo do VAO
    this->shader.use();
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBindVertexArray(vao);

    this->shader.setVec2("uTranslate", position);
    this->shader.setVec2("uScale", this->scale);
    this->shader.setVec4("uColor", this->color);
    this->shader.setFloat("uAspectRatio", (float)HEIGHT / WIDTH);

    this->shader.setFloat("uNFrames", this->nFrames);
    this->shader.setFloat("uCurrentFrame", this->currentFrame);

    glDrawArrays(GL_TRIANGLES, 0, 6); // (primitiva, location, numero de vertices)
}

void Sprite::setCurrentFrame(int n)
{
    this->currentFrame = n;
}

void Sprite::setColor(float newcolor[4])
{
    this->color[0] = newcolor[0];
    this->color[1] = newcolor[1];
    this->color[2] = newcolor[2];
    this->color[3] = newcolor[3];
}

*/

// Coisas dependentes de tempo roda uma vez por frame
/*
        if (timeDiff >= 1.0 / 120.0)
        {

            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "N A V - " + FPS + "FPS /" + ms + "ms";
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = crntTime;
            counter = 0;

            if (mouseRightIsPressed && pauseCooldown == 0)
            {
                gameIsPaused = !gameIsPaused;
                pauseCooldown = 20;
            }

            if (rIsPressed && pauseCooldown == 0)
            {
                Reset = true;
                pauseCooldown = 20;
            }

            if (pauseCooldown > 0)
                pauseCooldown--;

            mouseRightIsPressed = false;

        }
        */