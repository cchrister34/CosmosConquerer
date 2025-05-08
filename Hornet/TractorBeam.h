#pragma once
#include "GameObject.h"
#include "Spaceship.h"
#include "HtAudio.h"

class TractorBeam : public GameObject
{
public:
    TractorBeam(ObjectType objType);
    void Initialise(Vector2D position);
    void InitialiseFloorTractorBeam(Vector2D position);
    void PullTarget(Spaceship* pTarget);
    void Update(double frametime);
    void HandleEvent(Event evt) override;
    void ProcessCollision(GameObject& other) override;
    IShape2D& GetCollisionShape() override;
    void Render()override;
private:
    Spaceship* m_pTarget;
    PictureIndex m_tractorBeam;
    Rectangle2D m_collisionShape;
    bool m_isSpaceshipInRange; 
    int m_health;
    Vector2D m_targetLocation;
    double m_distance;
    Vector2D m_direction;
    double m_pullStrength;
    double m_pullMagnitude;
    Vector2D m_pullForce;
    bool m_isTrapped;
    int m_hitCount;
    SoundIndex m_pullingSoundEffect;
    int m_pullingEffectChannel;
    bool m_isPullingEffectPlaying;
    SoundIndex m_explosionBang;
    int m_explosionSoundChannel;
    Vector2D m_beamPullPos;
    bool m_isPullingAnimated;
};

