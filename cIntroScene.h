#pragma once
class cIntroScene
	:public cScene
{
public:
	cIntroScene();
	~cIntroScene();

	cTexture* intro[3];
	int index = 0;
	cTimer* ani = nullptr;
	bool once = true;
	float renderSize = 1;

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

