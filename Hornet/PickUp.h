#pragma once
#include "GameObject.h"
#include "pickuptypes.h" 

class PickUp : public GameObject
{
public:
    PickUp(PickUpType pickupType);
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
    IShape2D& GetCollisionShape() override;
    PickUpType GetPickUpType() const;
private:
    Circle2D m_collisionShape;
    PictureIndex m_SpeedPickUp;
    PictureIndex m_ShootPickUp;
    Vector2D m_speedPickUpPosition;
    Vector2D m_shootPickUpPosition;
    PickUpType m_pickupType;
};

