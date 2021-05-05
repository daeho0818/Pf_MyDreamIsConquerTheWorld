#pragma once
#include "singleton.h"
class cSceneManager
	:public singleton<cSceneManager>
{
	map< string, cScene*> m_scenes;
	cScene* nowScene = nullptr;
	cScene* nextScene = nullptr;
public:
	cSceneManager();
	~cSceneManager();

	void Update();
	void Render();
	void UIRender();
	void Release();

	void AddScene(string key, cScene* scene);
	void ChangeScene(string key);
	void PlayerInit();
	void Cheat();

	int Array[WINSIZEY][WINSIZEX];
};

#define SCENE cSceneManager::GetInstance()