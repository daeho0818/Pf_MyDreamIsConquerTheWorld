#include "DXUT.h"
#include "cUIManager.h"

cUIManager::cUIManager()
	:m_sprite(nullptr)
{
	D3DXCreateSprite(g_device, &m_sprite);
}

cUIManager::~cUIManager()
{
	m_sprite->Release();
}

void cUIManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cUIManager::End()
{
	m_sprite->End();
}

void cUIManager::Reset()
{
	m_sprite->OnResetDevice();
}

void cUIManager::Lost()
{
	m_sprite->OnLostDevice();
}

void cUIManager::CenterRender(cTexture* ptr, Vec2 pos)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixAffineTransformation2D(&mat, 2, nullptr, 0, &Vec2(pos.x - ptr->info.Width / 2, pos.y - ptr->info.Height / 2));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(ptr->ptr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
}

void cUIManager::CropRender(cTexture* ptr, Vec2 pos, RECT& rc)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixAffineTransformation2D(&mat, 1, nullptr, 0, &Vec2(pos.x - ptr->info.Width / 2, pos.y - ptr->info.Height / 2));
	m_sprite->SetTransform(&mat);
	m_sprite->Draw(ptr->ptr, &rc, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
}

void cUIManager::PrintText(string str, Vec2 pos, float size)
{
	D3DXMATRIXA16 mat;
	D3DXCreateFontA(g_device, size * 0.8, 0, 10, 1, 0, DEFAULT_CHARSET, 0, 0, 0, "아임크리수진", &m_font);
	D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2, 0);
	m_sprite->SetTransform(&mat);
	m_font->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	SAFE_RELEASE(m_font);
}