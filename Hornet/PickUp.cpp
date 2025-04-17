#include "PickUp.h"

//Constants
const Vector2D SPEED_PICKUP_POS(3200, 470);
const Vector2D SHOOT_PICKUP_POS(5000, -500);
double PICKUP_RADIUS = 64;
const std::string SPEED_PICKUP_IMAGE = "assets/powerup1.png";
const std::string SHOOT_PICKUP_IMAGE = "assets/powerup2.png";

PickUp::PickUp(ObjectType objType) : GameObject(ObjectType::PICKUP)
{
}

void PickUp::Initialise()
{
    m_SpeedPickUp = HtGraphics::instance.LoadPicture(SPEED_PICKUP_IMAGE.c_str());
    m_ShootPickUp = HtGraphics::instance.LoadPicture(SHOOT_PICKUP_IMAGE.c_str());

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
