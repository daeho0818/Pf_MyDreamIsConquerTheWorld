#include "DXUT.h"
#include "cItemAdmin.h"
#include "cHeal.h"
#include "cSpeed.h"
#include "cInvincibility.h";

cItemAdmin::cItemAdmin(cPlayer* player)
	:m_player(player)
{
	t_Heal = nullptr;
	t_Speed = nullptr;
	t_Invincibility = nullptr;
}

cItemAdmin::~cItemAdmin()
{
	for (auto iter : m_items) SAFE_DELETE(iter);
	m_items.clear();
	SAFE_DELETE(t_Heal);
	SAFE_DELETE(t_Speed);
	SAFE_DELETE(t_Invincibility);
}

void cItemAdmin::Update()
{
	if (t_Heal != nullptr) t_Heal->Update();
	if (t_Speed != nullptr) t_Speed->Update();
	if (t_Invincibility != nullptr) t_Invincibility->Update();
	for (auto iter : m_items)
	{
		iter->Update();
		if (SCENE->Array[(int)iter->m_pos.y][(int)iter->m_pos.x] == 4)
		{
			m_player->EatItem(iter->itemName);
			iter->isDestroy = true;
		}
	}
	if (t_Heal == nullptr)
	{
		t_Heal = new cTimer(15, [&]()->void {
			CreateItem("Heal");
			t_Heal = nullptr;
			});
	}
	if (t_Speed == nullptr)
	{
		t_Speed = new cTimer(20, [&]()->void {
			CreateItem("Speed");
			t_Speed = nullptr;
			});
	}
	if (t_Invincibility == nullptr)
	{
		t_Invincibility = new cTimer(30, [&]()->void {
			CreateItem("Invincibility");
			t_Invincibility = nullptr;
			});
	}
	IsDestroy();
}

void cItemAdmin::Render()
{
	for (auto iter : m_items) iter->Render();
}

void cItemAdmin::CreateItem(string key)
{
	Vec2 r_Pos;
	int random_x, random_y;
	while (true)
	{
		random_x = float(rand() % (40 + WINSIZEX) - 40);
		random_y = float(rand() % (300 + WINSIZEY) - 300);
		if (random_x > 40 && random_x < WINSIZEX - 40 && random_y > 300 && random_y < WINSIZEY - 300) 
			if(SCENE->Array[random_y][random_x] == 0)
				break;
	}
	r_Pos = { (float)random_x, (float)random_y };

	if (key == "Heal")
		m_items.push_back(new cHeal(r_Pos, 0.5));
	else if (key == "Speed")
		m_items.push_back(new cSpeed(r_Pos, 0.5));
	else if (key == "Invincibility")
		m_items.push_back(new cInvincibility(r_Pos, 0.5));
}

void cItemAdmin::IsDestroy()
{
	for (auto& iter = m_items.begin(); iter != m_items.end();)
	{
		if ((*iter)->isDestroy)
		{
			SAFE_DELETE(*iter);
			iter = m_items.erase(iter);
		}
		else
			iter++;
	}
}
