#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <stbi/stb_image.h>

#include "PrimitiveStructs.hpp"
#include "Shader.hpp"

std::vector<Vertex> loadOBJ(const char *file_name);
unsigned int createTexture(const std::string &textureName);
void createBuffers(unsigned int &vao, unsigned int &vbo, Shader &shaderProgram);
void print(const char *msg);