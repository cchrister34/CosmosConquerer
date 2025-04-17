#include "Tile.h"

//constants
const double TILE_WIDTH = 670;
const double TILE_HEIGHT = 150;
const double HALF_TILE_WIDTH = TILE_WIDTH / 2.0;
const double HALF_TILE_HEIGHT = TILE_HEIGHT / 2.0;
const std::string TILE_IMAGE = "assets/tilelayer.png";

Tile::Tile(ObjectType objType) : GameObject(ObjectType::TILE)
{
}

void Tile::Initialise(Vector2D position)
{
    //Load the image for tiles
    m_tileLayer = HtGraphics::instance.LoadPicture(TILE_IMAGE.c_str());

    //set the position of the collision at the centre of the image
    m_position = position;
    //calculate the location of the bottom left by subtracting half of the tile's width and height from the centre
    Vector2D bottomLeft = m_position - Vector2D(HALF_TILE_WIDTH, HALF_TILE_HEIGHT);
    //calcualte the top right by adding half of the tile width and height from the centre
    Vector2D topRight = m_position + Vector2D(HALF_TILE_WIDTH, HALF_TILE_HEIGHT);
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
    HtGraphics::instance.DrawAt(m_position, m_tileLayer);
}

void Tile::ProcessCollision(GameObject& other)
{
}