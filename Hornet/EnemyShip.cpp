#include "EnemyShip.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include <iostream>

//Constants
const std::string ENEMY_SHIP_IMAGE = "assets/enemyship.png";
const std::string BULLET_SOUND = "assets/zap.wav";
const double ENEMY_RADIUS = 48;
const double ENEMY_SIZE = 1.5;
const int TOPBORDER = 900;
const int BOTTOMBORDER = -900;
const int LEFTBORDER = 3000;
const int RIGHTBORDER = 9000;
const double SHOOT_RANGE = 750;
const double BULLET_MAGNITUDE = 65;
const double BULLET_SPEED = 700;
const double SHOOT_DELAY = 0.5;


EnemyShip::EnemyShip(ObjectType objType) : GameObject(ObjectType::ENEMYSHIP)
{
    m_pTarget = nullptr;
}

void EnemyShip::Initialise()
{
    LoadImage(ENEMY_SHIP_IMAGE.c_str());
    m_angle = m_velocity.angle();
    m_scale = ENEMY_SIZE;
    m_isPlayerInRange = false;

    m_enemySpawnXpos = rand() % 3001 + 4000;
    m_enemySpawnYpos = rand() % 2001 - 1000;
    m_position.set(Vector2D(m_enemySpawnXpos, m_enemySpawnYpos));

    m_enemySpeed = rand() % 51 + 100;
    m_enemyVelAngle = rand() % 360;
    m_velocity.setBearing(m_enemyVelAngle, m_enemySpeed);

    //Bullet
    m_shootdelay = SHOOT_DELAY;
    m_bulletSound = HtAudio::instance.LoadSound(BULLET_SOUND.c_str());

    SetCollidable();
    SetHandleEvents();
    m_collisionShape.PlaceAt(m_position, ENEMY_RADIUS);
}

void EnemyShip::Update(double frametime)
{
    //Shoot delay reset
    if (m_shootdelay > 0)
    {
        m_shootdelay -= frametime;
    }

    //Safety check to avoid a dangling pointer
    if (m_pTarget == nullptr)
    {
        Deactivate();
    }

    m_isPlayerInRange = false;
    m_position = m_position + m_velocity * frametime;
    m_angle = m_velocity.angle();

    //Spaceship Tracking
    if (m_pTarget->IsActive() == true)
    {
        m_playerLocation = m_pTarget->GetPosition();
        m_distance = (m_playerLocation - m_position).magnitude();

        if (m_distance < SHOOT_RANGE)
        {
            m_isPlayerInRange = true;
            m_direction = m_playerLocation - m_position;
            //Enemies move away from the player
            m_velocity = -m_direction.unitVector() * m_enemySpeed;
            //Rotates the enemy ship in the direction of the player
            m_angle = (m_playerLocation - m_position).angle();
       

            if (m_shootdelay <= 0 && m_isPlayerInRange)
            {
                Shoot();
            }
        }

        //Wrapping 
        if (m_position.YValue > TOPBORDER)
        {
            m_position.YValue = TOPBORDER;
            m_velocity.YValue = -m_velocity.YValue;
        }
        else if (m_position.YValue < BOTTOMBORDER)
        {
            m_position.YValue = BOTTOMBORDER;
            m_velocity.YValue = -m_velocity.YValue;
        }
        if (m_position.XValue < LEFTBORDER)
        {
            m_position.XValue = LEFTBORDER;
            m_velocity.XValue = -m_velocity.XValue;
        }
        else if (m_position.XValue > RIGHTBORDER)
        {
            m_position.XValue = RIGHTBORDER;
            m_velocity.XValue = -m_velocity.XValue;
        }


    }

    m_collisionShape.PlaceAt(m_position, ENEMY_RADIUS);
}

void EnemyShip::FindPlayer(Spaceship* pTarget)
{
    //Weak pointer, only used to access the functions of the spaceship class
    m_pTarget = pTarget;
}

void EnemyShip::Shoot()
{
    m_bulletPosition.setBearing(m_angle, BULLET_MAGNITUDE);
    m_bulletPosition = m_bulletPosition + m_position;
    Vector2D bulletPos = m_bulletPosition;
    Bullet* pBullet;
    pBullet = new Bullet(ObjectType::ENEMYBULLET);
    m_bulletSpeed.setBearing(m_angle, BULLET_SPEED);
    m_bulletSpeed = m_bulletSpeed + m_velocity;
    Vector2D bulletVel = m_bulletSpeed;
    pBullet->InitialiseEnemyBullet(bulletPos, bulletVel);
    ObjectManager::instance.AddItem(pBullet);
    m_shootdelay = SHOOT_DELAY;
    m_bulletSoundChannel = HtAudio::instance.Play(m_bulletSound);
}

IShape2D& EnemyShip::GetCollisionShape()
{
    return m_collisionShape;
}

void EnemyShip::ProcessCollision(GameObject& other)
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

void EnemyShip::HandleEvent(Event evt)
{
    if (evt.type == EventType::OBJECTDESTROYED && evt.pSource == m_pTarget)
    {
        m_pTarget = nullptr;
    }

    //Ensures fucntionality is still active if a spaceship is destoyed and respawns
    if (evt.type == EventType::OBJECTCREATED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            m_pTarget = static_cast<Spaceship*>(evt.pSource);
        }
    }
}



