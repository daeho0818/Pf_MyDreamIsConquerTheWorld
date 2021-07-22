#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, string bulletType, float size)
	:m_pos(pos), m_Dir(dir), size(size), effectName(effectName), bulletType(bulletType)
{
	m_image = IMAGE->FindImage(imgName);
}

cBullet::~cBullet()
{
}

bool cBullet::IsOutMap()
{
	return (m_pos.x - size < -200
		|| m_pos.x - size > WINSIZEX + 200
		|| m_pos.y - size < -200
		|| m_pos.y - size > WINSIZEY + 200);
}
