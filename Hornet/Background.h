#pragma once
#include "GameObject.h"

class Background : public GameObject
{
public:
    Background(ObjectType objType);
    void Initialise();
    void Update(double frametime)override;
    void Render()override;
private:
    PictureIndex m_bgImage1;
    PictureIndex m_bgImage2;
    PictureIndex m_bgImage3;
};