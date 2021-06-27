#include "DXUT.h"
#include "cThreadManager.h"

cThreadManager::cThreadManager()
{
}

cThreadManager::~cThreadManager()
{
	for (auto iter = th.begin(); iter != th.end(); ++iter)
	{
		iter->second.join();
	}
	th.clear();
}

void cThreadManager::Update()
{
}

void cThreadManager::AddThread(string str, function<void()> func)
{
	th.insert(make_pair(str, func));
}

void cThreadManager::ReleaseThread(string str)
{
	th.find(str)->second.join();
	th.erase(str);
}