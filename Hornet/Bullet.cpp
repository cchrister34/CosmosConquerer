#include "Bullet.h"

//Constants
const double FADEOUT_TIME = 0.5;
const double BULLET_LIFETIME = 1.0;
const double RADIUS = 12;
const double BULLET_SCALE = 1;
const int BULLET_TRANSPARENCY = 1;
const std::string BULLET_IMAGE = "assets/beams.png";
const std::string ENEMY_BULLET = "assets/enemybullet.png";
const int MIN_LIFETIME = 0;
const int BULLET_DRAWDEPTH = 1;

Bullet::Bullet(ObjectType objType) : GameObject(objType)
{
}

void Bullet::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
    m_lifetime -= frametime;
    if (m_lifetime <= MIN_LIFETIME)
    {
        Deactivate();
    }
    if (m_lifetime < FADEOUT_TIME)
    {
        m_transparency = BULLET_TRANSPARENCY - (m_lifetime / FADEOUT_TIME);
    }

    m_collisionArea.PlaceAt(m_position, RADIUS);

}


void Bullet::Initialise(Vector2D position, Vector2D velocity)
{
    m_position = position;
    m_velocity = velocity;

    LoadImage(BULLET_IMAGE.c_str());
    m_lifetime = BULLET_LIFETIME;
    m_angle = m_velocity.angle();
    m_scale = BULLET_SCALE;

    SetDrawDepth(BULLET_DRAWDEPTH);
    SetCollidable();
    m_collisionArea.PlaceAt(m_position, RADIUS);
}

void Bullet::InitialiseEnemyBullet(Vector2D position, Vector2D velocity)
{
    m_position = position;
    m_velocity = velocity;

    LoadImage(ENEMY_BULLET.c_str());
    m_lifetime = BULLET_LIFETIME;
    m_angle = m_velocity.angle();
    m_scale = BULLET_SCALE;

    SetDrawDepth(BULLET_DRAWDEPTH);
    SetCollidable();
    m_collisionArea.PlaceAt(m_position, RADIUS);
}

IShape2D& Bullet::GetCollisionShape()
{
    return m_collisionArea;
}

void Bullet::ProcessCollision(GameObject& other)
{
    ObjectType type = other.GetType();
    if (type == ObjectType::TILE || type == ObjectType::ROCK || type == ObjectType::EXPLOSIVEROCK
        || type == ObjectType::TRACTORBEAM)
    {
        Deactivate();
    }
}