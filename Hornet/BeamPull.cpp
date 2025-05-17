#include "BeamPull.h"

//Constants
const double TIMER = 0.0;
const double PULL_SIZE = 2;
const double TIMERINCREASE = 1.5;
const int IMAGE_AMOUNT = 3;
const int LOAD_FIRST_IMAGE = 0;
const int DRAWDEPTH_AMOUNT = -1;
const std::string BEAM_IMAGE_1 = "assets/beampull1.png";
const std::string BEAM_IMAGE_2 = "assets/beampull2.png";
const std::string BEAM_IMAGE_3 = "assets/beampull3.png";

BeamPull::BeamPull(ObjectType objType) : GameObject(ObjectType::BEAMPULL)
{
}

void BeamPull::Update(double frametime)
{
    m_timer = m_timer + TIMERINCREASE * frametime;
    //Loops through the images 0,1,2 constantly when object is initialised
    //Tractor beam class in responsible for deactivation
    m_imageNumber = static_cast<int>(m_timer) % IMAGE_AMOUNT;
}

void BeamPull::Initialise(Vector2D postion)
{
    m_position = postion;
    m_timer = TIMER;
    m_scale = PULL_SIZE;
    SetDrawDepth(DRAWDEPTH_AMOUNT);

    LoadImage(BEAM_IMAGE_1.c_str());
    LoadImage(BEAM_IMAGE_2.c_str());
    LoadImage(BEAM_IMAGE_3.c_str());

    m_imageNumber = LOAD_FIRST_IMAGE;
}