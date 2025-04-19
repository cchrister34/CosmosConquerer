#include "PickUp.h"
#include "ObjectManager.h"
#include "Spaceship.h"
#include <iostream>

//Constants
const Vector2D SPEED_PICKUP_POS(3200, 550);
const Vector2D SHOOT_PICKUP_POS(5000, -500);
double PICKUP_RADIUS = 64;
const std::string SPEED_PICKUP_IMAGE = "assets/powerup1.png";
const std::string SHOOT_PICKUP_IMAGE = "assets/powerup2.png";

PickUp::PickUp(PickUpType pickupType) : GameObject(ObjectType::PICKUP), m_pickupType(pickupType)
{
}

void PickUp::Initialise()
{
    m_SpeedPickUp = HtGraphics::instance.LoadPicture(SPEED_PICKUP_IMAGE.c_str());
    m_ShootPickUp = HtGraphics::instance.LoadPicture(SHOOT_PICKUP_IMAGE.c_str());

    //uses the enum class to set the position of the pick up
    if (m_pickupType == PickUpType::SPEED)
    {
        m_position = SPEED_PICKUP_POS;
    }
    else
    {
        m_position = SHOOT_PICKUP_POS;
    }

    SetCollidable();
    m_collisionShape.PlaceAt(m_position, PICKUP_RADIUS);
}

void PickUp::Update(double frametime)
{
}

void PickUp::ProcessCollision(GameObject& other)
{
    //Code causes high dependency, would be ideal to find an alternative method
    if (other.GetType() == ObjectType::SPACESHIP)
    {
        Spaceship& ship = static_cast<Spaceship&>(other);
        //This tells the spaceship what object type cas collected
        ship.CollectPickup(m_pickupType);
        //Deactivates the collected object to avoid player confusion
        this->Deactivate();
        Event evt;
        evt.type = EventType::OBJECTCOLLECTED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
}

void PickUp::Render()
{
    //uses the enum class to set the position of the image
    if (m_pickupType == PickUpType::SPEED)
    {
        HtGraphics::instance.DrawAt(m_position, m_SpeedPickUp);
    }
    else
    {
        HtGraphics::instance.DrawAt(m_position, m_ShootPickUp);
    }
}

IShape2D& PickUp::GetCollisionShape()
{
    return m_collisionShape;
}

PickUpType PickUp::GetPickUpType() const
{
    return m_pickupType;
}
