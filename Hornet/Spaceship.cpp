#include "Spaceship.h"
#include "HtKeyboard.h"
#include "Bullet.h"
#include "ObjectManager.h"

Spaceship::Spaceship(ObjectType objType) : GameObject(objType)
{
}

void Spaceship::Update(double frametime)
{
    m_position = m_position + m_velocity * frametime;
    m_shootdelay -= frametime;

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D))
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

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_SPACE) && m_shootdelay < 0)
    {
        const double BULLET_MAGNITUDE = 60;
        const double BULLET_SPEED = 800.0;
        m_bulletPosition.setBearing(m_angle, BULLET_MAGNITUDE);
        m_bulletPosition = m_bulletPosition + m_position;
        Bullet* p_Bullet = new Bullet();


        Vector2D bulletPosition = m_bulletPosition;

        m_bulletSpeed.setBearing(m_angle, BULLET_SPEED);
        m_bulletSpeed = m_bulletSpeed + m_velocity;

        Vector2D bulletVelocity = m_bulletSpeed;


        p_Bullet->Initialise(bulletPosition, bulletVelocity);
        ObjectManager::instance.AddItem(p_Bullet);

        m_shootdelay = SHOOTDELAY;
        m_bulletSoundChannel = HtAudio::instance.Play(m_bulletSound);
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
    m_angle = 90;
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
