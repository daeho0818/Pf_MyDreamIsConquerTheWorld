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
	for (auto iter : m_items) iter->Update();
	if (t_Heal == nullptr)
	{
		t_Heal = new cTimer(7, [&]()->void {
			CreateItem("Heal");
			t_Heal = nullptr;
			});
	}
	if (t_Speed == nullptr)
	{
		t_Speed = new cTimer(10, [&]()->void {
			CreateItem("Speed");
			t_Speed = nullptr;
			});
	}
	if (t_Invincibility == nullptr)
	{
		t_Invincibility = new cTimer(15, [&]()->void {
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
	if (key == "Heal")
		m_items.push_back(new cHeal({ float(rand() % 1400 + 100), float(rand() % 700 + 100) }));
	if (key == "Speed")
		m_items.push_back(new cSpeed({ float(rand() % 1400 + 100), float(rand() % 700 + 100) }));
	if (key == "Invincibility")
		m_items.push_back(new cInvincibility({ float(rand() % 1400 + 100), float(rand() % 700 + 100) }));
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
