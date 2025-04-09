#include "PickUp.h"

PickUp::PickUp()
{
}

void PickUp::Update(double frametime)
{
}

void PickUp::ProcessCollision(GameObject& other)
{
}

void PickUp::Initialise()
{
}

IShape2D& PickUp::GetCollisionShape()
{
    return m_collisionArea;
}
