#pragma once
#include "singleton.h"
class cThreadManager
	:public singleton<cThreadManager>
{
public:
	cThreadManager();
	~cThreadManager();

	map<string, thread> th;

	void Update();

	void AddThread(string str, function<void()> func);
	void ReleaseThread(string str);
};
#define THREAD cThreadManager::GetInstance()