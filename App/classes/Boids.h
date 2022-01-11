#pragma once

#include <jellyfish\Jellyfish3D.hpp>
#include "Instrumentor.h"

// random normalized float
float rf()
{
    return ((rand() % 10) - 5) / 5.0;
}

class Boids
{
public:
    int m_startIndex;
    int m_nBoids;
    float m_boidSpeed;
    float m_boidSteer;
    float m_viewRad;
    Scene *m_scene;
    std::vector<glm::vec3> m_speeds;
    std::vector<glm::vec3> m_accels;

    Boids(int startIndex, int nBoids, Scene &scene)
    {
        m_boidSpeed = 0.3;
        m_boidSteer = 0.05;
        m_viewRad = 3.0;
        m_scene = &scene;
        m_startIndex = startIndex;
        m_nBoids = nBoids;

        m_speeds.resize(m_nBoids);
        m_accels.resize(m_nBoids);

        for (int i = 0; i < m_nBoids; i++)
        {
            m_scene->addObject("boid" + std::to_string(i), 4, 1);
            m_scene->setPosition("boid" + std::to_string(i), glm::vec3(rf() * 10, rf() * 10, rf() * 10));
            m_scene->setScale("boid" + std::to_string(i), 0.2);

            m_speeds[i] = glm::vec3(rf(), rf(), rf());
            m_speeds[i] = normalize(m_speeds[i]) * m_boidSpeed;
            m_accels[i] = glm::vec3(0.0f);
        }
    }

    // Boid index
    void updatePosition(int i)
    {
        comp_Transform *transf = &m_scene->m_object[i + m_startIndex].m_transform;
        glm::vec3 newpos = transf->getPosition() + m_speeds[i];

        // teleport 1 or inviWall -1
        float a = 1;

        if (newpos.x > 25)
            newpos.x = -a * 25;
        if (newpos.x < -25)
            newpos.x = a * 25;

        if (newpos.y > 25)
            newpos.y = -a * 25;
        if (newpos.y < -25)
            newpos.y = a * 25;
        if (newpos.y > 25)
            newpos.y = -a * 25;

        if (newpos.z < -25)
            newpos.z = a * 25;
        if (newpos.z > 25)
            newpos.z = -a * 25;
        if (newpos.z < -25)
            newpos.z = a * 25;
        //newpos.y = 0; //! force 2d
        transf->setPosition(newpos);

        glm::vec3 normalizedSpVec = normalize(m_speeds[i]);
        transf->setRotation(glm::degrees(m_speeds[i]));
    }

    // Based on the laws
    void updateSpeed(int i)
    {
        glm::vec3 avgRepulsion(0.0);
        glm::vec3 avgPos(0.0);
        glm::vec3 avgSpeed(0.0);

        glm::vec3 separationForce(0.0);
        glm::vec3 cohesionForce(0.0);
        glm::vec3 alignForce(0.0);

        glm::vec3 thisPos = m_scene->m_object[i + m_startIndex].m_transform.getPosition();

        unsigned int countClose = 0;

        for (int j = 0; j < m_nBoids; j++)
        {
            glm::vec3 otherPos = m_scene->m_object[j + m_startIndex].m_transform.getPosition();
            float cdist = glm::distance(thisPos, otherPos);

            if (i != j && cdist < m_viewRad)
            {
                avgPos += otherPos;

                avgSpeed += m_speeds[j];

                avgRepulsion -= 1.0f / cdist * (otherPos - thisPos);

                countClose++;
            }
        }

        if (countClose != 0)
        {
            avgPos /= countClose;
            avgSpeed /= countClose;
            avgRepulsion /= countClose;

            // cohesionForce = normalize(avgPos - thisPos) * m_boidSteer;
            // alignForce = normalize(avgSpeed - m_speeds[i]) * m_boidSteer;
            // separationForce = normalize(avgRepulsion) * 0.5f * m_boidSteer;
            cohesionForce = avgPos - thisPos;
            alignForce = avgSpeed - m_speeds[i];
            separationForce = avgRepulsion * 2.0f;
        }

        m_speeds[i] += alignForce;
        m_speeds[i] += cohesionForce;
        m_speeds[i] += separationForce;
        m_speeds[i] = normalize(m_speeds[i]) * m_boidSpeed;
    }

    void updateAll()
    {
        for (int i = 0; i < m_nBoids; i++)
        {
            updateSpeed(i);
            updatePosition(i);
        }
    }
};