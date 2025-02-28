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
    IShape2D& GetCollisionShape() override;
private:
    Vector2D m_velocity;
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
};

//Player Constants because there is only one player
const double THRUST = 230.0;
const double SHOOTDELAY = 0.3;