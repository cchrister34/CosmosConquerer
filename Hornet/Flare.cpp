#include "Flare.h"

//Constants
const std::string FLARE_IMAGE = "assets/flare.png";
const double FLARE_LIFETIME = 3.0;
const double FLARE_SCALE = 1.0;
const double RADIUS = 12;


Flare::Flare() : GameObject(ObjectType::FLARE)
{
}

void Flare::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
    m_lifetime -= frametime;
    if (m_lifetime <= 0)
    {
        Deactivate();
    }

    m_collisionArea.PlaceAt(m_position, RADIUS);
}

void Flare::ProcessCollision(GameObject& other)
{
}

void Flare::Initialise(Vector2D position, Vector2D velocity)
{
    m_position = position;
    m_velocity = velocity;

    LoadImage(FLARE_IMAGE.c_str());
    m_lifetime = FLARE_LIFETIME;
    m_angle = m_velocity.angle();
    m_scale = FLARE_SCALE;

    SetCollidable();
    m_collisionArea.PlaceAt(m_position, RADIUS);
}

IShape2D& Flare::GetCollisionShape()
{
    return m_collisionArea;
}
