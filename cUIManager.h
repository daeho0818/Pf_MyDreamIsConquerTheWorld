#pragma once
#include "singleton.h"
class cUIManager :
	public singleton<cUIManager>
{
	LPD3DXSPRITE m_sprite;
	LPD3DXFONT m_font = NULL;
public:
	cUIManager();
	~cUIManager();

	void Begin();
	void End();
	void Reset();
	void Lost();

	void CenterRender(cTexture* ptr, Vec2 pos);
	void CropRender(cTexture* ptr, Vec2 pos, RECT& rc);
	void PrintText(string str, Vec2 pos, float size);
};

#define UI cUIManager::GetInstance()