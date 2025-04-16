#include "PickUp.h"

//Constants
const Vector2D SPEED_PICKUP_POS(3200, 410);
const Vector2D SHOOT_PICKUP_POS(5000, -500);
double PICKUP_RADIUS = 64;


PickUp::PickUp(ObjectType objType) : GameObject(ObjectType::PICKUP)
{
}

void PickUp::Initialise()
{
    m_SpeedPickUp = HtGraphics::instance.LoadPicture("assets/powerup1.png");
    m_ShootPickUp = HtGraphics::instance.LoadPicture("assets/powerup2.png");

    m_speedPickUpPosition = SPEED_PICKUP_POS;
    m_shootPickUpPosition = SHOOT_PICKUP_POS;

    SetCollidable();
    m_collisionShape.PlaceAt(m_position, PICKUP_RADIUS);
}

void PickUp::Update(double frametime)
{
}

void PickUp::ProcessCollision(GameObject& other)
{
}

void PickUp::Render()
{
    HtGraphics::instance.DrawAt(m_speedPickUpPosition, m_SpeedPickUp);
    HtGraphics::instance.DrawAt(m_shootPickUpPosition, m_ShootPickUp);
}

IShape2D& PickUp::GetCollisionShape()
{
    return m_collisionShape;
}
