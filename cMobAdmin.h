#pragma once
class cMobAdmin
{
public:
	cMobAdmin(vector<cBullet*>& bullet, string stage);
	~cMobAdmin();

	void Update();
	void Render();
	void UIRender();

	void Animation();

	bool isDestroy;

	Vec2 bossPos;

	vector<cMob*> m_mobs;
	vector<cBullet*>& m_bullets;

private:
	string stage;

	cTimer* t_DeadDelay = nullptr;

	void IsDestroy();
};

