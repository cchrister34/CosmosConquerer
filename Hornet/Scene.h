#pragma once
#include "GameObject.h"
#include "Tile.h"
#include "Background.h"
#include "ObjectManager.h"


class Scene : public GameObject
{
public:
    Scene(ObjectType objType);
    void Initialise();
    void Render()override;
private:
    Background* pBackGround;
    std::vector<Tile*> pTile;
};

