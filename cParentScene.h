#pragma once
class cParentScene abstract
{
public:
	virtual void StageStart(Vec2* curPos_, Vec2* curPos, Vec2* targetPos, float speed);
	virtual void StageClear();
	virtual void StageFail();
};

