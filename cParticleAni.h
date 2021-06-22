#pragma once
#include "cParticle.h"
class cParticleAni
    :public cParticle
{
public:
    cParticleAni(Vec2 pos, float size, bool effect = false, int count = 0, int kind = 0, float frametime = 0.005);
    ~cParticleAni();

    vector<cTexture*> m_images;
    cTimer* m_ani = nullptr;
    int m_frame = 0;
    int count;

    bool m_bOnce = true;

    float FrameTime;

    virtual void Update() override;
    virtual void Render() override;
};