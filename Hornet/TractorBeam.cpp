#include "TractorBeam.h"

//Constants
const std::string TRACTOR_BEAM_IMAGE = "assets/tractorbeam.png";
const double TRACTOR_BEAM_SIZE = 2.5;
const double PULL_RANGE = 1200;
const double PULL_STRENGTH = 30000;
const double PULL_MAGNETISM = 1;
const double TRAP_RADIUS = 200;
const int TRACTOR_BEAM_HEALTH = 5;

TractorBeam::TractorBeam(ObjectType objType) : GameObject(ObjectType::TRACTORBEAM)
{
    m_pTarget = nullptr;
}

void TractorBeam::Initialise(Vector2D position)
{
    m_position = position;
    m_tractorBeam = HtGraphics::instance.LoadPicture(TRACTOR_BEAM_IMAGE.c_str());
    m_scale = TRACTOR_BEAM_SIZE;
    m_health = TRACTOR_BEAM_HEALTH;
    m_isSpaceshipInRange = false;
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

    if (m_pTarget)
    {
        m_targetLocation = m_pTarget->GetPosition();
        //Size of the distance between the tractor beam and the spaceship objects
        m_distance = (m_targetLocation - m_position).magnitude();
        //Calculates the direction that the spaceship must travel to the reach the tractor beam

        if (m_distance < PULL_RANGE)
        {
            m_isSpaceshipInRange = true;
            m_direction = m_position - m_targetLocation;
            //Increases the pull stength based on how close the spaceship is to the tractor beam 
            m_pullMagnitude = PULL_STRENGTH * (PULL_MAGNETISM / m_distance);
            m_pullForce = m_direction.unitVector() * m_pullMagnitude;
            //Apply the pull force onto the spaceship object
            m_pTarget->TractorBeamPull(m_pullForce * frametime);
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
}

void TractorBeam::Render()
{
    HtGraphics::instance.DrawAt(m_position, m_tractorBeam, m_scale);
}
