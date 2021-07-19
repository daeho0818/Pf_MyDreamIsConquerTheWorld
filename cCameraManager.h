#pragma once
#include "singleton.h"
class cCameraManager
	:public singleton<cCameraManager>
{
public:
	cCameraManager();
	~cCameraManager();

	void Init();
	void Update();
	void Render();

	void ShakeCam(float time);
	void ZoomCam(float time, float delay, Vec2 pos, bool dontExit = false);
	void MoveCam(Vec2 targetPos);

private:
	Vec3 projPos;
	Vec3 camUp;
	Vec2 camPos;
	Vec2 m_targetPos;

	D3DXMATRIXA16 matProj;
	D3DXMATRIX matView;

	cTimer* t_ShakeDelay = nullptr;
	cTimer* t_Zoom = nullptr;
	cTimer* t_ZoomDelay = nullptr;

	bool isShake = false;
	bool isZoom = false;
	bool isZoomWait = false;

	float zoom = 1;
	float m_time;
	float m_delay;

	void Shaking();
	void Zooming();
	void Moving();
};
#define CAM cCameraManager::GetInstance()
