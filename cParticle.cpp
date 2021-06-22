#include "DXUT.h"
#include "cParticle.h"

cParticle::cParticle(Vec2 pos, float size, bool effect, int kind, float frameTime)
	:m_pos(pos),effect(effect), RenderSize(size)
{
}

cParticle::~cParticle()
{
}
