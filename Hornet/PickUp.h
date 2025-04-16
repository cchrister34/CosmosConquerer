#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
    PickUp();
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
    IShape2D& GetCollisionShape() override;
private:
    Circle2D m_collisionShape;
    PictureIndex m_SpeedPickUp;
    PictureIndex m_ShootPickUp;
};

