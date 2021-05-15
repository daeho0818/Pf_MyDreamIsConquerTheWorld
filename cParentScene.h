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
	
	int textCount = 1;
	bool isStart;
	bool isStop;
	bool isClear;
	bool isFail;

	float percent;
	float score;
	string curScene = "";

	cTimer* t_TextAni = nullptr;
	
	Vec2 textPos[5][3] = {
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}}
	};
};

