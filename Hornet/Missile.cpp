#include "Missile.h"
#include <iostream>

//Constans 
const std::string MISSILE_IMAGE = "assets/missile.bmp";
const double MISSILE_ANGLE = 90;
const double TOP_SPEED = 300; 
const double SPAWN_DELAY = 5;


Missile::Missile(ObjectType objType) : GameObject(ObjectType::MISSILE)
{
    m_pTarget = nullptr;
}

void Missile::Initialise()
{
    LoadImage(MISSILE_IMAGE.c_str());
    m_angle = MISSILE_ANGLE;
    m_position.set(-2000, 0);
    m_hasMissileSpawned = false;
    SetCollidable();
    SetHandleEvents();
}

void Missile::SetTarget(Spaceship* pTarget)
{
    //Weak pointer, only used to access the functions of the spaceship class
    m_pTarget = pTarget; 
}

void Missile::Update(double frametime)
{
    if (!m_hasMissileSpawned)
    {
        m_spawnDelay += frametime;
        if (m_spawnDelay >= SPAWN_DELAY)
        {
            m_targetLocation = m_pTarget->GetPosition();
            Vector2D spawnOffset(-1700, 0);
            m_position.set(m_targetLocation + spawnOffset);
            m_hasMissileSpawned = true;
        }
    }

    if (m_hasMissileSpawned && m_pTarget)
    {
        m_targetLocation = m_pTarget->GetPosition() - m_position;
        m_velocity = m_targetLocation.unitVector() * TOP_SPEED;
        m_position += m_velocity * frametime;
        m_direction = m_velocity.angle();
        m_angle = m_direction;
    }
}

void Missile::HandleEvent(Event evt)
{
    //Using a messaging system to avoid a bad pointer to the spaceship object
    if (evt.type == EventType::OBJECTDESTROYED && evt.pSource == m_pTarget)
    {
        m_pTarget = nullptr;
    }
}

void Missile::ProcessCollision(GameObject& other)
{
}
