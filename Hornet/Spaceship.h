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
    double m_shootdelay;
    SoundIndex m_bulletSound;
    bool hasBulletFired;
    int m_bulletSoundChannel;
    SoundIndex m_explosionBang;
    int m_explosionSoundChannel;
    Vector2D m_bulletPosition;
    Vector2D m_bulletSpeed;
    bool m_isFrictionActive = true;
};
