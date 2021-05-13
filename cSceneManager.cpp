#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
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
}

void cSceneManager::Render()
{
	if (nowScene) nowScene->Render();
	RENDER->CenterRender(IMAGE->FindImage("player"),
		{ float(MOUSE->mousePos.x * 2.1),
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
	if (INPUT->KeyDown(VK_F6)) ChangeScene("cIngameScene");
	if (INPUT->KeyDown(VK_F7)) ChangeScene("cIngameScene2");
}
