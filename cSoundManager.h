#pragma once
#include "singleton.h"
class cSoundManager
	:public singleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Release();

	CSoundManager m_Manager;
	list < LPDIRECTSOUNDBUFFER> m_channels;
	map<string, CSound*> m_sounds;

	LPDIRECTSOUNDBUFFER Play(string key,float volume = 1, bool loop = false);
	void StopAll();
	void AddSound(string key, wstring path);
};

#define SOUND cSoundManager::GetInstance()