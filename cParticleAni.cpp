#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size, int kind, float frameTime)
	:cParticle(pos, size, kind, frameTime)
{
	if (kind == 0) m_images = IMAGE->MakeVecImg("expl");
	FrameTime = frameTime;
	isDestroy = false;
}

cParticleAni::~cParticleAni()
{
	SAFE_DELETE(m_ani);
}

void cParticleAni::Update()
{
	if (m_ani != nullptr) m_ani->Update();
	if (m_bOnce)
	{
		m_ani = new cTimer(FrameTime, [&]()->void {
			m_frame++;
			if (m_frame == m_images.size())
				isDestroy = true;
			}, 1);
		m_bOnce = false;
	}
}

void cParticleAni::Render()
{
	RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);
}