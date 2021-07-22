#include "DXUT.h"
#include "cMBullet.h"

cMBullet::cMBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, string bulletType, float damage, float size, float speed)
	:cBullet(pos, dir, imgName, effectName, bulletType, size), m_speed(speed)
{
	m_Damage = damage;
	m_angle = atan2(m_Dir.y, m_Dir.x);
}

cMBullet::~cMBullet()
{
}

void cMBullet::Update()
{
	m_pos += m_Dir * m_speed * Delta;

	m_angle += 0.1;
}

void cMBullet::Render()
{
	RENDER->CenterRender(m_image, m_pos, size, -m_angle);
}
