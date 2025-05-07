#pragma once
#include "GameObject.h"
class BeamPull : public GameObject
{
public:
    BeamPull(ObjectType objType);
    void Update(double frametime) override;
    void Initialise(Vector2D postion);
private:
    double m_timer;
};

