#include "Missile.h"
#include <iostream>

//Constans 
const std::string MISSILE_IMAGE = "assets/missile.bmp";
const double MISSILE_ANGLE = 90;
const double TOP_SPEED = 500; 
const double SPAWN_DELAY = 5;
const double MISSILE_WIDTH = 128;
const double MISSILE_HEIGHT = 64;
const double HALF_MISSILE_WIDTH = MISSILE_WIDTH / 2.0;
const double HALF_MISSILE_HEIGHT = MISSILE_HEIGHT / 2.0;



Missile::Missile(ObjectType objType) : GameObject(ObjectType::MISSILE)
{
    m_pTarget = nullptr;
}

void Missile::Initialise()
{
    LoadImage(MISSILE_IMAGE.c_str());
    m_angle = MISSILE_ANGLE;
    //Dummy spawn
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

    Vector2D bottomLeft = m_position - Vector2D(HALF_MISSILE_WIDTH, HALF_MISSILE_HEIGHT);
    Vector2D topRight = m_position + Vector2D(HALF_MISSILE_WIDTH, HALF_MISSILE_HEIGHT);
    m_collisionShape.PlaceAt(bottomLeft, topRight);
}

void Missile::HandleEvent(Event evt)
{
    //Using a messaging system to avoid a bad pointer to the spaceship object
    if (evt.type == EventType::OBJECTDESTROYED && evt.pSource == m_pTarget)
    {
        m_pTarget = nullptr;
    }
}

IShape2D& Missile::GetCollisionShape()
{
    return m_collisionShape;
}

void Missile::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::FLARE)
    {
        Deactivate();
    }
}
