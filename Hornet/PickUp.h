#pragma once
#include "GameObject.h"
#include "pickuptypes.h" 
#include "HtAudio.h"

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
    PictureIndex m_HealthPickup;
    Vector2D m_speedPickUpPosition;
    Vector2D m_shootPickUpPosition;
    Vector2D m_healthPickUpPosition;
    PickUpType m_pickupType;
    SoundIndex m_pickUpSound;
    int m_pickUpSoundChannel;
};

