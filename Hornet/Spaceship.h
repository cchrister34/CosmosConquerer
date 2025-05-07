#pragma once
#include "GameObject.h"
#include "HtAudio.h"
#include "pickuptypes.h"

class Spaceship : public GameObject
{
public:
    Spaceship(ObjectType objType);
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    void SetFriction(bool active);
    IShape2D& GetCollisionShape() override;
    void CollectPickup(PickUpType type);
    void UseSpeedBoost();
    void UseShootBoost();
    void UsePickUp();
    void TractorBeamPull(Vector2D pull);
    void Trap();
    void Release();
    double GetHealth() const;
    bool IsDead() const;
    void Explode();
    void Shoot();
private:
    Vector2D m_velocity;
    Vector2D m_acceleration;
    Vector2D m_thrust;
    Vector2D m_friction;
    double m_health;
    double m_spawnImmunity;
    double m_angularVelocity;
    SoundIndex m_engineSound;
    int m_engineSoundChannel;
    bool isEnginePlaying;
    Circle2D m_collisionShape;
    Vector2D m_cameraPosition;
    Vector2D m_cameraVelocity;
    double m_topCameraBorder;
    double m_bottomCameraBorder;
    double m_shootdelay;
    Vector2D m_bulletPosition;
    Vector2D m_bulletSpeed;
    SoundIndex m_bulletSound;
    int m_bulletSoundChannel;
    double m_flareDelay;
    double m_flareAngle;
    Vector2D m_flareOffset;
    Vector2D m_flareSpawn;
    Vector2D m_flareVelocity;
    SoundIndex m_flareSound;
    int m_flareSoundChannel;
    SoundIndex m_explosionBang;
    int m_explosionSoundChannel;
    bool m_isFrictionActive;
    bool m_hasPickup;
    PickUpType m_collectedPickup;
    double m_speedMultiplier;
    double m_shootMultiplier;
    double m_pickupTimer;
    double m_dynamicbulletDelay;
    bool m_isTrapped;
    Vector2D m_storedVelocity;
    Vector2D m_findRockVelocity;
    Vector2D m_relativeVelocity;
    double m_relativeSpeed;
    double m_findRockSize;
    double m_rockCollisionDamage;
    bool hasReachedWinPos;
};
