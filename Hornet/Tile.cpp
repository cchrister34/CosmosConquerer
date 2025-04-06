#include "Tile.h"

//constants
const Vector2D TILEPOS1(2000, -1000);
const Vector2D TILEPOS2(2700, 300);

Tile::Tile(ObjectType objType)
{
}

void Tile::Initialise()
{
    m_tileLayer1 = HtGraphics::instance.LoadPicture("assets/tilelayer1.png");
    m_tileLayer2 = HtGraphics::instance.LoadPicture("assets/tilelayer2.png");
}

void Tile::Update(double frametime)
{
}

void Tile::Render()
{
    HtGraphics::instance.DrawAt(TILEPOS1, m_tileLayer1);
    HtGraphics::instance.DrawAt(TILEPOS2, m_tileLayer2);
}
