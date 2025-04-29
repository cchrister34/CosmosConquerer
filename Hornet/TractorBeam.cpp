#include "TractorBeam.h"

//Constants
const std::string TRACTOR_BEAM_IMAGE = "assets/tractorbeam.png";
const double TRACTOR_BEAM_SIZE = 2.5;

TractorBeam::TractorBeam(ObjectType objType) : GameObject(ObjectType::TRACTORBEAM)
{
    m_pTarget = nullptr;
}

void TractorBeam::Initialise(Vector2D position)
{
    m_position = position;
    m_tractorBeam = HtGraphics::instance.LoadPicture(TRACTOR_BEAM_IMAGE.c_str());
    m_scale = TRACTOR_BEAM_SIZE;
}

void TractorBeam::PullTarget(Spaceship* pTarget)
{
}

void TractorBeam::Update(double frametime)
{
}

void TractorBeam::HandleEvent(Event evt)
{
}


void TractorBeam::ProcessCollision(GameObject& other)
{
}

void TractorBeam::Render()
{
    HtGraphics::instance.DrawAt(m_position, m_tractorBeam, m_scale);
}
