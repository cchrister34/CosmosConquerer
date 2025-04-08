#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
    Tile(ObjectType objType);
    void Initialise(Vector2D position);
    void Update(double frametime)override;
    IShape2D& GetCollisionShape() override;
    void Render()override;
private:
    PictureIndex m_tileLayer2;
    Rectangle2D m_collisionShape;
};

