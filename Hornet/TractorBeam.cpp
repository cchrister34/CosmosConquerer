#include "TractorBeam.h"
#include "ObjectManager.h"
#include "Explosion.h"

//Constants
const std::string TRACTOR_BEAM_IMAGE = "assets/tractorbeam.png";
const std::string PULLING_SOUND = "assets/tractorbeam.wav";
const std::string EXPLOSION_SOUND = "assets/explosion4.wav";
const double TRACTOR_BEAM_HEIGHT = 68 * 2.5;
const double TRACTOR_BEAM_WIDTH = 182 * 2.5;
const double HALF_BEAM_HEIGHT = TRACTOR_BEAM_HEIGHT / 2;
const double HALF_BEAM_WIDTH = TRACTOR_BEAM_WIDTH / 2;
const double TRACTOR_BEAM_SIZE = 2.5;
const double PULL_RANGE = 1000;
const double PULL_STRENGTH = 50;
const double PULL_MAGNETISM = 1;
const double TRAP_RANGE = 300;
const int HIT_RELEASE_AMOUNT = 5;
const int HIT_RELEASE_RESET = 0;

TractorBeam::TractorBeam(ObjectType objType) : GameObject(ObjectType::TRACTORBEAM)
{
    m_pTarget = nullptr;
}

void TractorBeam::Initialise(Vector2D position)
{
    m_position = position;
    m_tractorBeam = HtGraphics::instance.LoadPicture(TRACTOR_BEAM_IMAGE.c_str());
    m_scale = TRACTOR_BEAM_SIZE;
    m_isSpaceshipInRange = false;
    m_isTrapped = false;

    Vector2D bottomLeft = m_position - Vector2D(HALF_BEAM_WIDTH, HALF_BEAM_HEIGHT);
    Vector2D topRight = m_position + Vector2D(HALF_BEAM_WIDTH, HALF_BEAM_HEIGHT);
    m_collisionShape.PlaceAt(bottomLeft, topRight);

    //Sounds
    m_explosionBang = HtAudio::instance.LoadSound(EXPLOSION_SOUND.c_str());
    m_pullingSoundEffect = HtAudio::instance.LoadSound(PULLING_SOUND.c_str());
    m_isPullingEffectPlaying = false;

    SetCollidable();
    SetHandleEvents();
}

void TractorBeam::PullTarget(Spaceship* pTarget)
{
    m_pTarget = pTarget;
}

void TractorBeam::Update(double frametime)
{
    m_isSpaceshipInRange = false;
    m_isTrapped = false;

    //Safety check to avoid a dangling pointer
    if (m_pTarget == nullptr)
    {
        Deactivate();
    }

    if (m_pTarget->IsActive() == true)
    {
        m_targetLocation = m_pTarget->GetPosition();
        //Size of the distance between the tractor beam and the spaceship objects
        m_distance = (m_targetLocation - m_position).magnitude();

        if (m_distance < PULL_RANGE)
        {
            m_isSpaceshipInRange = true;
            //Calculates the direction that the spaceship must travel to the reach the tractor beam
            m_direction = m_position - m_targetLocation;
            //Increases the pull stength based on how close the spaceship is to the tractor beam 
            m_pullMagnitude = PULL_STRENGTH * (PULL_MAGNETISM / m_distance);
            m_pullForce = m_direction * m_pullMagnitude;
            //Apply the pull force onto the spaceship object
            m_pTarget->TractorBeamPull(m_pullForce * frametime);

            //Sound
            if (!m_isPullingEffectPlaying)
            {
                m_pullingEffectChannel = HtAudio::instance.Play(m_pullingSoundEffect);
                m_isPullingEffectPlaying = true;
            }
        }
        else
        {
            if (m_isPullingEffectPlaying)
            {
                HtAudio::instance.Stop(m_pullingEffectChannel);
                m_isPullingEffectPlaying = false;
            }
        }

        if (m_distance < TRAP_RANGE)
        {
            m_isTrapped = true;
            m_pTarget->Trap();
        }

    }
}

void TractorBeam::HandleEvent(Event evt)
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


void TractorBeam::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::BULLET && m_isTrapped)
    {
        m_hitCount++;

        other.Deactivate();

        if (m_hitCount >= HIT_RELEASE_AMOUNT && m_pTarget)
        {
            Deactivate();
            m_pTarget->Release();
            m_hitCount = HIT_RELEASE_RESET;
            HtAudio::instance.Stop(m_pullingEffectChannel);
            m_isPullingEffectPlaying = false;
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
    }
}

IShape2D& TractorBeam::GetCollisionShape()
{
    return m_collisionShape;
}

void TractorBeam::Render()
{
    HtGraphics::instance.DrawAt(m_position, m_tractorBeam, m_scale);
}
