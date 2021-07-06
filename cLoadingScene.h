#pragma once

struct LoadInfo
{
	LoadInfo(string key, string path, int count) : key(key), path(path), count(count) {}
	string key;
	string path;
	int count;
};

class cLoadingScene
	:public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();


	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	void AddLoad(string key, string path, int count = 0);
	void AddResource();

	list<LoadInfo> loadList;

	cThreadPool* thread = nullptr;

	int listCount;
};

