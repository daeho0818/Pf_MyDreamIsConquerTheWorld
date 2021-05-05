#include "DXUT.h"
#include "cMBullet.h"

cMBullet::cMBullet(Vec2 pos, Vec2 dir, float damage, float size, float speed)
	:cBullet(pos, dir, size), m_speed(speed)
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
	RENDER->CenterRender(IMAGE->FindImage("bullet_enemy"), m_pos, 1, -m_angle);
}
