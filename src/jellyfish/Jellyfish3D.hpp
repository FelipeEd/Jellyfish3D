#pragma once

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <stbi/stb_image.h>
// #include <iostream>
// #include <string>
// #include <map>
// #include <fstream>
// #include <sstream>
// #include <math.h>
// #include <vector>
// #include <list>
#include <chrono>
#include <thread>
#include <future>
//#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>

#include <jellyfish\Clock.hpp>
#include <jellyfish\Timer.hpp>
#include <jellyfish\GUI.hpp>
#include <jellyfish\Display.hpp>
#include <jellyfish\Shader.hpp>
#include <jellyfish\Mesh.hpp>
#include <jellyfish\Material.hpp>
#include <jellyfish\Components.hpp>
#include <jellyfish\KeyStates.hpp>
#include <jellyfish\Objects.hpp>
#include <jellyfish\Light.hpp>
#include <jellyfish\Skybox.hpp>
#include <jellyfish\Resources.hpp>
#include <jellyfish\App.hpp>
#include <jellyfish\Scene.hpp>
#include <jellyfish\Renderer.hpp>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

// // Useful default stuff
// extern unsigned int WIDTH;
// extern unsigned int HEIGHT;
// extern Resources *assets;

// extern bool pbr;

void initOpengl();
std::vector<Vertex> loadOBJ(const char *file_name);
unsigned int createTexture(const std::string &textureName);
