#pragma once
class cParentScene abstract
{
public:
	cParentScene();
	~cParentScene();

	virtual void Init(string curScene);
	virtual void Update();
	virtual void Render();

	virtual void StageStart(Vec2* curPos_, Vec2* curPos, Vec2* targetPos, float speed);
	virtual void StageClear();
	virtual void StageFail();

	virtual void SetPercent(float percent);
	virtual void SetScore(float score);
	virtual void SetHP(int hp);
	
	int textCount;
	int timer;
	int CFCount;
	int delayCount;
	int hp;

private:
	int score;

public:
	bool isStart;
	bool isStop;
	bool isClear;
	bool isFail;
	bool isClearEnd;
	bool isFailEnd;
	bool delay;

	bool clear[7];
	bool over[4];
	bool textRender[7];

	float percent;
	float speed;

	cTimer* t_TextAni = nullptr;
	cTimer* t_Timer = nullptr;
	cTimer* t_Clear = nullptr;
	cTimer* t_Over = nullptr;
	cTimer* t_Delay = nullptr;

	cTexture* BG = nullptr;

	Vec2 textsPos[7];
};

