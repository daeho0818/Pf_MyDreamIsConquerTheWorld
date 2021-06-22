#pragma once
class cParticle
{
public:
	cParticle(Vec2 pos, float size, bool effect, int kind, float frameTime = 0.005);
	virtual ~cParticle();

	virtual void Update() = 0;
	virtual void Render() = 0;

	Vec2 m_pos; 
	float RenderSize;
	bool effect;
	bool isDestroy = false;
};

