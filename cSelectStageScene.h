#pragma once
class cSelectStageScene
	:public cScene
{
public:
	cSelectStageScene();
	~cSelectStageScene();

	bool isFirst = true;
	int speed;

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

	Vec2 cloudsPos[4];

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void StageInfo(Stage stage);
	void SceneChange(Stage stage);
};

