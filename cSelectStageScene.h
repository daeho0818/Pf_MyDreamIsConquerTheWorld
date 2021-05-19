#pragma once
class cSelectStageScene
	:public cScene
{
public:
	cSelectStageScene();
	~cSelectStageScene();

	bool isFirst = true;

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
	bool stageOpen = false;

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void StageInfo(Stage stage);
	void SceneChange(Stage stage);
};

