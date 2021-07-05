#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size, double deathTime, double frameTime, bool effect, string imgName)
	:cParticle(pos, size, effect, frameTime), imgName(imgName), deathTime(deathTime)
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
			m_ani = new cTimer(frameTime, [&]()->void {
				m_frame++;
				if (m_frame == m_images.size())
					isDestroy = true;
				}, 1);
			m_bOnce = false;
		}
	}
	else
	{
		RenderSize -= 0.02;

		m_pos += {(float)(rand() % 20 - 10), (float)(rand() % 20 - 10) };

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
