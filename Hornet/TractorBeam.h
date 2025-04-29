#pragma once
#include "GameObject.h"
#include "Spaceship.h"
#include "HtAudio.h"

class TractorBeam : public GameObject
{
public:
    TractorBeam(ObjectType objType);
    void Initialise(Vector2D position);
    void PullTarget(Spaceship* pTarget);
    void Update(double frametime);
    void HandleEvent(Event evt) override;
    void ProcessCollision(GameObject& other) override;
    void Render()override;
private:
    Spaceship* m_pTarget;
    PictureIndex m_tractorBeam;
};

