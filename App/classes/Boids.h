#pragma once

#include <jellyfish\Jellyfish3D.hpp>
#include "Instrumentor.h"

#include <glm/gtx/rotate_vector.hpp>

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
    float m_boidSpeed = 0.2f;
    float m_boidSteer = 0.01f;
    float m_viewRad = 5.0f;
    Scene *m_scene;
    std::vector<glm::vec3> m_speeds;
    std::vector<glm::vec3> m_accels;

    Boids(int startIndex, int nBoids, Scene &scene)
    {
        m_scene = &scene;
        m_startIndex = startIndex;
        m_nBoids = nBoids;

        m_speeds.resize(m_nBoids);
        m_accels.resize(m_nBoids);

        for (int i = 0; i < m_nBoids; i++)
        {
            m_scene->addObject("boid" + std::to_string(i), 4, 1);
            m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
            m_scene->setScale("boid" + std::to_string(i), 0.2);

            m_speeds[i] = glm::sphericalRand(m_boidSpeed);
            m_accels[i] = glm::vec3(0.0f);
        }
    }

    void resetPositions()
    {
        for (int i = 0; i < m_nBoids; i++)
        {
            m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
            m_scene->setScale("boid" + std::to_string(i), 0.2);

            m_speeds[i] = glm::sphericalRand(m_boidSpeed);
            m_accels[i] = glm::vec3(0.0f);
        }
    }

    // Boid index
    void updatePosition(int i)
    {
        comp_Transform *transf = &m_scene->m_object[i + m_startIndex].transform;
        glm::vec3 newpos = transf->position + m_speeds[i];

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

        if (newpos.z < -25)
            newpos.z = a * 25;
        if (newpos.z > 25)
            newpos.z = -a * 25;

        //newpos.x = 0; //! force 2d
        transf->position = newpos;

        glm::vec3 norSpVec = normalize(m_speeds[i]);
        // original looking is {0,0,1}, so to look at the speed direction
        // transf->setRotation({glm::degrees(glm::orientedAngle(glm::vec2(norSpVec.y, norSpVec.z), glm::vec2(1.0f, 0.0f))),
        //                      glm::degrees(glm::orientedAngle(glm::vec2(norSpVec.x, norSpVec.z), glm::vec2(1.0f, 0.0f))),
        //                      0.0f});
        float deg = glm::angle(glm::vec3(0.0f, 0.0f, 1.0f), norSpVec);
        transf->rotation = glm::rotate(glm::vec3(0.0f, 0.0f, 1.0f), deg, glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), norSpVec));

        /*
        Vector3 zaxis = Vector3::normalize(lookat - pos);
        Vector3 xaxis = Vector3::normalize(Vector3::cross(objectUpVector, zaxis));
        Vector3 yaxis = Vector3::cross(zaxis, xaxis);
        */
    }

    // Based on the laws
    void updateSpeed(int i)
    {
        InstrumentationTimer timer("Update Speed");
        glm::vec3 avgRepulsion(0.0);
        glm::vec3 avgPos(0.0);
        glm::vec3 avgSpeed(0.0);

        glm::vec3 separationForce(0.0);
        glm::vec3 cohesionForce(0.0);
        glm::vec3 alignForce(0.0);

        glm::vec3 thisPos = m_scene->m_object[i + m_startIndex].transform.position;

        unsigned int countClose = 0;

        for (int j = 0; j < m_nBoids; j++)
        {
            glm::vec3 otherPos = m_scene->m_object[j + m_startIndex].transform.position;
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

            cohesionForce = avgPos - thisPos;
            alignForce = avgSpeed - m_speeds[i];
            separationForce = avgRepulsion;
        }

        m_speeds[i] += alignForce * m_boidSteer;
        m_speeds[i] += cohesionForce * m_boidSteer;
        m_speeds[i] += separationForce * m_boidSteer;
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