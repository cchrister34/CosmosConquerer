#pragma once
#include "GameObject.h"
#include "HtAudio.h"

class Spaceship : public GameObject
{
public:
    Spaceship(ObjectType objType);
    void Update(double frametime) override;
    void ProcessCollision(GameObject& other) override;
    void Initialise();
    void SetFriction(bool active);
    IShape2D& GetCollisionShape() override;
private:
    Vector2D m_velocity;
    Vector2D m_acceleration;
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
    bool hasBulletFired;
    int m_bulletSoundChannel;
    double m_flareDelay;
    Vector2D m_flarePosition;
    Vector2D m_flareSpeed;
    SoundIndex m_explosionBang;
    int m_explosionSoundChannel;
    bool m_isFrictionActive = true;
};
