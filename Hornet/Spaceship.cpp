#include "Spaceship.h"

Spaceship::Spaceship() : GameObject(ObjectType::SPACESHIP)
{
}

void Spaceship::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
}

void Spaceship::ProcessCollision(GameObject& other)
{
}

void Spaceship::Initialise()
{
    m_position.set(0, 0);
    m_velocity.set(0, 0);
    LoadImage("assets/spaceship.png");
}
