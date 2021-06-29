#pragma once
#include "singleton.h"
class cParticleManager :
    public singleton<cParticleManager>
{
    vector<cParticle*> m_particles;
public:
    cParticleManager();
    ~cParticleManager();

    void AddParticle(Vec2 pos, float size, string imgName = "", float frameTime = 0.005);
    void AddEffect(Vec2 pos, float size, string imgName, double deathTime = 0.3);
    void Update();
    void Render();
    void Release();
};

#define PART cParticleManager::GetInstance()