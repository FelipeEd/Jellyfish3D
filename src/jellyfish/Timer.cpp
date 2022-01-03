#include <jellyfish/Jellyfish3D.hpp>

Timer::Timer(unsigned int alarm) { m_framesLeft = m_alarm = alarm; }

bool Timer::isUp()
{
    if (m_framesLeft == 0)
        return true;
    else
        return false;
}

void Timer::tick()
{
    if (m_framesLeft > 0)
        m_framesLeft--;
}

void Timer::reset()
{
    m_framesLeft = m_alarm;
}