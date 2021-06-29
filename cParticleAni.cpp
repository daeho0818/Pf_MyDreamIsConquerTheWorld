#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size, double deathTime, bool effect, string imgName, float frameTime)
	:cParticle(pos, size, effect, frameTime), imgName(imgName), deathTime(deathTime), FrameTime(FrameTime)
{
	m_images = IMAGE->MakeVecImg(imgName);

	isDestroy = false;
}

cParticleAni::~cParticleAni()
{
	SAFE_DELETE(m_ani);
}

void cParticleAni::Update()
{
	if (m_ani != nullptr) m_ani->Update();
	if (!effect)
	{
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
	else
	{
		if (m_ani == nullptr)
			m_ani = new cTimer(deathTime, [&]()->void {isDestroy = true; m_ani = nullptr; });
	}
}

void cParticleAni::Render()
{
	if (!effect)
		RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);

	else
	{
		RENDER->CenterRender(IMAGE->FindImage(imgName), m_pos, RenderSize);
	}
}
