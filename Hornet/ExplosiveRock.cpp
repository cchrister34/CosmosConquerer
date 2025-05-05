#include "ExplosiveRock.h"
#include "Explosion.h"
#include "ObjectManager.h"

//Constants
const std::string EXPLOSIVE_ROCK_IMAGE = "assets/Asteroids_Explosive.png";
const std::string EXPLOSION_SOUND = "assets/explosion3.wav";
const double ACTIVE_RANGE = 1500;
const double ROCKRADIUS = 36;
const double EXPLOSIVE_ROCK_SIZE = 1.5;
const int TOPBORDER = 1000;
const int BOTTOMBORDER = -1000;
const int BORDERLEFT = -6000;
const int BORDERRIGHT = 9000;

ExplosiveRock::ExplosiveRock(ObjectType objType) : GameObject(ObjectType::EXPLOSIVEROCK)
{
    m_pTarget = nullptr;
}

void ExplosiveRock::Initialise()
{
    LoadImage(EXPLOSIVE_ROCK_IMAGE.c_str());
    m_scale = EXPLOSIVE_ROCK_SIZE;
    m_isActive = false;

    m_explosiveRockXpos = rand() % 4001 + 8000;
    m_explosiveRockYpos = rand() % 2001 - 1000;
    m_position.set(Vector2D(m_explosiveRockXpos, m_explosiveRockYpos));

    m_explosiveRockSpeed = rand() % 101 + 200;
    m_explosiveRockVelocityAngle = rand() % 360;
    m_velocity.setBearing(m_explosiveRockVelocityAngle, m_explosiveRockSpeed);

    //Explosion
    m_explosionBang = HtAudio::instance.LoadSound(EXPLOSION_SOUND);

    SetCollidable();
    m_collisionShape.PlaceAt(m_position, ROCKRADIUS);
}

void ExplosiveRock::FindPlayer(Spaceship* pTarget)
{
    //Weak pointer, only used to access the functions of the spaceship class
    m_pTarget = pTarget;
}

void ExplosiveRock::Update(double frametime)
{
    if (m_pTarget == nullptr)
    {
        return;
    }

    //A check to see if spaceship is within a specific distance before becoming active 
    //Since the rocks explode on collision by the time the player reaches their position theyve all collided
    //Also helps free up sound channels as they are limited
    //Occasionally one will initially share a spawn with a tile and cause a explosion sound upon starting the game
    if (m_pTarget->IsActive() == true)
    {
        m_playerLocation = m_pTarget->GetPosition();
        m_distance = (m_playerLocation - m_position).magnitude();

        if (!m_isActive && m_distance < ACTIVE_RANGE)
        {
            m_isActive = true;
        }
    }

    //If inactive return to the start of Update()
    if (!m_isActive)
        return;

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

void ExplosiveRock::ProcessCollision(GameObject& other)
{
    ObjectType type = other.GetType();
    if (type == ObjectType::EXPLOSIVEROCK || type == ObjectType::TILE)
    {
        Deactivate();
        Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
        p_Explosion->Initialise(m_position);
        ObjectManager::instance.AddItem(p_Explosion);
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionBang);
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
    else if (type == ObjectType::BULLET)
    {
        Deactivate();
        Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
        p_Explosion->Initialise(m_position);
        ObjectManager::instance.AddItem(p_Explosion);
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionBang);
        Event evt;
        evt.type = EventType::SHOTEXPLOSIVEROCK;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
}

IShape2D& ExplosiveRock::GetCollisionShape()
{
    return m_collisionShape;
}

void ExplosiveRock::HandleEvent(Event evt)
{
    if (evt.type == EventType::OBJECTDESTROYED && evt.pSource == m_pTarget)
    {
        m_pTarget = nullptr;
        m_isActive = false;
    }

    //Ensures fucntionality is still active if a spaceship is destoyed and respawns
    if (evt.type == EventType::OBJECTCREATED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            m_pTarget = static_cast<Spaceship*>(evt.pSource);
            m_isActive = false;
        }
    }


}
