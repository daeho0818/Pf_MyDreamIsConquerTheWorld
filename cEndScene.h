#pragma once
class cEndScene
	:public cScene
{
public:
	cEndScene();
	~cEndScene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

