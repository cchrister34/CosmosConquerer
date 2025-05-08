#include "BeamPull.h"

//Constants
const double TIMER = 0.0;
const double PULL_SIZE = 2;
const double TIMERINCREASE = 1.5;
const int MAX_TIME = 3;
const int LOAD_FIRST_IMAGE = 0;
const int DRAWDEPTH_AMOUNT = -1;

BeamPull::BeamPull(ObjectType objType) : GameObject(ObjectType::BEAMPULL)
{
}

void BeamPull::Update(double frametime)
{
    m_timer = m_timer + TIMERINCREASE * frametime;
    m_imageNumber = static_cast<int>(m_timer) % 3;
}

void BeamPull::Initialise(Vector2D postion)
{
    m_position = postion;
    m_timer = TIMER;
    m_scale = PULL_SIZE;
    SetDrawDepth(DRAWDEPTH_AMOUNT);

    LoadImage("assets/beampull1.png");
    LoadImage("assets/beampull2.png");
    LoadImage("assets/beampull3.png");

    m_imageNumber = LOAD_FIRST_IMAGE;
}