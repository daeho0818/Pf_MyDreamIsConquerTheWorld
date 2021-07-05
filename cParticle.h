#pragma once
class cParticle
{
public:
	cParticle(Vec2 pos, float size, bool effect, float frameTime);
	virtual ~cParticle();

	virtual void Update() = 0;
	virtual void Render() = 0;

	Vec2 m_pos; 

	vector<cTexture*> m_images;

	float RenderSize;
	float frameTime;

	bool effect;
	bool isDestroy = false;
};

