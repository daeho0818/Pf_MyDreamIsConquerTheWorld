#pragma once
#include "singleton.h"
class cImageManager
	:public singleton<cImageManager>
{
	map<string, cTexture*> m_images;
public:
	cImageManager();
	~cImageManager();

	void AddImage(const string& key, const string& path, int count = 0);
	cTexture* FindImage(const string& key);
	vector<cTexture*> MakeVecImg(const string& key);
	void DeleteImage(const string& key);
};

#define IMAGE cImageManager::GetInstance()