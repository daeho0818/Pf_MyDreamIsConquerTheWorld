#pragma once
class cSelectStageScene
	:public cScene
{
public:
	cSelectStageScene();
	~cSelectStageScene();

	bool isFirst = true;

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};
