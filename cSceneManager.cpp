#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	score = 0;
	mapNames[0] = "Church";
	mapNames[1] = "City";
	mapNames[2] = "CityNight";
	mapNames[3] = "Desert";
	mapNames[4] = "Jungle";
	mapNames[5] = "Ice";
	mapNames[6] = "Ocean";

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
	RENDER->CenterRender(IMAGE->FindImage("Cursor"),
		{
			float(MOUSE->mousePos.x * 2.1),
			float(MOUSE->mousePos.y * 2.1)
		}, 0.2);
}

void cSceneManager::UIRender()
{
	if (nowScene) nowScene->UIRender();
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