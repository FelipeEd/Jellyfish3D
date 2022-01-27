#pragma once

#include <jellyfish\Jellyfish3D.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Debug.h"

class Boids
{
public:
    int m_startIndex;
    int m_nBoids;
    int targetIndex;

    float m_maxSpeed = 0.2f;
    float m_maxAccel = 0.01f;

    float m_speedMultiplier = 1.0f;
    float m_accelMultiplier = 1.0f;

    float A_fac = 0.2f;
    float C_fac = 0.2f;
    float S_fac = 0.5f;
    float F_fac = 0.2f;

    float m_viewRad = 5.0f;

    Scene *m_scene;

    std::vector<glm::vec3> m_speeds;
    //std::vector<glm::vec3> m_accels;

    Boids(int startIndex, int nBoids, Scene &scene);

    void reset();
    // Boid index
    void updatePosition(int i);
    // Based on the laws
    void updateSpeed(int i);
    void updateAll();
};