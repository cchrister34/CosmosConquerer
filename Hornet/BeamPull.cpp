#include "BeamPull.h"

//Constants
const double TIMER = 0.0;
const double PULL_SIZE = 2;
const int TIMERINCREASE = 1.5;

BeamPull::BeamPull(ObjectType objType)
{
}

void BeamPull::Update(double frametime)
{
    m_timer = m_timer + TIMERINCREASE * frametime;
    m_imageNumber = static_cast<int>(m_timer);

    if (m_timer >= 3)
    {
        Deactivate();
    }
}

void BeamPull::Initialise(Vector2D postion)
{
    m_position = postion;
    m_timer = TIMER;
    m_scale = PULL_SIZE;
    SetDrawDepth(-1);

    LoadImage("assets/beampull1.png");
    LoadImage("assets/beampull2.png");
    LoadImage("assets/beampull3.png");

    m_imageNumber = 0;
}
