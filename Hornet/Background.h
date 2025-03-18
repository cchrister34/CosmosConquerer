#pragma once
#include "GameObject.h"

class Background : public GameObject
{
public:
    Background(ObjectType objType);
    void Initialise();
    void Update(double frametime)override;
private:
    PictureIndex m_bgImage;
};