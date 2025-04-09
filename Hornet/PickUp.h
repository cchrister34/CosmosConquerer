#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
    PickUp();
    void Update(double frametime)override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    IShape2D& GetCollisionShape() override;
private:
    Circle2D m_collisionArea;
};

