#include "Explosion.h"

//constants
const double TIMER = 0.0;
const double EXPLOSION_SIZE = 2.0;
const int TIMERINCREASE = 4;

Explosion::Explosion(ObjectType objType)
{
}

void Explosion::Update(double frametime)
{
    m_timer = m_timer + TIMERINCREASE * frametime;
    m_imageNumber = static_cast<int>(m_timer);

    if (m_timer >= 8)
    {
        Deactivate();
    }
}

void Explosion::Initialise(Vector2D postion)
{
    m_position = postion;
    m_timer = TIMER;
    m_scale = EXPLOSION_SIZE;

    LoadImage("assets/explosionA1.bmp");
    LoadImage("assets/explosionA2.bmp");
    LoadImage("assets/explosionA3.bmp");
    LoadImage("assets/explosionA4.bmp");
    LoadImage("assets/explosionA5.bmp");
    LoadImage("assets/explosionA6.bmp");
    LoadImage("assets/explosionA7.bmp");
    LoadImage("assets/explosionA8.bmp");

    m_imageNumber = 0;

}