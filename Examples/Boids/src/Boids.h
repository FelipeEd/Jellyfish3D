#pragma once

#include <Jellyfish3D.hpp>
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

    float m_maxSpeed = 0.5f;
    float m_maxAccel = 0.05f;
    float m_minSpeed = 0.1f;

    float m_speedMultiplier = 0.93f;
    float m_accelMultiplier = 0.42f;

    float A_fac = 0.15f;
    float C_fac = 0.05f;
    float S_fac = 0.68f;
    float F_fac = 0.02f;

    float m_viewRad = 7.0f;
    float m_boidsFOV = 55.0f;

    // Boundary box
    float m_boundaryX = 25.0f;
    float m_boundaryY = 12.5f;
    float m_boundaryZ = 25.0f;
    bool m_enableBoundary = true;

    bool hasLeadingBoid = true;

    glm::vec3 boidsAvgPos = glm::vec3(0.0);
    glm::vec3 boidsAvgVelocity = glm::vec3(1.0, 0, 0);

    std::vector<glm::vec3> m_speeds;
    std::vector<Object*> m_boidObjects;
    
    // Atualização cíclica para performance
    int m_boidsPerFrame = 300;  // Quantos boids atualizar por frame
    int m_currentBoidIndex = 0;  // Próximo boid a atualizar
    // std::vector<glm::vec3> m_accels;

    Boids(int startIndex, int nBoids, Scene &scene);

    void reset();
    // Boid index
    void updatePosition(int i, float deltaTime);
    // Based on the laws
    void updateSpeed(int i, float deltaTime);
    void updateAll(float deltaTime);
    void addBoid();
    void removeBoid();
    void calcAvgs();

    glm::vec3 getAvgPos() { return boidsAvgPos; };
    glm::vec3 getAvgVelocity() { return boidsAvgVelocity; };
};