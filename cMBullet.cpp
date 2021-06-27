#include "DXUT.h"
#include "cMBullet.h"

cMBullet::cMBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, float damage, float size, float speed)
	:cBullet(pos, dir, imgName, effectName, size), m_speed(speed)
{
	m_Damage = damage;
	bulletType = "mob";
}

cMBullet::~cMBullet()
{
}

void cMBullet::Update()
{
	m_pos += m_Dir * m_speed * Delta;
	m_angle = atan2(m_Dir.y, m_Dir.x);
}

void cMBullet::Render()
{
	RENDER->CenterRender(m_image, m_pos, size, -m_angle);
}
