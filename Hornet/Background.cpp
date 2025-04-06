#include "Background.h"


//Constants
const Vector2D BG_IMG1_POS(0, 0);
const Vector2D BG_IMG2_POS(4175, 0);
const Vector2D BG_IMG3_POS(8350, 0);
const double BG_IMG_SCALE = 2.5;

Background::Background(ObjectType objType)
{
}

void Background::Initialise()
{
    m_bgImage1 = HtGraphics::instance.LoadPicture("assets/spacebg.png");
    m_bgImage2 = HtGraphics::instance.LoadPicture("assets/starsbg.png");
    m_bgImage3 = HtGraphics::instance.LoadPicture("assets/starsbg2.png");
    SetDrawDepth(-2);
}

void Background::Update(double frametime)
{
}

void Background::Render()
{
    HtGraphics::instance.DrawAt(BG_IMG1_POS, m_bgImage1, BG_IMG_SCALE);

    //image width is 1670 so second image needs to have its starts position at +1670*2.5 which is 4175
    HtGraphics::instance.DrawAt(BG_IMG2_POS, m_bgImage2, BG_IMG_SCALE);

    HtGraphics::instance.DrawAt(BG_IMG3_POS, m_bgImage3, BG_IMG_SCALE);
}
