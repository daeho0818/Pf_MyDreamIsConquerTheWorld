#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer(cTexture* ptr[2])
{
	BG[0] = ptr[0];
	BG[1] = ptr[1];
	Init();
}

cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	memset(SCENE->SCENE->Array, 0, sizeof(SCENE->Array));
	right = false; left = false; up = false; down = false;
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	imgColor = (DWORD*)lr.pBits;
	BG[0]->ptr->UnlockRect(0);

	t_Speed = nullptr;
	t_Invincibility = nullptr;

	hp = 5;
	coloring_cells = 0;
	last_x = 0, last_y = 0;
	speed = 10;
	real_cells = (WINSIZEX - 1) * (WINSIZEY - 1);
	coloring_per = 0;
	timer = 180;
	draw_line = false;
	draw_mode = false;
	returning = false;
	stop = false;
	invincibility = false;

	for (int y = WINSIZEY - 1; y != -1; --y)
		for (int x = WINSIZEX - 1; x != -1; --x)
			if (x == 0 || x == WINSIZEX - 1 || y == 0 + 1 || y == WINSIZEY - 2)
				SCENE->Array[y][x] = 1;
	draw_mode = true;
	DrawLine();
}

void cPlayer::Update(Vec2 bossPos)
{
	ItemUpdate();

	hRc = {
		0,
		0,
		(LONG)IMAGE->FindImage("hpBar")->info.Width / 10 * hp,
		(LONG)IMAGE->FindImage("hpBar")->info.Height / 2
	};

	this->bossPos = bossPos;

	sprintf(perText, "%.3f퍼센트", coloring_per);

	KeyEvent();

	//if (returning) Returning();

	Move();

	if (t_Speed != nullptr) t_Speed->Update();
	if (t_Invincibility != nullptr) t_Invincibility->Update();
	if (t_Timer != nullptr) t_Timer->Update();

	// 플레이어 애니메이션
	//if(t_Ani != nullptr) t_Ani->Update();
	//player = IMAGE->MakeVecImg("player");
	//int temp;
	//t_Ani = new cTimer(0.1, [&]()->void {
	//	if (index >= player.size())
	//		temp = -1;
	//	if (index <= 0)
	//		temp = 1;
	//		index += temp;
	//	});
	if (INPUT->KeyDown(VK_F11)) coloring_per = 100;

	if (t_Timer == nullptr)
	{
		t_Timer = new cTimer(1, [&]()->void {
			timer--;
			t_Timer = nullptr;
			});
	}
}

void cPlayer::Render()
{
	RENDER->CenterRender(BG[1], { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(BG[0], { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(IMAGE->FindImage("player"), m_pos, 0.1);

	char key[5] = "";
	sprintf(key, "%d", (int)coloring_per / 10);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(3000, 100));
	sprintf(key, "%d", (int)coloring_per % 10);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(3100, 100));
	RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(3200, 100));

	char time[5] = "";
	sprintf(time, "%d", timer / 60);
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 - 150, 100));
	sprintf(time, "%d", (timer % 60) / 10);
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2, 100));
	sprintf(time, "%d", abs((timer % 60) - (((timer % 60) / 10) * 10)));
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 + 100, 100));

	// 2분 40초
	// 1분 20초
}

void cPlayer::UIRender()
{
}

void cPlayer::Release()
{
	SAFE_DELETE(t_Speed);
	SAFE_DELETE(t_Invincibility);
	SAFE_DELETE(t_Timer);
}

void cPlayer::KeyEvent()
{
	if (INPUT->KeyDown(VK_LEFT))
		left = true;
	else if (INPUT->KeyDown(VK_RIGHT))
		right = true;
	else if (INPUT->KeyDown(VK_UP))
		up = true;
	else if (INPUT->KeyDown(VK_DOWN))
		down = true;

	if (INPUT->KeyUp(VK_LEFT))
		left = false;
	else if (INPUT->KeyUp(VK_RIGHT))
		right = false;
	else if (INPUT->KeyUp(VK_UP))
		up = false;
	else if (INPUT->KeyUp(VK_DOWN))
		down = false;

	if (INPUT->KeyDown(VK_SPACE))
	{
		draw_line = true;
		startDrawPos = m_pos;
	}
	if (INPUT->KeyUp(VK_SPACE))
	{
		returning = true;
		draw_line = false;
	}
}

void cPlayer::DrawTempLine()
{
	if (!draw_mode) draw_mode = true;
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;
	int index = int(m_pos.y) * WINSIZEX + int(m_pos.x);
	SCENE->Array[(int)m_pos.y][(int)m_pos.x] = 1;
	textureColor[index] = D3DCOLOR_RGBA(255, 0, 0, 255);
	BG[0]->ptr->UnlockRect(0);
}

void cPlayer::DrawLine(bool isFilled)
{
	if (!draw_mode) return;
	draw_mode = false;
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;
	for (int y = WINSIZEY - 1; y != -1; --y)
	{
		for (int x = WINSIZEX - 1; x != -1; --x)
		{
			D3DXCOLOR targetPixel = textureColor[y * WINSIZEX + x];
			switch (SCENE->Array[y][x])
			{
			case 0:
				targetPixel = imgColor[y * WINSIZEX + x];
				break;
			case 1:
				targetPixel = D3DCOLOR_RGBA(0, 255, 0, 255);
				last_x = x;
				last_y = y;
				SCENE->Array[y][x] = 2;
				break;
			case 3:
				targetPixel = D3DCOLOR_RGBA(0, 0, 0, 0);
				break;
			}
			textureColor[y * WINSIZEX + x] = targetPixel;
		}
	}
	BG[0]->ptr->UnlockRect(0);
	if (isFilled) return;
	if (last_x != 0 && last_y != 0)
	{
		FillPlace({ (float)bossPos.x, (float)bossPos.y }, 0, 4, true);
		for (int y = WINSIZEY - 2; y != 0; --y)
		{
			for (int x = WINSIZEX - 1; x != 0; --x)
			{
				if (SCENE->Array[y][x] == 0)
				{
					FillPlace({ (float)x - 1, (float)y - 1 }, 0, 3);
				}
			}
		}
		FillPlace({ (float)bossPos.x, (float)bossPos.y }, 4, 0, true);
		last_x = 0;
		last_y = 0;
	}
}

void cPlayer::FillPlace(Vec2 pos, int target, int change, bool isFilled)
{
	if (target == change) return;
	ChkLine();
	if (m_pos.y < 899 && m_pos.x < 1599)
		if (SCENE->Array[(int)pos.y + 1][(int)pos.x + 1] != target) return;
	queue<Vec2> v2q;

	SCENE->Array[(int)pos.y][(int)pos.x] = change;

	v2q.push(pos);
	if (!isFilled)
		coloring_cells++;

	while (!v2q.empty())
	{
		Vec2 n = v2q.front();
		v2q.pop();
		if (SCENE->Array[(int)n.y][(int)n.x - 1] == target)
		{
			SCENE->Array[(int)n.y][(int)n.x - 1] = change;
			v2q.push({ n.x - 1, n.y });
			if (!isFilled)
				coloring_cells++;
		}
		if (SCENE->Array[(int)n.y][(int)n.x + 1] == target)
		{
			SCENE->Array[(int)n.y][(int)n.x + 1] = change;
			v2q.push({ n.x + 1, n.y });
			if (!isFilled)
				coloring_cells++;
		}
		if (SCENE->Array[(int)n.y - 1][(int)n.x] == target)
		{
			SCENE->Array[(int)n.y - 1][(int)n.x] = change;
			v2q.push({ n.x, n.y - 1 });
			if (!isFilled)
				coloring_cells++;
		}
		if (SCENE->Array[(int)n.y + 1][(int)n.x] == target)
		{
			SCENE->Array[(int)n.y + 1][(int)n.x] = change;
			v2q.push({ n.x, n.y + 1 });
			if (!isFilled)
				coloring_cells++;
		}
	}
	if (!isFilled)
	{
		float temp1 = coloring_cells * 100;
		float temp2 = real_cells;
		coloring_per = temp1 / temp2;

		draw_mode = true;
		DrawLine(true);
	}
}

bool cPlayer::Near(BYTE dir, int target)
{
	switch (dir)
	{
	case VK_UP:
		return SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == target;
		break;
	case VK_DOWN:
		return SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == target;
		break;
	case VK_LEFT:
		return SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == target;
		break;
	case VK_RIGHT:
		return SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == target;
		break;
	}
}

int cPlayer::Current()
{
	return SCENE->Array[(int)m_pos.y][(int)m_pos.x];
}

void cPlayer::Move()
{
	if (!stop)
	{
		if (left)
		{
			if (m_pos.x != 0 || draw_line)
			{
				for (int i = 0; i < speed; i++)
				{
					ChkLine();
					if (!Near(VK_LEFT, 1) && (Near(VK_LEFT, 2) || draw_line))
					{
						m_pos.x--;
						if (Current() == 2)
							DrawLine();
						else
						{
							ChkLine();
							if (!Near(VK_LEFT, 3))
								DrawTempLine();
						}
					}
				}
			}
		}
		else if (right)
		{
			if (m_pos.x != WINSIZEX || draw_line)
			{
				for (int i = 0; i < speed; i++)
				{
					ChkLine();
					if (!Near(VK_RIGHT, 1) && (Near(VK_RIGHT, 2) || draw_line))
					{
						m_pos.x++;
						if (Current() == 2)
							DrawLine();
						else
						{
							ChkLine();
							if (!Near(VK_RIGHT, 3))
								DrawTempLine();
						}
					}
				}
			}
		}
		else if (up)
		{
			if (m_pos.y != 0 || draw_line)
			{
				for (int i = 0; i < speed; i++)
				{
					ChkLine();
					if (!Near(VK_UP, 1) && (Near(VK_UP, 2) || draw_line))
					{
						m_pos.y--;
						if (Current() == 2)
							DrawLine();
						else
						{
							ChkLine();
							if (!Near(VK_UP, 3))
								DrawTempLine();
						}
					}
				}
			}
		}
		else if (down)
		{
			if (m_pos.y != WINSIZEY - 1 || draw_line)
			{
				for (int i = 0; i < speed; i++)
				{
					ChkLine();
					if (!Near(VK_DOWN, 1) && (Near(VK_DOWN, 2) || draw_line))
					{
						m_pos.y++;
						if (Current() == 2)
							DrawLine();
						else
						{
							ChkLine();
							if (!Near(VK_DOWN, 3))
								DrawTempLine();
						}
					}
				}
			}
		}
	}
}

void cPlayer::ChkLine()
{
	if (m_pos.x >= WINSIZEX) m_pos.x = WINSIZEX; if (m_pos.x <= 0) m_pos.x = 0;
	if (m_pos.y >= WINSIZEY - 2) m_pos.y = WINSIZEY - 2; if (m_pos.y <= 0 + 1) m_pos.y = 0 + 1;
}

void cPlayer::Returning()
{
	if (m_pos == startDrawPos) { draw_mode = true; DrawLine(true); returning = false; return; }
	if (Near(VK_LEFT, 1))
	{
		SCENE->Array[(int)m_pos.y][(int)m_pos.x] = 0;
		m_pos.x--;
	}
	else if (Near(VK_RIGHT, 1))
	{
		SCENE->Array[(int)m_pos.y][(int)m_pos.x] = 0;
		m_pos.x++;
	}
	else if (Near(VK_UP, 1))
	{
		SCENE->Array[(int)m_pos.y][(int)m_pos.x] = 0;
		m_pos.y--;
	}
	else if (Near(VK_DOWN, 1))
	{
		SCENE->Array[(int)m_pos.y][(int)m_pos.x] = 0;
		m_pos.y++;
	}
	else
		m_pos = startDrawPos;
}

void cPlayer::ItemUpdate()
{
	string key;
	if (itemName == "Heal" || itemName == "Speed" || itemName == "invincibility")
	{
		key = itemName;
		EatItem(key);
	}
}

void cPlayer::EatItem(string key)
{
	if (key == "Heal")
	{
		if (hp < 5) hp += 1;
	}

	if (key == "Speed")
	{
		speed = 6;
		if (t_Speed == nullptr)
		{
			t_Speed = new cTimer(5, [&]()->void {
				speed = 3;
				t_Speed = nullptr;
				});
		}
	}

	if (key == "Invincibility")
	{
		invincibility = true;
		t_Invincibility = new cTimer(5, [&]()->void {
			invincibility = false;
			t_Invincibility = nullptr;
			});
	}
	itemName = "none";
}