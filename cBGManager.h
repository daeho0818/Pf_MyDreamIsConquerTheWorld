#pragma once
#include "singleton.h"
class cBGManager
	:public singleton<cBGManager>
{
public:
	cBGManager();
	~cBGManager();

	bool isLoadScene = true;

	cTexture* ptr[2];

	void Render();
};
#define BG cBGManager::GetInstance()