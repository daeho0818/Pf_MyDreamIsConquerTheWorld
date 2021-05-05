#pragma once
#include "singleton.h"
class cSoundManager
	:public singleton<cSoundManager>
{
public:
	CSoundManager m_Manager;
	list<LPDIRECTSOUNDBUFFER> m_channels;
	map<string, CSound*> m_sounds;

	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Release();

	LPDIRECTSOUNDBUFFER Play(string key, bool loop = false);
	void StopAll();
	void AddSound(string key, wstring path);
};

#define SOUND cSoundManager::GetInstance()