#pragma once
class cMobAdmin
{
public:
	cMobAdmin(vector<cBullet*>& bullet);
	~cMobAdmin();

	vector<cMob*> m_mobs;
	vector<cBullet*>& m_bullets;
	Vec2 bossPos;

	void Update();
	void Render();
	void UIRender();

	cMob* boss;
};

