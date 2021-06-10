#include "DXUT.h"
#include "cReflexBullet.h"

cReflexBullet::cReflexBullet(Vec2 pos, Vec2 dir,cTexture* ptr, float damage, float size, float speed, bool dead)
	:cBullet(pos, dir, size),ptr(ptr), m_speed(speed), dead(dead)
{
	m_Damage = damage;
	bulletType = "mob";
}

cReflexBullet::~cReflexBullet()
{
	SAFE_DELETE(t_Dead);
}


void cReflexBullet::Update()
{
	if (t_Dead != nullptr) t_Dead->Update();
	if (dead)
	{
		if (t_Dead == nullptr)
			t_Dead = new cTimer(7, [&]()->void { t_Dead = nullptr; isDestroy = true; });
	}
	m_pos += m_Dir * m_speed * Delta;
	m_angle = atan2(m_Dir.y, m_Dir.x);

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		m_Dir.x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		m_Dir.y *= -1;
	}
}

void cReflexBullet::Render()
{
	RENDER->CenterRender(ptr, m_pos, size, -m_angle);
}

string cReflexBullet::ChkOut()
{
	if (m_pos.x > WINSIZEX - 40)
	{
		return "Right";
	}
	else if (m_pos.x < 40)
	{
		return "Left";
	}
	else if (m_pos.y < 300)
	{
		return "Up";
	}
	else if (m_pos.y > WINSIZEY - 40)
	{
		return "Down";
	}
	return "";
}
