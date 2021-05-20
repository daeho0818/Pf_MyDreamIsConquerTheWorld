#pragma once
#include "cBoss.h"
class cPlayer
{
public:
	cPlayer(cTexture* ptr[2]);
	~cPlayer();

	Vec2 m_pos = { 500, 500 };
	Vec2 bossPos;
	Vec2 startDrawPos;

	cTexture* BG[2];

	string itemName;

	cTimer* t_Speed = nullptr;
	cTimer* t_Invincibility = nullptr;

	DWORD* imgColor;

	RECT cellSize = {40, 300, WINSIZEX - 40, WINSIZEY - 40};

	int hp = 3;
	int coloring_cells = 0;
	int tempCount = 0;
	int last_x = 0, last_y = 0;
	int speed;
	int real_cells = (WINSIZEX - 80) * (WINSIZEY - 370);

	float coloring_per = 0;

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