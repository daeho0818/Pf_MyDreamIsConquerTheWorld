#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	Init();
}

cCameraManager::~cCameraManager()
{
	SAFE_DELETE(t_ShakeDelay);
}

void cCameraManager::Init()
{
	projPos = { -WINSIZEX, WINSIZEY, 100 };
	camPos = { 0, 0 };
	camUp = { 0, 1, 0 };

}

void cCameraManager::Update()
{
	projPos = { -WINSIZEX * zoom, WINSIZEY * zoom, 100 };

	Shaking();

	Zooming();

	Moving();

	D3DXMatrixOrthoLH(&matProj, projPos.x, projPos.y, 0, projPos.z);
	D3DXMatrixLookAtLH(&matView, &Vec3(camPos.x, camPos.y, 1), &Vec3(camPos.x, camPos.y, 0), &camUp);
}

void cCameraManager::Render()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void cCameraManager::ShakeCam(float time)
{
	isShake = true;
	m_time = time;
	t_ShakeDelay = new cTimer(time, [&]()->void { isShake = false; camPos = { 0, 0 }; t_ShakeDelay = nullptr; });
}

void cCameraManager::ZoomCam(float time, float delay, Vec2 pos, bool dontExit)
{
	isZoom = true;

	m_time = time;
	m_delay = delay;

	dontExit ?
		MoveCam(pos) :
		m_targetPos = pos - Vec2(WINSIZEX / 2, WINSIZEY / 2);

	t_Zoom = new cTimer(time, [&]()->void {
		zoom = 0.5;
		isZoom = false;
		t_Zoom = nullptr;
		});
}

void cCameraManager::MoveCam(Vec2 targetPos)
{
	Vec2 movePos = targetPos;
	if (movePos.x >= 3000) movePos.x = 3000;
	else if (movePos.x <= 1000) movePos.x = 1000;

	if (movePos.y <= 1350) movePos.y = 1350;
	else if (movePos.y >= 600) movePos.y = 600;

	m_targetPos = movePos - Vec2(WINSIZEX / 2, WINSIZEY / 2);
}

void cCameraManager::Shaking()
{
	if (t_ShakeDelay != nullptr) t_ShakeDelay->Update();

	if (isShake)
		camPos = { float(rand() % 100 - 50), float(rand() % 100 - 50) };
}

void cCameraManager::Zooming()
{
	if (t_Zoom != nullptr) t_Zoom->Update();
	if (t_ZoomDelay != nullptr) t_ZoomDelay->Update();

	if (isZoom && zoom > 0.5f)
	{
		zoom -= 0.01 / m_time;
	}

	if (!isZoom && zoom != 1)
	{
		if (t_ZoomDelay == nullptr)
			t_ZoomDelay = new cTimer(m_delay, [&]()->void {isZoomWait = true; t_ZoomDelay = nullptr; });
	}
	if (isZoomWait)
	{
		zoom = 1;
		m_targetPos = { 0, 0 };
		/*MoveCam(Vec2(WINSIZEX / 2, WINSIZEY / 2));*/
		isZoomWait = false;
	}
}

void cCameraManager::Moving()
{
	D3DXVec2Lerp(&camPos, &camPos, &m_targetPos, 0.5f);
}
