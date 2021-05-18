#pragma once
#include "singleton.h"
class cSceneManager
	:public singleton<cSceneManager>
{
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

	map< string, cScene*> m_scenes;
	cScene* nowScene = nullptr;
	cScene* nextScene = nullptr;
	int Array[WINSIZEY][WINSIZEX];
	string curScene = "";
};

#define SCENE cSceneManager::GetInstance()