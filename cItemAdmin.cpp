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
		if (SCENE->Array[(int)iter->m_pos.y][(int)iter->m_pos.x] == 3)
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
		t_Speed = new cTimer(15, [&]()->void {
			CreateItem("Speed");
			t_Speed = nullptr;
			});
	}
	if (t_Invincibility == nullptr)
	{
		t_Invincibility = new cTimer(20, [&]()->void {
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
	do
	{
		r_Pos = { float(rand() % (40 + WINSIZEX) - 40), float(rand() % (WINSIZEY + 300) - 340) };
	} while (SCENE->Array[(int)r_Pos.y][(int)r_Pos.x] == 3);

	if (key == "Heal")
		m_items.push_back(new cHeal(r_Pos));
	else if (key == "Speed")
		m_items.push_back(new cSpeed(r_Pos));
	else if (key == "Invincibility")
		m_items.push_back(new cInvincibility(r_Pos));
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
