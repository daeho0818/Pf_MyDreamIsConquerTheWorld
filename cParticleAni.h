#pragma once
#include "cParticle.h"
class cParticleAni
	:public cParticle
{
public:
	cParticleAni(Vec2 pos, float size, int kind, float frameTime = 0.005);
	virtual ~cParticleAni();

	vector<cTexture*> m_images;
	cTimer* m_ani = nullptr;
	int m_frame = 0;
	bool m_bOnce = true;
	float FrameTime;

	// cParticle을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};