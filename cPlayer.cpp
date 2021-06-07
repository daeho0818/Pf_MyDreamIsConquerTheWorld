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
	memset(SCENE->Array, 0, sizeof(SCENE->Array));
	right = false; left = false; up = false; down = false;

	player = IMAGE->FindImage("player");

	t_Speed = nullptr;
	t_Invincibility = nullptr;
	t_Fade = nullptr;

	hp = 3;
	coloring_cells = 0;
	last_x = 0, last_y = 0;
	speed = 15;
	coloring_per = 0;
	FadeCount = 0;
	drawStart = false;
	draw_line = false;
	draw_mode = false;
	returning = false;
	stop = false;
	invincibility = false;
	isAttacked = false;

	m_pos = { 40, 300 };
	cellSize = { 40, 300, WINSIZEX - 40, WINSIZEY - 40 };

	for (int y = cellSize.bottom; y != cellSize.top - 1; --y)
	{
		for (int x = cellSize.right; x != cellSize.left - 1; --x)
		{
			if (x == cellSize.left || x == cellSize.right || y == cellSize.top || y == cellSize.bottom)
			{
				SCENE->Array[y - 2][x] = 1;
				SCENE->Array[y - 1][x] = 1;
				SCENE->Array[y + 1][x] = 1;
				SCENE->Array[y + 2][x] = 1;
				SCENE->Array[y][x] = 1;
				SCENE->Array[y][x - 2] = 1;
				SCENE->Array[y][x - 1] = 1;
				SCENE->Array[y][x + 1] = 1;
				SCENE->Array[y][x + 2] = 1;
			}
			else if (x < cellSize.left || x > cellSize.right || y < cellSize.top || y > cellSize.bottom)
				SCENE->Array[y][x] = 3;
		}
	}
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* imgPixel = (DWORD*)lr.pBits;
	for (int y = 0; y < WINSIZEY; y++)
		for (int x = 0; x < WINSIZEX; x++)
			imgColor[y][x] = (D3DXCOLOR)imgPixel[y * WINSIZEX + x];
	BG[0]->ptr->UnlockRect(0);

	draw_mode = true;
	DrawLine(true);

	ChkLine();
}

void cPlayer::Update(Vec2 bossPos)
{
	if (t_Fade != nullptr) t_Fade->Update();
	ItemUpdate();

	this->bossPos = bossPos;

	KeyEvent();

	if (isAttacked)
	{
		if (!invincibility)
			player = IMAGE->FindImage("h_player");
		invincibility = true;
		if (FadeCount < 5)
		{
			if (t_Fade == nullptr)
			{
				t_Fade = new cTimer(0.5, [&]()->void {
					if (FadeCount % 2 != 0)
						player = IMAGE->FindImage("h_player");
					else
						player = IMAGE->FindImage("player");
					FadeCount++;
					t_Fade = nullptr;
					});
			}
		}
		else
		{
			isAttacked = false;
			invincibility = false;
			FadeCount = 0;
		}
	}

	if (returning) Returning();

	Move();

	if (t_Speed != nullptr) t_Speed->Update();
	if (t_Invincibility != nullptr) t_Invincibility->Update();
}

void cPlayer::Render()
{
	RENDER->CenterRender(BG[1], { WINSIZEX / 2, WINSIZEY / 2 });
	if (coloring_per < 80)
		RENDER->CenterRender(BG[0], { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(player, m_pos, 0.2);

	char t_hp[5] = "";
	sprintf(t_hp, "%d", hp);
	RENDER->CenterRender(IMAGE->FindImage(t_hp), Vec2(100, 100));
}

void cPlayer::UIRender()
{
}

void cPlayer::Release()
{
	SAFE_DELETE(t_Speed);
	SAFE_DELETE(t_Invincibility);
	SAFE_DELETE(t_Fade);
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
	else if (INPUT->KeyUp(VK_SPACE))
	{
		draw_line = false;
		if (Current() == 1)
		{
			returning = true;
		}
	}

	if (INPUT->KeyDown(VK_RETURN))
	{
		
	}
}

void cPlayer::DrawTempLine(BYTE dir)
{
	if (!draw_mode) draw_mode = true;
	if (!drawStart) startDrawPos = m_pos;
	drawStart = true;
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;

	if (dir == VK_LEFT || dir == VK_RIGHT)
	{
		SCENE->Array[int(m_pos.y - 1)][int(m_pos.x)] = 9;
		int index = int(m_pos.y - 1) * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);

		SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 1;
		index = (int)m_pos.y * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);

		SCENE->Array[int(m_pos.y + 1)][int(m_pos.x)] = 9;
		index = int(m_pos.y + 1) * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);
	}
	else if (dir == VK_UP || dir == VK_DOWN)
	{
		SCENE->Array[int(m_pos.y)][int(m_pos.x - 1)] = 9;
		int index = (int)m_pos.y * WINSIZEX + int(m_pos.x - 1);
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);

		SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 1;
		index = (int)m_pos.y * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);

		SCENE->Array[int(m_pos.y)][int(m_pos.x + 1)] = 9;
		index = (int)m_pos.y * WINSIZEX + int(m_pos.x + 1);
		textureColor[index] = D3DCOLOR_RGBA(155, 155, 155, 255);
	}
	BG[0]->ptr->UnlockRect(0);
}

void cPlayer::DrawLine(bool isFilled)
{
	if (!draw_mode) return;
	draw_mode = false;
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;

	for (int y = cellSize.bottom + 1; y != cellSize.top - 1; --y)
	{
		for (int x = cellSize.right + 1; x != cellSize.left - 1; --x)
		{
			D3DXCOLOR targetPixel;
			switch (SCENE->Array[y][x])
			{
			case 1:
				if (returning)
				{
					targetPixel = imgColor[y][x];
					SCENE->Array[y][x] = 0;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				else
				{
					targetPixel = D3DXCOLOR(0, 0, 0, 1);
					SCENE->Array[y][x] = 2;
					last_x = x;
					last_y = y;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				break;
			case 3:
				targetPixel = D3DXCOLOR(0, 0, 0, 0);
				textureColor[y * WINSIZEX + x] = targetPixel;
				break;
			case 9:
				if (returning)
				{
					targetPixel = imgColor[y][x];
					SCENE->Array[y][x] = 0;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				else
				{
					targetPixel = D3DXCOLOR(0, 0, 0, 1);
					SCENE->Array[y][x] = 2;
					last_x = x;
					last_y = y;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				break;
			}
		}
	}
	BG[0]->ptr->UnlockRect(0);
	if (isFilled) return;
	if (last_x != cellSize.left && last_y != cellSize.top)
	{
		drawStart = false;
		FillPlace({ (float)bossPos.x, (float)bossPos.y }, 0, 4, true);
		for (int y = cellSize.bottom - 1; y != cellSize.top; --y)
		{
			for (int x = cellSize.right - 1; x != cellSize.left; --x)
			{
				if (SCENE->Array[y][x] == 0)
				{
					FillPlace({ (float)x, (float)y }, 0, 3);
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
	queue<Vec2> v2q;

	SCENE->Array[(int)pos.y][(int)pos.x] = change;

	v2q.push(pos);
	if (!isFilled)
		coloring_cells++;

	while (!v2q.empty())
	{
		Vec2 n = v2q.front();
		v2q.pop();

		if (SCENE->Array[(int)n.y][(int)n.x - 1] == target && n.x - 1 > cellSize.left)
		{
			SCENE->Array[(int)n.y][(int)n.x - 1] = change;
			v2q.push({ n.x - 1, n.y });
			if (!isFilled)
				coloring_cells++;
		}
		if (SCENE->Array[(int)n.y][(int)n.x + 1] == target && n.x + 1 < cellSize.right)
		{
			SCENE->Array[(int)n.y][(int)n.x + 1] = change;
			v2q.push({ n.x + 1, n.y });
			if (!isFilled)
				coloring_cells++;
		}

		if (SCENE->Array[(int)n.y - 1][(int)n.x] == target && n.y - 1 > cellSize.top)
		{
			SCENE->Array[(int)n.y - 1][(int)n.x] = change;
			v2q.push({ n.x, n.y - 1 });
			if (!isFilled)
				coloring_cells++;
		}
		if (SCENE->Array[(int)n.y + 1][(int)n.x] == target && n.y + 1 < cellSize.bottom)
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
		SCENE->score += coloring_per * 10;

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
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (Near(VK_LEFT, 2) || !Near(VK_LEFT, 1) && draw_line)
				{
					m_pos.x--;
					if (Current() == 2 && m_pos != startDrawPos)
						DrawLine();
					else
					{
						ChkLine();
						if (!Near(VK_LEFT, 3))
							DrawTempLine(VK_LEFT);
					}
				}
			}
		}
		else if (right)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (Near(VK_RIGHT, 2) || !Near(VK_RIGHT, 1) && draw_line)
				{
					m_pos.x++;
					if (Current() == 2 && m_pos != startDrawPos)
						DrawLine();
					else
					{
						ChkLine();
						if (!Near(VK_RIGHT, 3))
							DrawTempLine(VK_RIGHT);
					}
				}
			}
		}
		else if (up)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (Near(VK_UP, 2) || !Near(VK_UP, 1) && draw_line)
				{
					m_pos.y--;
					if (Current() == 2 && m_pos != startDrawPos)
						DrawLine();
					else
					{
						ChkLine();
						if (!Near(VK_UP, 3))
							DrawTempLine(VK_UP);
					}
				}
			}
		}
		else if (down)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (Near(VK_DOWN, 2) || !Near(VK_DOWN, 1) && draw_line)
				{
					m_pos.y++;
					if (Current() == 2 && m_pos != startDrawPos)
						DrawLine();
					else
					{
						ChkLine();
						if (!Near(VK_DOWN, 3))
							DrawTempLine(VK_DOWN);
					}
				}
			}
		}
	}
}

void cPlayer::ChkLine()
{
	if (m_pos.x >= cellSize.right) m_pos.x = cellSize.right; if (m_pos.x <= cellSize.left) m_pos.x = cellSize.left;
	if (m_pos.y >= cellSize.bottom) m_pos.y = cellSize.bottom; if (m_pos.y <= cellSize.top) m_pos.y = cellSize.top;
}

void cPlayer::Returning()
{
	D3DLOCKED_RECT lr;
	BG[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;
	for (int i = 0; i < speed; i++)
	{
		D3DXCOLOR targetPixel;
		if (Near(VK_LEFT, 1))
		{
			targetPixel = imgColor[(int)m_pos.y - 1][(int)m_pos.x];
			textureColor[int(m_pos.y - 1) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y - 1)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y + 1][(int)m_pos.x];
			textureColor[int(m_pos.y + 1) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y + 1)][int(m_pos.x)] = 0;
			m_pos.x--;
		}
		else if (Near(VK_RIGHT, 1))
		{
			targetPixel = imgColor[(int)m_pos.y - 1][(int)m_pos.x];
			textureColor[int(m_pos.y - 1) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y - 1)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y + 1][(int)m_pos.x];
			textureColor[int(m_pos.y + 1) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y + 1)][int(m_pos.x)] = 0;
			m_pos.x++;
		}
		else if (Near(VK_DOWN, 1))
		{
			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x - 1];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x - 1)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x - 1)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x + 1];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x + 1)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x + 1)] = 0;
			m_pos.y++;
		}
		else if (Near(VK_UP, 1))
		{
			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x - 1];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x - 1)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x - 1)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 0;

			targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x + 1];
			textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x + 1)] = targetPixel;
			SCENE->Array[int(m_pos.y)][int(m_pos.x + 1)] = 0;
			m_pos.y--;
		}
		else
		{
			draw_line = false;
			returning = false;
			m_pos = startDrawPos;
		}
	}
	BG[0]->ptr->UnlockRect(0);
}

void cPlayer::ItemUpdate()
{
	if (hp <= 0) hp = 0;
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
		if (hp < 3) hp += 1;
		SCENE->score += 50;
	}

	if (key == "Speed")
	{
		speed = 25;
		if (t_Speed == nullptr)
		{
			t_Speed = new cTimer(5, [&]()->void {
				speed = 15;
				t_Speed = nullptr;
				});
		}
		SCENE->score += 75;
	}

	if (key == "Invincibility")
	{
		invincibility = true;
		t_Invincibility = new cTimer(5, [&]()->void {
			invincibility = false;
			t_Invincibility = nullptr;
			});
		SCENE->score += 100;
	}
	itemName = "none";
}