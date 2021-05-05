#include "DXUT.h"
#include "cIntroScene.h"

cIntroScene::cIntroScene()
{
}

cIntroScene::~cIntroScene()
{
	Release();
}

void cIntroScene::Init()
{
	intro[0] = IMAGE->FindImage("intro1");
	intro[1] = IMAGE->FindImage("intro2");
	intro[2] = IMAGE->FindImage("intro3");
	index = 0; renderSize = 25;
	ani = nullptr; once = true;
}

void cIntroScene::Update()
{
	if (ani != nullptr) ani->Update();
	if (once)
	{
		once = false;
		ani = new cTimer(2, [&]()->void {
			index++;
			renderSize = 0;
			once = true;
			ani = nullptr;
			if (index == 2) renderSize = 25;
			if (index >= 3) SCENE->ChangeScene("cTitleScene");
			});
	}
	if (index == 0 || index == 2) renderSize -= 0.1;
	else renderSize += 0.1;
}

void cIntroScene::Render()
{
	RENDER->CenterRender(intro[index], { WINSIZEX / 2, WINSIZEY / 2 });
	if (index == 0) RENDER->CenterRender(IMAGE->FindImage("badEffect"), { 300, 300 }, renderSize);
	if (index == 1) RENDER->CenterRender(IMAGE->FindImage("fireEffect"), { 300, 300 }, renderSize);
	if (index == 2) RENDER->CenterRender(IMAGE->FindImage("angelEffect"), { 300, 300 }, renderSize);
}

void cIntroScene::UIRender()
{
}

void cIntroScene::Release()
{
	SAFE_DELETE(ani);
}
