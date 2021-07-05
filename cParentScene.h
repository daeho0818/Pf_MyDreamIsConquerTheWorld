#pragma once
class cParentScene abstract
{
public:
	cParentScene();
	~cParentScene();

	virtual void Init(string curScene);
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();

	virtual void StageStart(Vec2* curPos_, Vec2* curPos, Vec2* targetPos, float speed);

	void SetPercent(float percent);
	void SetScore(float score);
	void SetHP(int hp);
	void SetBossPos(Vec2 bossPos);

	int textCount;
	int timer;
	int CFCount;
	int delayCount;

private:
	int score;
	int alphaColor = 255;
	int hp;

	bool waitToStart = true;
	bool clear[7];
	bool over[4];
	bool textRender[7];
	bool isFadeOut = true;

	cTimer* t_TextAni = nullptr;
	cTimer* t_Timer = nullptr;
	cTimer* t_Clear = nullptr;
	cTimer* t_Over = nullptr;
	cTimer* t_Delay = nullptr;
	cTimer* t_WaitToStart = nullptr;
	cTimer* t_TimeFade = nullptr;

	Vec2 textsPos[7];
	Vec2 bossPos;

public:
	bool isStart;
	bool isStop;
	bool isClear;
	bool isFail;
	bool isClearEnd;
	bool isFailEnd;
	bool delay;

	float percent;
	float speed;

	cTexture* t_BG = nullptr;
};

