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
const int RAND_IMAGE = 3;
const int RAND_ANGLE = 360;
const int RAND_X_POS1 = 2200;
const int RAND_X_POS2 = 200;
const int RAND_SPEED1 = 111;
const int RAND_SPEED2 = 40;
const int RAND_FRAG_SPEED1 = 51;
const int RAND_FRAG_SPEED2 = 20;
const int ROCK_AMOUNT = 3;

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
    const char* rockImages[RAND_IMAGE] =
    {
        "assets/asteroid1.png",
        "assets/asteroid2.png",
        "assets/asteroid3.png"
    };
    int randImage = rand() % RAND_IMAGE;
    LoadImage(rockImages[randImage]);

    m_scale = ROCKSIZE;

    int posAngle = rand() % RAND_ANGLE;
    int posDistance = rand() % RAND_X_POS1 - RAND_X_POS2;
    m_position.setBearing(posAngle, posDistance);

    int angle = rand() % RAND_ANGLE;
    int speed = rand() % RAND_SPEED1 + RAND_SPEED2;
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
    const char* rockImages[RAND_IMAGE] =
    {
        "assets/asteroid1.png",
        "assets/asteroid2.png",
        "assets/asteroid3.png"
    };
    int randImage = rand() % RAND_IMAGE;
    LoadImage(rockImages[randImage]);

    m_position = position;
    m_scale = ROCKFRAGMENT;

    int angle = rand() % RAND_ANGLE;
    int speed = rand() % RAND_FRAG_SPEED1 + RAND_FRAG_SPEED2;
    m_velocity.setBearing(angle, speed);

}


void Rock::Die()
{
    Deactivate();

    for (int i = 0; i < ROCK_AMOUNT; i++)
    {
        Rock* pFragRock = new Rock(ObjectType::ROCK);
        int angle = rand() % RAND_ANGLE;
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
        //Subtratcs one objects' position from anothers, returning a vector that points from one object to another.
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
