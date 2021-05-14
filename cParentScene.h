#pragma once
class cParentScene abstract
{
	virtual void StageStart() = 0;
	virtual void StageClear() = 0;
	virtual void StageFail() = 0;
};

