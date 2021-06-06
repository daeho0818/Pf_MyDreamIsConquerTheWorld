#pragma once
class cLoadingScene
	:public cScene
{
public:
	cLoadingScene();
	~cLoadingScene();

	int loadCount = 0;
	int bundle = 0;

	cTimer* t_Delay = nullptr;

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void AddResource();
};

