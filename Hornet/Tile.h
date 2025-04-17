#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
    Tile(ObjectType objType);
    void Initialise(Vector2D position);
    void Update(double frametime)override;
    void ProcessCollision(GameObject& other)override;
    IShape2D& GetCollisionShape() override;
    void Render()override;
private:
    PictureIndex m_tileLayer;
    Rectangle2D m_collisionShape;
};

