#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
    Tile(ObjectType objType);
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
private:
    PictureIndex m_tileLayer1;
    PictureIndex m_tileLayer2;
};

