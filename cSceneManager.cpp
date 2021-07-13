#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	score = 0;
	mapNames[0] = "cChurchScene";
	mapNames[1] = "cCityScene";
	mapNames[2] = "cCityNightScene";
	mapNames[3] = "cDesertScene";
	mapNames[4] = "cJungleScene";
	mapNames[5] = "cIceScene";
	mapNames[6] = "cOceanScene";

	for (int i = 0; i < 7; i++)
	{
		m_rewards.insert(make_pair(mapNames[i], 0));
	}
}

cSceneManager::~cSceneManager()
{
	Release();
}

void cSceneManager::Update()
{
	if (nowScene) nowScene->Update();
	if (nextScene)
	{
		if (nowScene) nowScene->Release();

		for (auto iter : BUTTON->m_buttons)
			SAFE_DELETE(iter);
		BUTTON->m_buttons.clear();
		BUTTON->buttonRects.clear();
		BUTTON->buttonPos.clear();

		nextScene->Init();
		nowScene = nextScene;
		nextScene = nullptr;
	}

	Cheat();

	for (int i = 0; i < 7; i++)
		a_rewards[i] = m_rewards.find(mapNames[i])->second;
}

void cSceneManager::Render()
{
	if (nowScene) nowScene->Render();
}

void cSceneManager::UIRender()
{
	if (nowScene) nowScene->UIRender();

	UI->CenterRender(IMAGE->FindImage("Cursor"), MOUSE->mousePos, 0.1);
}

void cSceneManager::Release()
{
	if (nowScene) nowScene->Release();
	for (auto iter : m_scenes) SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(string key, cScene* scene)
{
	m_scenes.insert(make_pair(key, scene));
}

void cSceneManager::ChangeScene(string key)
{
	auto iter = m_scenes.find(key);
	nextScene = (*iter).second;
}

void cSceneManager::PlayerInit()
{
}

void cSceneManager::Cheat()
{
	if (INPUT->KeyDown(VK_F5)) ChangeScene("cTitleScene");
	if (INPUT->KeyDown(VK_F6)) ChangeScene("cSelectStageScene");
}