#include "Bullet.h"

Bullet::Bullet() :GameObject(ObjectType::BULLET)
{
}

void Bullet::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
    m_lifetime -= frametime;
    if (m_lifetime <= 0)
    {
        Deactivate();
    }
    if (m_lifetime < FADEOUT_TIME)
    {
        m_transparency = 1 - (m_lifetime / FADEOUT_TIME);
    }

    m_collisionArea.PlaceAt(m_position, RADIUS);

}


void Bullet::Initialise(Vector2D position, Vector2D velocity)
{
    m_position = position;
    m_velocity = velocity;

    LoadImage("assets/beams.png");
    m_lifetime = BULLET_LIFETIME;
    m_angle = m_velocity.angle();
    m_scale = 2.0;

    SetCollidable();
    m_collisionArea.PlaceAt(m_position, RADIUS);
}

IShape2D& Bullet::GetCollisionShape()
{
    return m_collisionArea;
}

void Bullet::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::ROCK)
    {
        Deactivate();
    }
}