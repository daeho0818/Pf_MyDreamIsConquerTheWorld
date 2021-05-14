#include "DXUT.h"
#include "cParentScene.h"

void cParentScene::StageStart(Vec2* curPos_, Vec2* curPos, Vec2* targetPos, float speed)
{
	D3DXVec2Lerp(curPos_, curPos, targetPos, speed);
}

void cParentScene::StageClear()
{
}

void cParentScene::StageFail()
{
}
