#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer(cTexture* ptr[2])
{
	BG->ptr[0] = ptr[0];
	BG->ptr[1] = ptr[1];

	Init();
}

cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	CAM->MoveCam({ WINSIZEX / 2, WINSIZEY / 2 });

	memset(SCENE->Array, 0, sizeof(SCENE->Array));
	right = false; left = false; up = false; down = false;

	player = IMAGE->FindImage("player");

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
	isHp = false;
	speedUp = false;
	invincibility = false;
	isAttacked = false;
	camEvent = true;
	render = true;

	m_pos = { 40, WINSIZEY / 2 };
	cellSize = { 40, 300, WINSIZEX - 40, WINSIZEY - 40 };

	if (SCENE->curScene == "cChurchScene")
	{
		lineColor = D3DCOLOR_RGBA(255, 255, 150, 255);
	}
	else if (SCENE->curScene == "cCityNightScene")
	{
		lineColor = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (SCENE->curScene == "cCityScene")
	{
		lineColor = D3DCOLOR_RGBA(255, 124, 170, 255);
	}
	else if (SCENE->curScene == "cDesertScene")
	{
		lineColor = D3DCOLOR_RGBA(100, 0, 50, 255);
	}
	else if (SCENE->curScene == "cIceScene")
	{
		lineColor = D3DCOLOR_RGBA(255, 255, 150, 255);
	}
	else if (SCENE->curScene == "cJungleScene")
	{
		lineColor = D3DCOLOR_RGBA(173, 77, 255, 255);
	}
	else if (SCENE->curScene == "cOceanScene")
	{
		lineColor = D3DCOLOR_RGBA(255, 150, 0, 255);
	}

	for (int y = WINSIZEY - 12; y != 9; --y)
	{
		for (int x = WINSIZEX - 12; x != 9; --x)
		{
			if (x == cellSize.left || x == cellSize.right || y == cellSize.top || y == cellSize.bottom)
			{
				for (int i = -10; i < 10; i++)
				{
					SCENE->Array[y - i][x] = 1;
					SCENE->Array[y][x - i] = 1;
				}
			}
			else if (x < cellSize.left || x > cellSize.right || y < cellSize.top || y > cellSize.bottom)
				SCENE->Array[y][x] = 3;
		}
	}
	D3DLOCKED_RECT lr;
	BG->ptr[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* imgPixel = (DWORD*)lr.pBits;
	for (int y = 0; y < WINSIZEY; y++)
		for (int x = 0; x < WINSIZEX; x++)
			imgColor[y][x] = (D3DXCOLOR)imgPixel[y * WINSIZEX + x];
	BG->ptr[0]->ptr->UnlockRect(0);

	draw_mode = true;
	DrawLine(true);

	ChkLine();
	thread = new cThreadPool(1);
	thread->EnqueueJob([&]()->void {
		CAM->ZoomCam(1.5, 2, { WINSIZEX / 2, WINSIZEY / 2 });
		});
}
void cPlayer::Update(Vec2 bossPos)
{
	if (t_Fade != nullptr) t_Fade->Update();
	if (t_Hp != nullptr) t_Hp->Update();

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

	if (invincibility || speedUp)
	{
		for (int i = 0; i < 10; i++)
		{
			int random = rand() % 3;
			int random_x = 0, random_y = 0;
			if (random == 1) // x는 음수
			{
				random = rand() % 3;
				random_x = -(rand() % 75);
				if (random == 1) // y는 음수
				{
					random_y = -(rand() % 75);
				}
				else // y는 양수
				{
					random_y = rand() % 75;
				}
			}
			else // x는 양수
			{
				random = rand() % 3;
				random_x = rand() % 75;
				if (random == 1) // y는 음수
				{
					random_y = -(rand() % 75);
				}
				else // y는 양수
				{
					random_y = rand() % 75;
				}
			}
			float size = (rand() % 11) / 10;
			PART->AddEffect({ m_pos.x + random_x, m_pos.y + random_y }, size, "white_effect", 0.1);
		}
	}

	if (returning) Returning();

	if (!draw_mode) SOUND->Stop("draw_line");

	Move();

	if (t_Speed != nullptr) t_Speed->Update();
	if (t_Invincibility != nullptr) t_Invincibility->Update();
	if (t_PFadeDelay != nullptr) t_PFadeDelay->Update();
}

void cPlayer::Render()
{
	if (render)
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
	SAFE_DELETE(t_Hp);
	SAFE_DELETE(t_Speed);
	SAFE_DELETE(t_Invincibility);
	SAFE_DELETE(t_Fade);
	SAFE_DELETE(t_PFadeDelay);
	SAFE_DELETE(thread);
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
		if (SCENE->Array[(int)m_pos.y][(int)m_pos.x] != 1)
		{
			draw_line = true;
			startDrawPos = m_pos;
		}
	}
	else if (INPUT->KeyUp(VK_SPACE))
	{
		draw_line = false;
		if (Current() == 1)
		{
			returning = true;
		}
	}

	if (INPUT->KeyPress(VK_F1))
		speed = 25;
	if (INPUT->KeyPress(VK_F2))
		invincibility = true;
}

D3DLOCKED_RECT lr;
void cPlayer::DrawTempLine(BYTE dir)
{
	if (!draw_mode)
	{
		draw_mode = true;
		SOUND->Play("draw_line", true);
	}
	BG->ptr[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;

	if (dir == VK_LEFT || dir == VK_RIGHT)
	{
		int index;
		for (int i = -10; i < 10; i++)
		{
			SCENE->Array[int(m_pos.y - i)][int(m_pos.x)] = 9;
			index = int(m_pos.y - i) * WINSIZEX + (int)m_pos.x;
			textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);
			for (int j = -10; j < 10; j++)
			{
				if (SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 1 && SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 2)
				{
					SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] = 9;
					index = int(m_pos.y - i) * WINSIZEX + (int)(m_pos.x - j);
					textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);
				}
			}
		}

		SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 1;
		index = (int)m_pos.y * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);
	}
	else if (dir == VK_UP || dir == VK_DOWN)
	{
		int index;
		for (int i = -10; i < 10; i++)
		{
			SCENE->Array[int(m_pos.y)][int(m_pos.x - i)] = 9;
			index = (int)m_pos.y * WINSIZEX + int(m_pos.x - i);
			textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);

			for (int j = -10; j < 10; j++)
			{
				if (SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 1 && SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 2)
				{
					SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] = 9;
					index = int(m_pos.y - j) * WINSIZEX + (int)(m_pos.x - i);
					textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);
				}
			}
		}

		SCENE->Array[int(m_pos.y)][int(m_pos.x)] = 1;
		index = (int)m_pos.y * WINSIZEX + (int)m_pos.x;
		textureColor[index] = D3DCOLOR_RGBA(140, 255, 200, 255);
	}
	BG->ptr[0]->ptr->UnlockRect(0);
}

void cPlayer::DrawLine(bool isFilled)
{
	if (!draw_mode) return;
	draw_mode = false;
	D3DLOCKED_RECT lr;
	BG->ptr[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;

	for (int y = WINSIZEY - 3; y != 1; --y)
	{
		for (int x = WINSIZEX - 3; x != 1; --x)
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
					targetPixel = lineColor;
					SCENE->Array[y][x] = 2;
					last_x = x;
					last_y = y;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				break;
			case 3:
				textureColor[y * WINSIZEX + x] = D3DCOLOR_RGBA(0, 0, 0, 0);
				if (x % 10 == 0 && y % 10 == 0)
				{
					PART->AddEffect({ (float)x, (float)y }, 1, "white_effect");
				}
				SCENE->Array[y][x] = 4;
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
					targetPixel = lineColor;
					SCENE->Array[y][x] = 2;
					last_x = x;
					last_y = y;
					textureColor[y * WINSIZEX + x] = targetPixel;
				}
				break;
			}
		}
	}

	BG->ptr[0]->ptr->UnlockRect(0);

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
	int temp_Coloring_Cell = 0;
	if (target == change) return;
	ChkLine();
	queue<Vec2> v2q;

	SCENE->Array[(int)pos.y][(int)pos.x] = change;

	v2q.push(pos);
	if (!isFilled)
	{
		coloring_cells++;
		temp_Coloring_Cell++;
	}

	while (!v2q.empty())
	{
		Vec2 n = v2q.front();
		v2q.pop();

		if (SCENE->Array[(int)n.y][(int)n.x - 1] == target && n.x - 1 > cellSize.left)
		{
			SCENE->Array[(int)n.y][(int)n.x - 1] = change;
			v2q.push({ n.x - 1, n.y });
			if (!isFilled)
			{
				coloring_cells++;
				temp_Coloring_Cell++;
			}
		}
		if (SCENE->Array[(int)n.y][(int)n.x + 1] == target && n.x + 1 < cellSize.right)
		{
			SCENE->Array[(int)n.y][(int)n.x + 1] = change;
			v2q.push({ n.x + 1, n.y });
			if (!isFilled)
			{
				coloring_cells++;
				temp_Coloring_Cell++;
			}
		}

		if (SCENE->Array[(int)n.y - 1][(int)n.x] == target && n.y - 1 > cellSize.top)
		{
			SCENE->Array[(int)n.y - 1][(int)n.x] = change;
			v2q.push({ n.x, n.y - 1 });
			if (!isFilled)
			{
				coloring_cells++;
				temp_Coloring_Cell++;
			}
		}
		if (SCENE->Array[(int)n.y + 1][(int)n.x] == target && n.y + 1 < cellSize.bottom)
		{
			SCENE->Array[(int)n.y + 1][(int)n.x] = change;
			v2q.push({ n.x, n.y + 1 });
			if (!isFilled)
			{
				coloring_cells++;
				temp_Coloring_Cell++;
			}
		}
	}
	if (!isFilled)
	{
		float temp1 = coloring_cells * 100;
		float temp2 = real_cells;
		coloring_per = temp1 / temp2;
		SCENE->score += temp_Coloring_Cell / 1000;

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
				if (!Near(VK_LEFT, 3) && !Near(VK_LEFT, 4))
				{
					if (Near(VK_LEFT, 2) || !Near(VK_LEFT, 1) && draw_line)
					{
						m_pos.x--;
						if (Current() == 2 && m_pos != startDrawPos)
						{
							DrawLine();
						}

						else
						{
							ChkLine();
							DrawTempLine(VK_LEFT);

							if (!drawStart) startDrawPos = m_pos + Vec2(2, 0);
							drawStart = true;

							PART->AddEffect(m_pos, 1, "white_effect");
						}
					}
				}
			}
		}
		else if (right)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (!Near(VK_RIGHT, 3) && !Near(VK_RIGHT, 4))
				{
					if (Near(VK_RIGHT, 2) || !Near(VK_RIGHT, 1) && draw_line)
					{
						m_pos.x++;
						if (Current() == 2 && m_pos != startDrawPos)
						{
							DrawLine();
						}
						else
						{
							ChkLine();
							DrawTempLine(VK_RIGHT);

							if (!drawStart) startDrawPos = m_pos - Vec2(2, 0);
							drawStart = true;

							PART->AddEffect(m_pos, 1, "white_effect");
						}
					}
				}
			}
		}
		else if (up)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (!Near(VK_UP, 3) && !Near(VK_UP, 4))
				{
					if (Near(VK_UP, 2) || !Near(VK_UP, 1) && draw_line)
					{
						m_pos.y--;
						if (Current() == 2 && m_pos != startDrawPos)
						{
							DrawLine();
						}
						else
						{
							ChkLine();
							DrawTempLine(VK_UP);

							if (!drawStart) startDrawPos = m_pos + Vec2(0, 2);
							drawStart = true;

							PART->AddEffect(m_pos, 1, "white_effect");
						}
					}
				}
			}
		}
		else if (down)
		{
			for (int i = 0; i < speed; i++)
			{
				ChkLine();
				if (!Near(VK_DOWN, 3) && !Near(VK_DOWN, 4))
				{
					if (Near(VK_DOWN, 2) || !Near(VK_DOWN, 1) && draw_line)
					{
						m_pos.y++;
						if (Current() == 2 && m_pos != startDrawPos)
						{
							DrawLine();
						}

						else
						{
							ChkLine();
							DrawTempLine(VK_DOWN);

							if (!drawStart) startDrawPos = m_pos - Vec2(0, 2);
							drawStart = true;

							PART->AddEffect(m_pos, 1, "white_effect");
						}
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
	SOUND->Stop("draw_line");
	D3DLOCKED_RECT lr;
	BG->ptr[0]->ptr->LockRect(0, &lr, 0, D3DLOCK_DISCARD);
	DWORD* textureColor = (DWORD*)lr.pBits;
	for (int i = 0; i < speed; i++)
	{
		D3DXCOLOR targetPixel;
		if (Near(VK_LEFT, 1))
		{
			for (int i = -10; i < 10; i++)
			{
				targetPixel = imgColor[(int)m_pos.y - i][(int)m_pos.x];
				textureColor[int(m_pos.y - i) * WINSIZEX + int(m_pos.x)] = targetPixel;
				SCENE->Array[int(m_pos.y - i)][int(m_pos.x)] = 0;

				for (int j = -10; j < 10; j++)
				{
					if (SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 1 && SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 2)
					{
						targetPixel = imgColor[(int)m_pos.y - i][(int)m_pos.x - j];
						textureColor[int(m_pos.y - i) * WINSIZEX + int(m_pos.x - j)] = targetPixel;
						SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] = 0;
					}
				}
			}
			m_pos.x--;
		}

		else if (Near(VK_RIGHT, 1))
		{
			for (int i = -10; i < 10; i++)
			{
				targetPixel = imgColor[(int)m_pos.y - i][(int)m_pos.x];
				textureColor[int(m_pos.y - i) * WINSIZEX + int(m_pos.x)] = targetPixel;
				SCENE->Array[int(m_pos.y - i)][int(m_pos.x)] = 0;

				for (int j = -10; j < 10; j++)
				{
					if (SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 1 && SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] != 2)
					{
						targetPixel = imgColor[(int)m_pos.y - i][(int)m_pos.x - j];
						textureColor[int(m_pos.y - i) * WINSIZEX + int(m_pos.x - j)] = targetPixel;
						SCENE->Array[int(m_pos.y - i)][int(m_pos.x - j)] = 0;
					}
				}
			}
			m_pos.x++;
		}

		else if (Near(VK_DOWN, 1))
		{
			for (int i = -10; i < 10; i++)
			{
				targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x - i];
				textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x - i)] = targetPixel;
				SCENE->Array[int(m_pos.y)][int(m_pos.x - i)] = 0;

				for (int j = -10; j < 10; j++)
				{
					if (SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 1 && SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 2)
					{
						targetPixel = imgColor[(int)m_pos.y - j][(int)m_pos.x - i];
						textureColor[int(m_pos.y - j) * WINSIZEX + int(m_pos.x - i)] = targetPixel;
						SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] = 0;
					}
				}
			}
			m_pos.y++;
		}

		else if (Near(VK_UP, 1))
		{
			for (int i = -10; i < 10; i++)
			{
				targetPixel = imgColor[(int)m_pos.y][(int)m_pos.x - i];
				textureColor[int(m_pos.y) * WINSIZEX + int(m_pos.x - i)] = targetPixel;
				SCENE->Array[int(m_pos.y)][int(m_pos.x - i)] = 0;

				for (int j = -10; j < 10; j++)
				{
					if (SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 1 && SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] != 2)
					{
						targetPixel = imgColor[(int)m_pos.y - j][(int)m_pos.x - i];
						textureColor[int(m_pos.y - j) * WINSIZEX + int(m_pos.x - i)] = targetPixel;
						SCENE->Array[int(m_pos.y - j)][int(m_pos.x - i)] = 0;
					}
				}
			}
			m_pos.y--;
		}
		else
		{
			m_pos = startDrawPos;
			draw_line = false;
			returning = false;
		}
	}
	BG->ptr[0]->ptr->UnlockRect(0);
}

void cPlayer::ItemUpdate()
{
	if (hp <= 0) hp = 0;
}

void cPlayer::EatItem(string key)
{
	if (key == "Heal")
	{
		isHp = true;
		if (hp < 3) hp += 1;
		SCENE->score += 50;
		if (t_Hp == nullptr)
		{
			t_Hp = new cTimer(1, [&]()->void {
				isHp = false;
				t_Hp = nullptr;
				});
		}
	}

	if (key == "Speed")
	{
		if (t_Speed == nullptr)
		{
			speed = 25;
			speedUp = true;
			t_Speed = new cTimer(5, [&]()->void {
				speedUp = false;
				speed =15;
				t_Speed = nullptr;
				});
		}
		SCENE->score += 75;
	}

	if (key == "Invincibility")
	{
		invincibility = true;
		if (t_Invincibility == nullptr)
		{
			t_Invincibility = new cTimer(5, [&]()->void {
				invincibility = false;
				t_Invincibility = nullptr;
				});
		}
		SCENE->score += 100;
	}
}

void cPlayer::CamEvent()
{
	if (t_camMoveDelay != nullptr) t_camMoveDelay->Update();

	if (camEvent && t_camMoveDelay == nullptr)
	{
		t_camMoveDelay = new cTimer(2, [&]()->void {
			CAM->MoveCam({ 1000, m_pos.y });
			camEvent = false;
			t_camMoveDelay = nullptr;
			});
	}
}
