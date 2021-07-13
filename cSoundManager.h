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
	map <string, LPDIRECTSOUNDBUFFER> m_channels;
	map<string, CSound*> m_sounds;

	LPDIRECTSOUNDBUFFER Play(string key,LONG volume = DSBVOLUME_MAX, bool loop = false);
	void Stop(string key);
	void StopAll();
	void AddSound(string key, wstring path);
};

#define SOUND cSoundManager::GetInstance()