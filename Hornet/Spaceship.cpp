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

        //Friction;
        Vector2D friction = -m_velocity.unitVector();
        friction = friction * (m_velocity.magnitude() * FRICTION_STRENGTH * frametime);
        acceleration = friction;
    }
    else if (isEnginePlaying)
    {
        HtAudio::instance.Stop(m_engineSoundChannel);
        isEnginePlaying = false;
    }

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_SPACE) && m_shootdelay < 0)
    {
        m_bulletPosition.setBearing(m_angle, BULLET_MAGNITUDE);
        m_bulletPosition = m_bulletPosition + m_position;
        Bullet* pBullet = nullptr;
        pBullet = new Bullet;
        if (!pBullet)
        {
            //Memory Leak
        }
        else
        {
            Vector2D bulletPosition = m_bulletPosition;

            m_bulletSpeed.setBearing(m_angle, BULLET_SPEED);
            m_bulletSpeed = m_bulletSpeed + m_velocity;

            Vector2D bulletVelocity = m_bulletSpeed;


            pBullet->Initialise(bulletPosition, bulletVelocity);
            ObjectManager::instance.AddItem(pBullet);

            m_shootdelay = SHOOT_DELAY;
            m_bulletSoundChannel = HtAudio::instance.Play(m_bulletSound);
        }
    }
}


void Spaceship::ProcessCollision(GameObject& other)
{
}

void Spaceship::Initialise()
{
    m_position.set(0,-900);
    m_velocity.set(0, 0);
    LoadImage(SHIP_IMAGE.c_str()); //c_str used to convert sting to const char
    m_scale = SHIP_SIZE; 
    m_engineSound = HtAudio::instance.LoadSound(ENGINE_SOUND.c_str());

    m_shootdelay = SHOOT_DELAY;
    m_bulletSound = HtAudio::instance.LoadSound(BULLET_SOUND);
    m_explosionBang = HtAudio::instance.LoadSound(EXPLOSION_SOUND);

    SetCollidable();
}


IShape2D& Spaceship::GetCollisionShape()
{
    return m_collisionShape;
}
