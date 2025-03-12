#pragma once
#include "GameObject.h"

class Background : public GameObject
{
public:
    Background(ObjectType objType);
    void Initialise();
    void Update(double frametime) override;
    void Render()override;
private:
    int m_width;
    int m_height;
    PictureIndex m_bgImage;
};

