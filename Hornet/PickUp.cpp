#include "PickUp.h"

//Constants
double PICKUP_RADIUS = 64;


PickUp::PickUp()
{
}

void PickUp::Initialise()
{
    m_SpeedPickUp = HtGraphics::instance.LoadPicture("assets/powerup1");
    m_ShootPickUp = HtGraphics::instance.LoadPicture("assets/powerup2");

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
    HtGraphics::instance.DrawAt(m_position, m_SpeedPickUp);
    HtGraphics::instance.DrawAt(m_position, m_ShootPickUp);
}

IShape2D& PickUp::GetCollisionShape()
{
    return m_collisionShape;
}
