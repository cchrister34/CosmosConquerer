#include "Background.h"

Background::Background(ObjectType objType)
{
}

void Background::Initialise()
{
    m_bgImage = HtGraphics::instance.LoadPicture("assets/bgImage.png");
}

void Background::Update(double frametime)
{
}

void Background::Render()
{
   Vector2D centre(0, 0);
   double scale = 2.0;
   HtGraphics::instance.DrawAt(centre, m_bgImage, scale);
}
