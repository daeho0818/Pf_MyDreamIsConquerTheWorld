#pragma once
#include "cParticle.h"
class cParticleAni
    :public cParticle
{
public:
    cParticleAni(Vec2 pos, float size, double deathTime, double frametime, bool effect = false, string imgName = "");
    ~cParticleAni();

    vector<cTexture*> m_images;

    cTimer* m_ani = nullptr;

    string imgName;

    int m_frame = 0;

    bool m_bOnce = true;

    double deathTime;

    virtual void Update() override;
    virtual void Render() override;
};