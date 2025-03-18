#include "Background.h"

Background::Background(ObjectType objType)
{
}

void Background::Initialise()
{
    LoadImage("assets/spacebg.png");
    SetDrawDepth(-1);
    m_scale = 2.0;
}
