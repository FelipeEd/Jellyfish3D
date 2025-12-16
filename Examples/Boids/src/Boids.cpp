#include "Boids.h"

// random normalized float
float rf()
{
    return ((rand() % 10) - 5) / 5.0;
}

float dist(glm::vec3 a, glm::vec3 b)
{
    return glm::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

float len(glm::vec3 a)
{
    return glm::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

Boids::Boids(int startIndex, int nBoids, Scene &scene)
{
    m_scene = &scene;
    m_scene->addObject("Target", 6, 5);
    m_scene->setScale("Target", m_boidScale * 2);
    targetIndex = startIndex;
    m_startIndex = startIndex + 1;

    m_nBoids = nBoids;

    m_speeds.resize(m_nBoids + 20);  // Mudado de reserve para resize
    m_boidObjects.reserve(m_nBoids + 20);
    // m_accels.resize(m_nBoids);

    for (int i = 0; i < m_nBoids; i++)
    {
        m_scene->addObject("boid" + std::to_string(i), 4, 1);
        m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
        m_scene->setScale("boid" + std::to_string(i), m_boidScale);
        m_scene->m_object[i + m_startIndex].isBoids = true;
        m_speeds[i] = glm::sphericalRand(m_maxSpeed);
        // m_accels[i] = glm::vec3(0.0f);
    }
    
    // Cache pointers after all objects are added
    for (int i = 0; i < m_nBoids; i++)
    {
        m_boidObjects.push_back(&m_scene->m_object[i + m_startIndex]);
    }
}

void Boids::reset()
{
    for (int i = 0; i < m_nBoids; i++)
    {
        m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
        m_scene->setScale("boid" + std::to_string(i), m_boidScale);
        m_boidObjects[i]->isBoids = true;
        m_speeds[i] = glm::sphericalRand(m_maxSpeed);
        // m_accels[i] = glm::vec3(0.0f);
    }
    m_scene->setPosition("target", glm::vec3(0.0f));
}

// Boid index
void Boids::updatePosition(int i, float deltaTime)
{
    comp_Transform *transf = &m_boidObjects[i]->transform;

    glm::vec3 trueSpeed = m_speeds[i];
    glm::vec3 newpos = transf->position + trueSpeed * deltaTime * 60.0f; // 60 FPS as reference

    // Boundary box with teleportation
    if (m_enableBoundary)
    {
        if (newpos.x > m_boundaryX)
            newpos.x = -m_boundaryX;
        if (newpos.x < -m_boundaryX)
            newpos.x = m_boundaryX;

        if (newpos.y > m_boundaryY)
            newpos.y = -m_boundaryY;
        if (newpos.y < -m_boundaryY)
            newpos.y = m_boundaryY;

        if (newpos.z > m_boundaryZ)
            newpos.z = -m_boundaryZ;
        if (newpos.z < -m_boundaryZ)
            newpos.z = m_boundaryZ;
    }

    transf->position = newpos;

    transf->lookAt(glm::normalize(trueSpeed + glm::sphericalRand(0.0001f)));
}

// Based on the laws
void Boids::updateSpeed(int i, float deltaTime)
{
    glm::vec3 avgPos(0.0f);
    glm::vec3 avgSpeed(0.0f);
    glm::vec3 avgRepulsion(0.0f);

    glm::vec3 alignForce(0.0f);
    glm::vec3 cohesionForce(0.0f);
    glm::vec3 separationForce(0.0f);

    glm::vec3 accel(0.0f);

    glm::vec3 thisPos = m_boidObjects[i]->transform.position;

    unsigned int countClose = 0;

    // Calculating avg stuff from the flock
    for (int j = 0; j < m_nBoids; j++)
    {
        glm::vec3 otherPos = m_boidObjects[j]->transform.position;
        float cdist = dist(thisPos, otherPos);

        // FOV check: angle between velocity and direction to neighbor
        if (i != j && cdist < m_viewRad && cdist > 0.001f)
        {
            glm::vec3 toOther = otherPos - thisPos;
            float angle = glm::degrees(glm::angle(glm::normalize(m_speeds[i]), glm::normalize(toOther)));
            
            if (angle < m_boidsFOV)
            {
                avgPos += otherPos;
                avgSpeed += m_speeds[j];
                avgRepulsion += (thisPos - otherPos) / (cdist * cdist); // inverse square law

                countClose++;
            }
        }
    }

    // If the boid is not alone
    if (countClose != 0)
    {
        avgPos /= countClose;
        avgSpeed /= countClose;
        avgRepulsion /= countClose;

        // Forces mantêm magnitudes proporcionais - afetam aceleração
        alignForce = avgSpeed - m_speeds[i];
        cohesionForce = avgPos - thisPos;
        separationForce = avgRepulsion;
    }

    glm::vec3 followForce(0.0f);
    if (hasLeadingBoid)
    {
        followForce = m_scene->m_object[targetIndex].transform.position - thisPos;
    }
    
    // Soma das forças = aceleração resultante
    accel = alignForce * A_fac + cohesionForce * C_fac + separationForce * S_fac + followForce * F_fac;

    accel *= m_accelMultiplier;
    if (glm::length(accel) > m_maxAccel)
        accel = glm::normalize(accel) * m_maxAccel;

    m_speeds[i] += accel * deltaTime * 60.0f; // 60 FPS as reference

    // Limits the boid speed
    float currentSpeed = glm::length(m_speeds[i]);
    if (currentSpeed > m_maxSpeed)
    {
        m_speeds[i] = glm::normalize(m_speeds[i]) * m_maxSpeed;
    }
    else if (currentSpeed < m_minSpeed && currentSpeed > 0.001f)
    {
        // Maintain minimum speed to avoid trembling
        m_speeds[i] = glm::normalize(m_speeds[i]) * m_minSpeed;
    }
    
    // Apply speed multiplier AFTER clamping
    m_speeds[i] *= m_speedMultiplier;
}

void Boids::updateAll(float deltaTime)
{
    // Atualiza apenas alguns boids por frame (ciclo)
    int boidsToUpdate = std::min(m_boidsPerFrame, m_nBoids);
    
    {
        TIME_IT("Calc Speeds")
        for (int count = 0; count < boidsToUpdate; count++)
        {
            updateSpeed(m_currentBoidIndex, deltaTime);
            m_currentBoidIndex = (m_currentBoidIndex + 1) % m_nBoids;
        }
    }

    {
        TIME_IT("Update Positions")
        // Atualiza posições de todos (leve)
        for (int i = 0; i < m_nBoids; i++)
        {
            updatePosition(i, deltaTime);
        }
    }
    {
        TIME_IT("Calc avgs")
        this->calcAvgs();
    }
}

void Boids::addBoid()
{
    int i = m_nBoids;
    m_scene->addObject("boid" + std::to_string(i), 4, 1);
    m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
    m_scene->setScale("boid" + std::to_string(i), m_boidScale);
    m_scene->m_object[i + m_startIndex].isBoids = true;
    m_speeds.push_back(glm::sphericalRand(1.0));
    
    // Rebuild cache since vector may have reallocated
    m_boidObjects.clear();
    for (int j = 0; j < m_nBoids + 1; j++)
    {
        m_boidObjects.push_back(&m_scene->m_object[j + m_startIndex]);
    }

    m_nBoids++;
}

void Boids::removeBoid()
{
    if (m_nBoids > 0)
    {
        m_scene->removeLastObject();
        m_speeds.pop_back();
        m_boidObjects.pop_back();
        m_nBoids--;
    }
}

void Boids::calcAvgs()
{
    boidsAvgPos = glm::vec3(0.0);
    boidsAvgVelocity = glm::vec3(0.0);
    for (int i = 0; i < m_nBoids; i++)
    {
        boidsAvgPos += m_boidObjects[i]->transform.position;
        boidsAvgVelocity += m_speeds[i];
    }
    boidsAvgPos /= m_nBoids;
    boidsAvgVelocity /= m_nBoids;
}