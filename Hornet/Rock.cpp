#include "Rock.h"
#include "ObjectManager.h"
#include "HtCamera.h"

//Constants
const int TOPBORDER = 1000;
const int BOTTOMBORDER = -1000;
const int BORDERLEFT = -1600;
const int BORDERRIGHT = 2200;
const double ROCKRADIUS = 52;
const double ROCKSIZE = 0.75;
const double ROCKFRAGMENT = 0.3;
const int FRAG_SPEED = 10;

Rock::Rock(ObjectType objType) : GameObject(ObjectType::ROCK)
{
}

void Rock::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;

    if (m_position.XValue < BORDERLEFT)
    {
        m_velocity.XValue = -m_velocity.XValue;
    }
    else if (m_position.XValue > BORDERRIGHT)
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
    const char* rockImages[3] =
    {
        "assets/asteroid1.png",
        "assets/asteroid2.png",
        "assets/asteroid3.png"
    };
    int randImage = rand() % 3;
    LoadImage(rockImages[randImage]);

    m_scale = ROCKSIZE;

    int posAngle = rand() % 360;
    int posDistance = rand() % 2201 -200;
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

void Rock::InitialiseRockFragment(const Vector2D& position)
{
    const char* rockImages[3] =
    {
        "assets/asteroid1.png",
        "assets/asteroid2.png",
        "assets/asteroid3.png"
    };
    int randImage = rand() % 3;
    LoadImage(rockImages[randImage]);

    m_position = position;
    m_scale = ROCKFRAGMENT;

    int angle = rand() % 360;
    int speed = rand() % 51 + 20;
    m_velocity.setBearing(angle, speed);

}


void Rock::Die()
{
    Deactivate();

    for (int i = 0; i < 3; i++)
    {
        Rock* pFragRock = new Rock(ObjectType::ROCK);
        int angle = rand() % 360;
        int speed = FRAG_SPEED;
        m_rockFragScatter.setBearing(angle, speed);
        pFragRock->InitialiseRockFragment(m_position + m_rockFragScatter);
        ObjectManager::instance.AddItem(pFragRock);
    }
}


Vector2D Rock::GetVelocity()
{
    return m_velocity;
}



void Rock::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::BULLET)
    {
        Die();
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }

    ObjectType type = other.GetType();
    if (type == ObjectType::TILE || type == ObjectType::ROCK)
    {
        //Subtratcs a rock's position from anothers, returning a vector that points from one rock to another.
        Vector2D collisionVector = m_position - other.GetPosition();
        //Uses the collision vector to calculate the direction they are colliding from
        Vector2D direction = collisionVector.unitVector();
        double speed = m_velocity.magnitude();
        m_velocity = direction * speed;
        Event evt;
        evt.type = EventType::OBJECTCOLLIDED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }

    if (other.GetType() == ObjectType::SPACESHIP)
    {
        Die();
    }
}
