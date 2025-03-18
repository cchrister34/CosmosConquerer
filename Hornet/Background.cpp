#include "Background.h"
#include "HtCamera.h"

Background::Background(ObjectType objType)
{
}

void Background::Initialise()
{
    LoadImage("assets/spacebg.png");
    SetDrawDepth(-1);
    m_scale = 2.0;
}

void Background::Update(double frametime)
{
    Vector2D cameraPos = HtCamera::instance.GetCameraCentre(Vector2D());
    m_position = Vector2D(cameraPos.XValue, 0);
}

