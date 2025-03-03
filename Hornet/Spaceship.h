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

    //Player Constants because there is only one player
    const double THRUST = 230.0;
    const double SHOOT_DELAY = 0.3;
    const double SHIP_SIZE = 1.25;
    const double FRICTION_STRENGTH = 2.0;
    const double BULLET_MAGNITUDE = 60;
    const double BULLET_SPEED = 800.0;
    const std::string SHIP_IMAGE = "assets/spaceship.png"; //Cannot use const char* because of one definition rule 
    const std::string ENGINE_SOUND = "assets/thrustloop.wav";
    const std::string BULLET_SOUND = "assets/zap.wav";
    const std::string EXPLOSION_SOUND = "assets/explosion1.wav";
};
