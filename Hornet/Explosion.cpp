#include "Explosion.h"

Explosion::Explosion() : GameObject(ObjectType::EXPLOSION)
{
}

void Explosion::Update(double frametime)
{
    const int TIMERINCREASE = 4;
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
    m_timer = 0.0;
    m_scale = 2.0;

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