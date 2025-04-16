#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
    PickUp(ObjectType objType);
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
    IShape2D& GetCollisionShape() override;
private:
    Circle2D m_collisionShape;
    PictureIndex m_SpeedPickUp;
    PictureIndex m_ShootPickUp;
    Vector2D m_speedPickUpPosition;
    Vector2D m_shootPickUpPosition;

};

