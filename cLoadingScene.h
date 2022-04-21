#pragma once

#include "cTitleScene.h"
#include "cSelectStageScene.h"
#include "cIceScene.h"
#include "cCityScene.h"
#include "cCityNightScene.h"
#include "cChurchScene.h"
#include "cJungleScene.h"
#include "cDesertScene.h"
#include "cOceanScene.h"
#include "cEndScene.h"

struct LoadInfo
{
	LoadInfo(string key, string path, int count) : key(key), path(path), count(count) {}
	string key;
	string path;
	int count;
};

class cLoadingScene
	:public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();


	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void AddLoad(string key, string path, int count = 0);

	list<LoadInfo> loadList;
	list <function<void()>> loadScenes;

	int listCount;

	bool loadStart = false;
};

