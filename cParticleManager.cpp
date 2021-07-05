#include "DXUT.h"
#include "cParticleAni.h"
#include "cParticleManager.h"

cParticleManager::cParticleManager()
{
}

cParticleManager::~cParticleManager()
{
	Release();
}

void cParticleManager::AddParticle(Vec2 pos, float size, string imgName, double frameTime)
{
	cParticle* par = new cParticleAni(pos, size, 0, frameTime, false, imgName);
	m_particles.push_back(par);
}

void cParticleManager::AddEffect(Vec2 pos, float size, string imgName, double deathTime)
{
	cParticle* par = new cParticleAni(pos, size, deathTime, 1, true, imgName);
	m_particles.push_back(par);
}

void cParticleManager::Update()
{
	for (auto iter : m_particles) iter->Update();
	for (auto iter = m_particles.begin(); iter != m_particles.end();)
	{
		if ((*iter)->isDestroy)
		{
			SAFE_DELETE((*iter));
			iter = m_particles.erase(iter);
		}
		else
			iter++;
	}
}

void cParticleManager::Render()
{
	for (auto iter : m_particles) iter->Render();
}

void cParticleManager::Release()
{
	for (auto iter : m_particles) SAFE_DELETE(iter);
	m_particles.clear();
}