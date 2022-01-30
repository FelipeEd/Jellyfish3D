#pragma once

#include <jellyfish\Jellyfish3D.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Debug.h"

class Boids
{
public:
    float m_boidScale = 0.4;
    int m_startIndex;
    int m_nBoids;
    int targetIndex;
    Scene *m_scene;

    float m_maxSpeed = 0.3f;
    float m_maxAccel = m_maxSpeed / 60;

    float m_speedMultiplier = 1.0f;
    float m_accelMultiplier = 1.0f;

    float A_fac = 0.2f;
    float C_fac = 0.2f;
    float S_fac = 0.6f;
    float F_fac = 0.1f;

    float m_viewRad = 5.0f;
    float m_boidsFOV = 45.0f;

    glm::vec3 boidsAvgPos = glm::vec3(0.0);
    glm::vec3 boidsAvgVelocity = glm::vec3(1.0, 0, 0);

    std::vector<glm::vec3> m_speeds;
    //std::vector<glm::vec3> m_accels;

    Boids(int startIndex, int nBoids, Scene &scene);

    void reset();
    // Boid index
    void updatePosition(int i);
    // Based on the laws
    void updateSpeed(int i);
    void updateAll();
    void addBoid();
    void removeBoid();

    glm::vec3 getAvgPos() { return boidsAvgPos; };
    glm::vec3 getAvgVelocity() { return boidsAvgVelocity; };
};