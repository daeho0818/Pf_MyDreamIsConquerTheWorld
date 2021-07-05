#pragma once
class cPlayer
{
public:
	cPlayer(cTexture* ptr[2]);
	~cPlayer();

	void Init();
	void Update(Vec2 bossPos = Vec2());
	void Render();
	void UIRender();
	void Release();

	void EatItem(string key);
	void CamEvent();

private:
	Vec2 startDrawPos;

	cTimer* t_Speed = nullptr;
	cTimer* t_Invincibility = nullptr;
	cTimer* t_Fade = nullptr;
	cTimer* t_PFadeDelay = nullptr;
	cTimer* t_camMoveDelay = nullptr;

	D3DXCOLOR imgColor[WINSIZEY][WINSIZEX];

	RECT cellSize = { 40, 300, WINSIZEX - 40, WINSIZEY - 40 };
	
	D3DXCOLOR lineColor;

	int last_x = 0, last_y = 0;

	int real_cells = (WINSIZEX - 80) * (WINSIZEY - 370);
	int FadeCount;

	bool left, right, up, down;
	bool drawStart;
	bool draw_mode = false;
	bool stop = false;
	bool speedUp = false;
	bool camEvent = true;

	void KeyEvent();
	void DrawTempLine(BYTE dir);
	void DrawLine(bool isFilled = false);
	void FillPlace(Vec2 pos, int target, int change, bool isFilled = false);
	bool Near(BYTE dir, int target);
	int Current();

	void Move();
	void ChkLine();
	void Returning(bool isReturned = false );
	void ItemUpdate();

public:
	Vec2 m_pos;
	Vec2 bossPos;

	cTexture* player;

	int hp = 3;
	int coloring_cells = 0;
	int tempCount = 0;
	int speed;

	float coloring_per = 0;

	bool draw_line = false;
	bool returning = false;
	bool invincibility = false;
	bool isAttacked;
};