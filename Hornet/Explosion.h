#pragma once
#include "GameObject.h"

class  Explosion : public GameObject
{
public:
    Explosion();
    void Update(double frametime) override;
    void Initialise(Vector2D postion);
private:
    double m_timer;
};

