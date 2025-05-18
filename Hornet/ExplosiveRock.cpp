#include "ExplosiveRock.h"
#include "Spaceship.h"
#include "Explosion.h"
#include "ObjectManager.h"

//Constants
const std::string EXPLOSIVE_ROCK_IMAGE = "assets/Asteroids_Explosive.png";
const std::string EXPLOSION_SOUND = "assets/explosion3.wav";
const double ACTIVE_RANGE = 1750;
const double ROCKRADIUS = 36;
const double EXPLOSIVE_ROCK_SIZE = 1.5;


ExplosiveRock::ExplosiveRock(ObjectType objType) : GameObject(ObjectType::EXPLOSIVEROCK)
{
    m_pTarget = nullptr;
}

void ExplosiveRock::Initialise()
{
    LoadImage(EXPLOSIVE_ROCK_IMAGE.c_str());
    m_scale = EXPLOSIVE_ROCK_SIZE;
    m_isActive = false;

    //Spawn Constants 
    const int EXPLOSIVEROCK_RAND_X_POS_MIN = 4001;
    const int EXPLOSIVEROCK_RAND_X_POS_MAX = 8000;
    const int EXPLOSIVEROCK_RAND_Y_POS_MIN = 900;
    const int EXPLOSIVEROCK_RAND_Y_POS_MAX = 1801;
    const int RAND_ANGLE = 360;
    const int RAND_SPEED_MIN = 151;
    const int RAND_SPEED_MAX = 250;

    m_explosiveRockXpos = rand() % EXPLOSIVEROCK_RAND_X_POS_MIN + EXPLOSIVEROCK_RAND_X_POS_MAX;
    m_explosiveRockYpos = rand() % EXPLOSIVEROCK_RAND_Y_POS_MAX - EXPLOSIVEROCK_RAND_Y_POS_MIN;
    m_position.set(Vector2D(m_explosiveRockXpos, m_explosiveRockYpos));

    m_explosiveRockSpeed = rand() % RAND_SPEED_MIN + RAND_SPEED_MAX;
    m_explosiveRockVelocityAngle = rand() % RAND_ANGLE;
    m_velocity.setBearing(m_explosiveRockVelocityAngle, m_explosiveRockSpeed);

    //Explosion
    m_isExplosionSoundPlaying = false;
    m_explosionSound = HtAudio::instance.LoadSound(EXPLOSION_SOUND);

    SetCollidable();
    SetHandleEvents();
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
        Deactivate();
    }

    //A check to see if spaceship is within a specific distance before becoming active 
    //Since the rocks explode on collision by the time the player reaches their position theyve all collided
    //Also helps free up sound channels as they are limited
    //Occasionally one will initially share a spawn with a tile and cause a explosion sound upon starting the game
    if (m_pTarget != nullptr)
    {
        m_playerLocation = m_pTarget->GetPosition();
        m_distance = (m_playerLocation - m_position).magnitude();

        if (!m_isActive && m_distance < ACTIVE_RANGE)
        {
            m_isActive = true;
        }
    }

    if (m_isActive)
    {
        m_position = m_position + m_velocity * frametime;

        //Wrapping
        //Wrapping constants 
        const int TOPBORDER = 1000;
        const int BOTTOMBORDER = -1000;
        const int BORDERLEFT = 4000;
        const int BORDERRIGHT = 9000;


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

    }
    m_collisionShape.PlaceAt(m_position, ROCKRADIUS);
}

void ExplosiveRock::ProcessCollision(GameObject& other)
{
    if (!m_isActive)
        return;

    ObjectType type = other.GetType();
    if (type == ObjectType::EXPLOSIVEROCK || type == ObjectType::TILE || type == ObjectType::TRACTORBEAM)
    {
        Explode();
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);
    }
    else if (type == ObjectType::BULLET)
    {
        Explode();
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

    if (evt.type == EventType::GAMEOVER)
    {
        m_pTarget = nullptr;
        m_isActive = false;
    }

    if (evt.type == EventType::MISSIONCOMPLETE)
    {
        m_pTarget = nullptr;
        m_isActive = false;
    }
}

void ExplosiveRock::Explode()
{
    Deactivate();
    Explosion* p_Explosion = new Explosion(ObjectType::EXPLOSION);
    p_Explosion->Initialise(m_position);
    ObjectManager::instance.AddItem(p_Explosion);
    if (!m_isExplosionSoundPlaying)
    {
        m_explosionSoundChannel = HtAudio::instance.Play(m_explosionSound);
    }
}
