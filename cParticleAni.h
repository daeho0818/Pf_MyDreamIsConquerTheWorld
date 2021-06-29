#pragma once
#include "cParticle.h"
class cParticleAni
    :public cParticle
{
public:
    cParticleAni(Vec2 pos, float size, double deathTime, bool effect = false, string imgName = "", int count = 0, float frametime = 0.005);
    ~cParticleAni();

    vector<cTexture*> m_images;

    cTimer* m_ani = nullptr;

    string imgName;

    int m_frame = 0;
    int count;

    bool m_bOnce = true;

    double deathTime;

    float FrameTime;

    virtual void Update() override;
    virtual void Render() override;
};