#include "Background.h"

Background::Background(ObjectType objType)
{
}

void Background::Initialise()
{
    m_bgImage1 = HtGraphics::instance.LoadPicture("assets/spacebg.png");
    m_bgImage2 = HtGraphics::instance.LoadPicture("assets/starsbg.png");
    SetDrawDepth(-2);
}

void Background::Update(double frametime)
{
}

void Background::Render()
{
    Vector2D bgImage1pos(-1100, 0);
    HtGraphics::instance.DrawAt(bgImage1pos, m_bgImage1, 2.5);

    Vector2D bgImage2pos(3000, 0);
    HtGraphics::instance.DrawAt(bgImage2pos, m_bgImage2, 2.5);
}
