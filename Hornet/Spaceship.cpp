#include "Spaceship.h"
#include "HtKeyboard.h"

Spaceship::Spaceship(ObjectType objType) : GameObject(objType)
{
}

void Spaceship::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W))
    {
        //Sound
        if (!isEnginePlaying)
        {
            m_engineSoundChannel = HtAudio::instance.Play(m_engineSound, true);
            isEnginePlaying = true;
        }
        Vector2D acceleration;
        acceleration.setBearing(m_angle, THRUST);
        m_velocity = m_velocity + acceleration * frametime;

        //Friction
        const double MAGINCREMENT = 1.0;
        double drag = m_velocity.magnitude() * MAGINCREMENT;
        Vector2D friction = m_velocity.unitVector() * -drag;
        m_velocity = m_velocity + friction * frametime;
    }
    else if (isEnginePlaying)
    {
        HtAudio::instance.Stop(m_engineSoundChannel);
        isEnginePlaying = false;
    }
}

void Spaceship::ProcessCollision(GameObject& other)
{
}

void Spaceship::Initialise()
{
    m_position.set(0,0);
    m_velocity.set(0, 0);
    LoadImage("assets/spaceship.png");
    m_scale = 2.0;
    m_engineSound = HtAudio::instance.LoadSound("assets/thrustloop.wav");

    m_shootdelay = SHOOTDELAY;
    m_bulletSound = HtAudio::instance.LoadSound("assets/zap.wav");
    m_explosionBang = HtAudio::instance.LoadSound("assets/explosion1.wav");

    SetCollidable();
}

IShape2D& Spaceship::GetCollisionShape()
{
    return m_collisionShape;
}
