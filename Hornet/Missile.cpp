#include "Missile.h"
#include "ObjectManager.h"

//Constans 
const std::string MISSILE_IMAGE = "assets/missile.png";
const std::string MISSILE_SOUND = "assets/missile.wav";
const Vector2D OFF_SCREEN_SPAWN(-2500, 0);
const Vector2D MISSILE_SPAWN_OFFSET(-1700, 0);
const double MISSILE_ANGLE = 90;
const double MISSILE_SIZE = 3;
const double TOP_SPEED = 500; 
const double SPAWN_DELAY = 15;
const double SPAWN_DELAY_RESET = 0.0;
const double MISSILE_WIDTH = 128;
const double MISSILE_HEIGHT = 64;
const double HALF_MISSILE_WIDTH = MISSILE_WIDTH / 2.0;
const double HALF_MISSILE_HEIGHT = MISSILE_HEIGHT / 2.0;



Missile::Missile(ObjectType objType) : GameObject(ObjectType::MISSILE)
{
    m_pTarget = nullptr;
}

void Missile::Initialise()
{
    LoadImage(MISSILE_IMAGE.c_str());
    m_angle = MISSILE_ANGLE;
    m_scale = MISSILE_SIZE;
    //Dummy spawn
    m_position.set(OFF_SCREEN_SPAWN);
    m_hasMissileSpawned = false;
    m_missileSound = HtAudio::instance.LoadSound(MISSILE_SOUND.c_str());
    SetCollidable();
    SetHandleEvents();
}

void Missile::SetTarget(Spaceship* pTarget)
{
    //Weak pointer, only used to access the functions of the spaceship class
    m_pTarget = pTarget; 
}

void Missile::Update(double frametime)
{

    //Safety check to avoid a dangling pointer
    if (m_pTarget == nullptr)
    {
        Deactivate();
    }

    if (!m_hasMissileSpawned)
    {
        m_spawnDelay += frametime;
        if (m_spawnDelay >= SPAWN_DELAY)
        {
            //Check to see if spaceship is active
            //If not checked game crashes if spaceship was destoryed before spawn timer runs out
            if (m_pTarget != nullptr)
            {
                m_targetLocation = m_pTarget->GetPosition();
                //Where the missile spawns relative to the shapeship
                //Uses the position of the spaceship and adds a Vector2D to it for desired spawn point
                m_position.set(m_targetLocation + MISSILE_SPAWN_OFFSET);
                m_hasMissileSpawned = true;

                //Sound
                if (!isMissilePlaying)
                {
                    m_missileSoundChannel = HtAudio::instance.Play(m_missileSound, true);
                    isMissilePlaying = true;
                }
            }
        }
    }

    if (m_hasMissileSpawned && m_pTarget)
    {
        m_targetLocation = m_pTarget->GetPosition() - m_position;
        m_velocity = m_targetLocation.unitVector() * TOP_SPEED;
        m_position += m_velocity * frametime;
        m_direction = m_velocity.angle();
        m_angle = m_direction;
    }

    Vector2D bottomLeft = m_position - Vector2D(HALF_MISSILE_WIDTH, HALF_MISSILE_HEIGHT);
    Vector2D topRight = m_position + Vector2D(HALF_MISSILE_WIDTH, HALF_MISSILE_HEIGHT);
    m_collisionShape.PlaceAt(bottomLeft, topRight);

    //If ship is destroyed by another object, deactivate and stop sound
    if (!m_pTarget)
    {
        Deactivate();
        m_hasMissileSpawned = false;
        if (isMissilePlaying)
        {
            HtAudio::instance.Stop(m_missileSoundChannel);
            isMissilePlaying = false;
        }
    }
}


void Missile::HandleEvent(Event evt)
{
    //Using a messaging system to avoid a bad pointer to the spaceship object
    if (evt.type == EventType::OBJECTDESTROYED && evt.pSource == m_pTarget)
    {
        m_pTarget = nullptr;
    }

    if (evt.type == EventType::OBJECTCREATED)
    {
        if (evt.pSource && evt.pSource->GetType() == ObjectType::SPACESHIP)
        {
            m_pTarget = static_cast<Spaceship*>(evt.pSource);
            m_hasMissileSpawned = false;
            m_spawnDelay = SPAWN_DELAY_RESET;
            m_position = OFF_SCREEN_SPAWN;
            if (isMissilePlaying)
            {
                HtAudio::instance.Stop(m_missileSoundChannel);
                isMissilePlaying = false;
            }

        }
    }

    if (evt.type == EventType::GAMEOVER)
    {
        m_pTarget = nullptr;
    }


    if (evt.type == EventType::MISSIONCOMPLETE)
    {
        m_pTarget = nullptr;
    }
}

IShape2D& Missile::GetCollisionShape()
{
    return m_collisionShape;
}

void Missile::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::FLARE)
    {
        //This means that the missile will not respawn if destroyed by flares
        Deactivate();
        if (isMissilePlaying)
        {
            HtAudio::instance.Stop(m_missileSoundChannel);
            isMissilePlaying = false;
        }
        Event evt;
        evt.type = EventType::OBJECTDESTROYED;
        evt.pSource = this;
        evt.position = m_position;
        ObjectManager::instance.HandleEvent(evt);

    }
}