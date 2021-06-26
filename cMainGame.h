#pragma once
class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	bool isLoadScene = true;

	void Init();
	void Update();
	void Render();
	void Release();
	void ResetDevice();
	void LostDevice();
};