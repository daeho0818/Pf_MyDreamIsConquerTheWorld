#pragma once
class cSelectStageScene
	:public cScene
{
public:
	cSelectStageScene();
	~cSelectStageScene();

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

private:
	bool isFirst = true;
	bool stageOpen = false;

	int speed;

	float operY;

	enum Stage
	{
		Ice,
		City,
		City_Night,
		Church,
		Desert,
		Ocean,
		Jungle,
		None
	};
	Stage stage = Stage::None;

	Vec2 cloudsPos[4];
	Vec2 operPos;

	void StageInfo(Stage stage);
	void SceneChange(Stage stage);
};

