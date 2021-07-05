#pragma once
class cEndScene
	:public cScene
{
public:
	cEndScene();
	~cEndScene();

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	int index = 0;
	int count = 0;
	int operY[9] = { 0, };

	bool isAniStart = true;
	bool isTextUp = true;

	cTimer* t_AniTerm = nullptr;
	cTimer* t_AniDelay = nullptr;

	void TextUpOrDown();
};

