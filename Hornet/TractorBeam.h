#pragma once
#include "GameObject.h"
#include "Spaceship.h"
#include "HtAudio.h"

class TractorBeam : public GameObject
{
public:
    TractorBeam(ObjectType objType);
    void Initialise();
    void PullTarget(Spaceship* pTarget);
    void Update(double frametime);
    void HandleEvent(Event evt) override;
    IShape2D& GetCollisionShape() override;
    void ProcessCollision(GameObject& other) override;
private:
    Spaceship* m_pTarget;
};

