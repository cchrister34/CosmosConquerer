#include "Scene.h"

//Constants
const Vector2D TILE_POS_1(2000, 0);
const Vector2D TILE_POS_2(3200, 400);
const Vector2D TILE_POS_3(5000, -650);
const Vector2D TILE_POS_4(6300, -500);
const Vector2D TILE_POS_5(7300, 300);


Scene::Scene(ObjectType objType)
{
}

void Scene::Initialise()
{
    pBackGround = new Background(ObjectType::BACKGROUND);
    pBackGround->Initialise();
    ObjectManager::instance.AddItem(pBackGround);

    //Create a vector to store all the locations of the tiles
   //Would prefer this to be in tile.cpp but could not figure it out
    std::vector<Vector2D> tilePositions =
    {
        Vector2D(TILE_POS_1),
        Vector2D(TILE_POS_2),
        Vector2D(TILE_POS_3),
        Vector2D(TILE_POS_4),
        Vector2D(TILE_POS_5),
    };

    //Cycle through the tile locations and create a tile object at the set coordinates
    for (const Vector2D& position : tilePositions)
    {
        Tile* pTile = new Tile(ObjectType::TILE);
        pTile->Initialise(position);
        ObjectManager::instance.AddItem(pTile);
    };
}

void Scene::Render()
{
    //Scene is just a container for other objects to keep the game loop clean
}
