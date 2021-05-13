#pragma once
#include "cBoss.h"
class cPlayer
{
public:
	cPlayer(cTexture* ptr[2]);
	~cPlayer();

	int Stage;
	int index = 0;

	Vec2 m_pos = { 0, 0 };
	Vec2 bossPos;
	Vec2 startDrawPos;

	RECT hRc;

	cTexture* BG[2];

	vector<cTexture*> player;

	string itemName;

	cTimer* t_Speed = nullptr;
	cTimer* t_Invincibility = nullptr;
	cTimer* t_Ani = nullptr;

	DWORD* imgColor;

	int hp = 5;
	int coloring_cells = 0;
	int last_x = 0, last_y = 0;
	int speed = 3;
	int real_cells = (WINSIZEX - 1) * (WINSIZEY - 1);
	int saveHp = 0;

	float coloring_per = 0;

	char perText[128] = "";

	bool left, right, up, down;
	bool draw_line = false;
	bool draw_mode = false;
	bool returning = false;
	bool stop = false;
	bool invincibility = false;

	void Init();
	void Update(Vec2 bossPos);
	void Render();
	void UIRender();
	void Release();

	void KeyEvent();
	void DrawTempLine();
	void DrawLine(bool isFilled = false);
	void FillPlace(Vec2 pos, int target, int change, bool isFilled = false);
	bool Near(BYTE dir, int target);
	int Current();

	void Move();
	void ChkLine();
	void Returning();
	void ItemUpdate();
	void EatItem(string key);
};