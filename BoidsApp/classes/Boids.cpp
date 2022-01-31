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

    m_speeds.reserve(m_nBoids + 20);
    //m_accels.resize(m_nBoids);

    for (int i = 0; i < m_nBoids; i++)
    {
        m_scene->addObject("boid" + std::to_string(i), 4, 1);
        m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
        m_scene->setScale("boid" + std::to_string(i), m_boidScale);
        m_scene->m_object[i + m_startIndex].isBoids = true;
        m_speeds[i] = glm::sphericalRand(m_maxSpeed);
        //m_accels[i] = glm::vec3(0.0f);
    }
}

void Boids::reset()
{
    for (int i = 0; i < m_nBoids; i++)
    {
        m_scene->setPosition("boid" + std::to_string(i), glm::sphericalRand(20.0f));
        m_scene->setScale("boid" + std::to_string(i), m_boidScale);
        m_scene->m_object[i + m_startIndex].isBoids = true;
        m_speeds[i] = glm::sphericalRand(m_maxSpeed);
        //m_accels[i] = glm::vec3(0.0f);
    }
    m_scene->setPosition("target", glm::vec3(0.0f));
}

// Boid index
void Boids::updatePosition(int i)
{
    comp_Transform *transf = &m_scene->m_object[i + m_startIndex].transform;

    glm::vec3 trueSpeed = m_speeds[i];
    glm::vec3 newpos = transf->position + trueSpeed;

    // teleport 1 or inviWall -1
    float a = 1;

    if (newpos.x > 25)
        newpos.x = -a * 25;
    if (newpos.x < -25)
        newpos.x = a * 25;

    if (newpos.y > 12.5)
        newpos.y = -a * 12.5;
    if (newpos.y < -12.5)
        newpos.y = a * 12.5;

    if (newpos.z < -25)
        newpos.z = a * 25;
    if (newpos.z > 25)
        newpos.z = -a * 25;

    //newpos.z = 0; //! force 2d
    transf->position = newpos;

    transf->lookAt(glm::normalize(trueSpeed));
}

// Based on the laws
void Boids::updateSpeed(int i)
{
    glm::vec3 avgPos(0.0f);
    glm::vec3 avgSpeed(0.0f);
    glm::vec3 avgRepulsion(0.0f);

    glm::vec3 alignForce(0.0f);
    glm::vec3 cohesionForce(0.0f);
    glm::vec3 separationForce(0.0f);

    glm::vec3 accel(0.0f);

    glm::vec3 thisPos = m_scene->m_object[i + m_startIndex].transform.position;

    unsigned int countClose = 0;

    // Calculating avg stuff from the flock
    for (int j = 0; j < m_nBoids; j++)
    {
        glm::vec3 otherPos = m_scene->m_object[j + m_startIndex].transform.position;
        float cdist = dist(thisPos, otherPos);

        if (i != j && cdist < m_viewRad && glm::angle(m_speeds[i], thisPos - otherPos) < m_boidsFOV)
        {
            avgPos += otherPos;
            avgSpeed += m_speeds[j];
            avgRepulsion -= 1.0f / cdist * (otherPos - thisPos);

            countClose++;
        }
    }

    // If the boid is not alone
    if (countClose != 0)
    {
        avgPos /= countClose;
        avgSpeed /= countClose;
        avgRepulsion /= countClose;

        alignForce = avgSpeed - m_speeds[i];
        cohesionForce = avgPos - thisPos;
        separationForce = avgRepulsion;
    }

    glm::vec3 followForce = m_scene->m_object[targetIndex].transform.position - thisPos;
    accel = alignForce * A_fac + cohesionForce * C_fac + separationForce * S_fac + followForce * F_fac;

    accel *= m_accelMultiplier;
    if (glm::length(accel) > m_maxAccel)
        accel = glm::normalize(accel) * m_maxAccel;

    m_speeds[i] += accel;

    m_speeds[i] *= m_speedMultiplier;

    // limits the boid speed
    if (glm::length(m_speeds[i]) > m_maxSpeed)
        m_speeds[i] = normalize(m_speeds[i]) * m_maxSpeed;
}

void Boids::updateAll()
{

    {
        TIME_IT("Calc Speeds")
        for (int i = 0; i < m_nBoids; i++)
        {
            updateSpeed(i);
        }
    }

    {
        TIME_IT("Update Positions")
        for (int i = 0; i < m_nBoids; i++)
        {
            updatePosition(i);
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

    m_nBoids++;
}

void Boids::removeBoid()
{
    if (m_nBoids > 0)
    {
        m_scene->removeLastObject();
        m_speeds.pop_back();
        m_nBoids--;
    }
}

void Boids::calcAvgs()
{
    boidsAvgPos = glm::vec3(0.0);
    boidsAvgVelocity = glm::vec3(0.0);
    for (int i = 0; i < m_nBoids; i++)
    {
        boidsAvgPos += m_scene->m_object[i + m_startIndex].transform.position;
        boidsAvgVelocity += m_speeds[i];
    }
    boidsAvgPos /= m_nBoids;
    boidsAvgVelocity /= m_nBoids;
}