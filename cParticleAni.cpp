#include "DXUT.h"
#include "cParticleAni.h"

cParticleAni::cParticleAni(Vec2 pos, float size, bool effect, int count, int kind, float frameTime)
	:cParticle(pos, size, effect, kind, frameTime), count(count)
{
	FrameTime = frameTime;
	if (kind == 0)
		m_images = IMAGE->MakeVecImg("Effect");
	else if (kind == 1)
		m_images = IMAGE->MakeVecImg("Effect");
	else if (kind == 2)
		m_images = IMAGE->MakeVecImg("Effect");
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
		RenderSize = 1.7f;
		if (count <= 50)
		{
			RenderSize = 1;
		}
		else if (count <= 100)
		{
			RenderSize = 0.7f;
		}
		else if (count <= 150)
		{
			RenderSize = 0.5f;
		}
		else
		{
			RenderSize = 1.7f;
		}
		RenderSize -= 0.1;
		if (m_ani == nullptr)
			m_ani = new cTimer(0.3f, [&]()->void {isDestroy = true; m_ani = nullptr; });
	}
}

void cParticleAni::Render()
{
	if (!effect)
		RENDER->CenterRender(IMAGE->FindImage("Effect"), m_pos, RenderSize);
	//RENDER->CenterRender(m_images[m_frame], m_pos, RenderSize);
	else
	{
		RENDER->CenterRender(IMAGE->FindImage("Effect"), m_pos, RenderSize);
	}
}
