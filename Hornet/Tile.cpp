#include "Tile.h"

//constants
const double TILE_WIDTH = 670;
const double TILE_HEIGHT = 150;
const Vector2D TILEPOS1(2000, 0);
const Vector2D TILEPOS2(3200, 400);

Tile::Tile(ObjectType objType)
{
}

void Tile::Initialise()
{
    //Load the image for tiles
    m_tileLayer2 = HtGraphics::instance.LoadPicture("assets/tilelayer2.png");

    m_position = TILEPOS1;
    Vector2D bottomLeft = m_position - Vector2D(TILE_WIDTH / 2, TILE_HEIGHT / 2);
    Vector2D topRight = m_position + Vector2D(TILE_WIDTH / 2 , TILE_HEIGHT / 2);
    m_collisionShape.PlaceAt(bottomLeft, topRight);
    SetCollidable();
}

void Tile::Update(double frametime)
{
}

IShape2D& Tile::GetCollisionShape()
{
    return m_collisionShape;
}


void Tile::Render()
{
    HtGraphics::instance.DrawAt(m_position, m_tileLayer2);
}
