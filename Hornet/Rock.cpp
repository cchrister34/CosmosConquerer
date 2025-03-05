#include "Rock.h"
#include "ObjectManager.h"

//Constants
const int TOPBORDER = 1000;
const int BOTTOMBORDER = -1000;
const int BORDERLEFT = 1600;
const int BORDERRIGHT = -1600;
const double ROCKRADIUS = 64;
const double ROCKSIZE = 0.4;
const double ROCKFRAGMENT = 0.3;

Rock::Rock() : GameObject(ObjectType::ROCK)
{
}

void Rock::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;

    if (m_position.XValue > BORDERLEFT)
    {
        m_velocity.XValue = -m_velocity.XValue;
    }
    else if (m_position.XValue < BORDERRIGHT)
    {
        m_velocity.XValue = -m_velocity.XValue;
    }

    if (m_position.YValue > TOPBORDER)
    {
        m_velocity.YValue = -m_velocity.YValue;
    }
    else if (m_position.YValue < BOTTOMBORDER)
    {
        m_velocity.YValue = -m_velocity.YValue;
    }

    m_collisionShape.PlaceAt(m_position, ROCKRADIUS);
}

void Rock::Initialise()
{
    LoadImage("assets/asteroid.png");
    double rockSize = ROCKSIZE;
    double fragRock = ROCKFRAGMENT;
    m_scale = rockSize;

    int posAngle = rand() % 360;
    int posDistance = rand() % 401 + 600;
    m_position.setBearing(posAngle, posDistance);

    int angle = rand() % 360;
    int speed = rand() % 111 + 40;
    m_velocity.setBearing(angle, speed);

    SetCollidable();
    m_collisionShape.PlaceAt(m_position, ROCKRADIUS);
}

IShape2D& Rock::GetCollisionShape()
{
    return m_collisionShape;

}

void Rock::Initialise(Vector2D rockSize, Vector2D rockVelocity, double size)
{
    rockSize = m_position;
    rockVelocity = m_velocity;
    size = ROCKFRAGMENT;
}

void Rock::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::BULLET)
    {
        Deactivate();
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
}
