#pragma once
#pragma comment(lib, "dsound.lib")

#include "SDKsound.h"
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <functional>
#include <string>
#include <queue>
#include <time.h>
#include <math.h>
#include <cstdarg>
#include <thread>

#define g_device DXUTGetD3D9Device()
#define Delta DXUTGetElapsedTime()

using namespace std;

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

const int WINSIZEX = 4000;
const int WINSIZEY = 2250;
static bool isWindowed = false;

#include "cTexture.h"
#include "cParticle.h"
#include "cScene.h"
#include "cTimer.h"
#include "cItem.h"
#include "cBullet.h"
#include "cMob.h"
#include "cButton.h"
#include "DebugLog.h"

#include "cImageManager.h"
#include "cInputManager.h"
#include "cParticleManager.h"
#include "cRenderManager.h"
#include "cUIManager.h"
#include "cSoundManager.h"
#include "cSceneManager.h"
#include "cMouseManager.h"
#include "cButtonManager.h"
#include "cThreadManager.h"
#include "cBGManager.h"

#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif