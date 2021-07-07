#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	Init();
}

cSoundManager::~cSoundManager()
{
	Release();
}

void cSoundManager::Init()
{
	m_Manager.Initialize(DXUTGetHWND(), 1);
}

void cSoundManager::Update()
{
	DWORD status;
	for (auto& iter = m_channels.begin(); iter != m_channels.end();)
	{
		(*iter)->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			(*iter)->Release();
			iter = m_channels.erase(iter);
		}
		else
			iter++;
	}
}

void cSoundManager::Release()
{
	for (auto iter : m_sounds) delete iter.second;
	for (auto iter : m_channels) iter->Release();
}

LPDIRECTSOUNDBUFFER cSoundManager::Play(string key,float volume, bool loop)
{
	LPDIRECTSOUNDBUFFER sb;
	m_Manager.GetDirectSound()->DuplicateSoundBuffer(m_sounds[key]->GetBuffer(0), &sb);
	sb->SetVolume(volume);
	sb->Play(0, 0, loop == true ? DSBPLAY_LOOPING : 0);
	m_channels.push_back(sb);
	return sb;
}

void cSoundManager::StopAll()
{
	for (auto iter : m_channels) iter->Release();
	m_channels.clear();
}

void cSoundManager::AddSound(string key, wstring path)
{
	CSound* sound;
	wchar_t Path[128];
	swprintf(Path, L"./Resource/Sound/%s.wav", path.c_str());
	m_Manager.Create(&sound, Path, DSBCAPS_CTRLVOLUME);
	m_sounds.insert(make_pair(key, sound));
}