#include "DXUT.h"
#include "cMainGame.h"
#include "cTitleScene.h"
#include "cSelectStageScene.h"
#include "cIceScene.h"
#include "cCityScene.h"
#include "cCityNightScene.h"
#include "cChurchScene.h"
#include "cJungleScene.h"
#include "cDesertScene.h"
#include "cOceanScene.h"
#include "cEndScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	AddResource();
	SCENE->AddScene("cTitleScene", new cTitleScene);
	SCENE->AddScene("cSelectStageScene", new cSelectStageScene);
	SCENE->AddScene("cIceScene", new cIceScene);
	SCENE->AddScene("cCityScene", new cCityScene);
	SCENE->AddScene("cCityNightScene", new cCityNightScene);
	SCENE->AddScene("cChurchScene", new cChurchScene);
	SCENE->AddScene("cDesertScene", new cDesertScene);
	SCENE->AddScene("cOceanScene", new cOceanScene);
	SCENE->AddScene("cJungleScene", new cJungleScene);
	SCENE->AddScene("cEndScene", new cEndScene);
	SCENE->ChangeScene("cTitleScene");
}

void cMainGame::Update()
{
	MOUSE->Update();
	INPUT->Update();
	PART->Update();
	SCENE->Update();
	SOUND->Update();
}

void cMainGame::Render()
{
	SCENE->Render();
	PART->Render();
	UI->Begin();
	SCENE->UIRender();
	UI->End();
}

void cMainGame::Release()
{
	cImageManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
	cParticleManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	cMouseManager::ReleaseInstance();
	cButtonManager::ReleaseInstance();
}

void cMainGame::ResetDevice()
{
	UI->Reset();
}

void cMainGame::LostDevice()
{
	UI->Lost();
}

void cMainGame::AddResource()
{
	// title
	IMAGE->AddImage("TitleBG", "title/TitleBG");
	IMAGE->AddImage("Logo", "title/Logo");
	IMAGE->AddImage("start_note", "title/start_note");
	IMAGE->AddImage("start_button", "title/start_button");
	IMAGE->AddImage("guide_note", "title/guide_note");
	IMAGE->AddImage("guide_button", "title/guide_button");
	IMAGE->AddImage("adven_note", "title/adven_note");
	IMAGE->AddImage("adven_button", "title/adven_button");
	IMAGE->AddImage("develop_note", "title/develop_note");
	IMAGE->AddImage("develop_button", "title/develop_button");
	IMAGE->AddImage("quit_note", "title/quit_note");
	IMAGE->AddImage("quit_button", "title/quit_button");
	IMAGE->AddImage("pattern", "title/pattern");

	// guide Note
	IMAGE->AddImage("guide_BG", "title/GuideBook/BG");
	IMAGE->AddImage("guide_Arrow", "title/GuideBook/arrow");
	IMAGE->AddImage("guide_close", "title/GuideBook/close");
	IMAGE->AddImage("guide_text1", "title/GuideBook/text1");
	IMAGE->AddImage("guide_text2", "title/GuideBook/text2");

	//adventure Note
	IMAGE->AddImage("adven_Back", "title/AdvenBook/back");
	IMAGE->AddImage("adven_BG", "title/AdvenBook/BG");
	IMAGE->AddImage("adven_BGRect", "title/AdvenBook/BGRect");
	IMAGE->AddImage("adven_Chain", "title/AdvenBook/chains");
	IMAGE->AddImage("adven_Lock", "title/AdvenBook/lock");
	IMAGE->AddImage("adven_CircleDown", "title/AdvenBook/circleDown");
	IMAGE->AddImage("adven_CircleUp", "title/AdvenBook/circleUp");
	IMAGE->AddImage("adven_CollectionPer", "title/AdvenBook/collectionPer");
	IMAGE->AddImage("adven_CollectionPerBG", "title/AdvenBook/collectionPerBG");
	IMAGE->AddImage("adven_CollectionPerRect", "title/AdvenBook/collectionPerRect");
	IMAGE->AddImage("adven_ContentRect", "title/AdvenBook/contentRect");
	IMAGE->AddImage("adven_ContentBG", "title/AdvenBook/contentBG");
	IMAGE->AddImage("adven_Handle", "title/AdvenBook/handle");
	IMAGE->AddImage("adven_HandleBG", "title/AdvenBook/handleBG");
	IMAGE->AddImage("adven_ItemRect", "title/AdvenBook/itemRect");
	IMAGE->AddImage("adven_DontClear", "title/AdvenBook/dontClear");
	IMAGE->AddImage("adven_textBG", "title/AdvenBook/textBG");

	// world map
	IMAGE->AddImage("WorldMap", "WorldMap/map");
	IMAGE->AddImage("WorldEmblem", "WorldMap/Emblem");
	IMAGE->AddImage("X", "WorldMap/Details/public/x");
	IMAGE->AddImage("church_button", "WorldMap/church_button");
	IMAGE->AddImage("church_complete", "WorldMap/church_complete");
	IMAGE->AddImage("church_lock", "WorldMap/church_lock");
	IMAGE->AddImage("city(night)_button", "WorldMap/city(night)_button");
	IMAGE->AddImage("city(night)_complete", "WorldMap/city(night)_complete");
	IMAGE->AddImage("city(night)_lock", "WorldMap/city(night)_lock");
	IMAGE->AddImage("city_button", "WorldMap/city_button");
	IMAGE->AddImage("city_complete", "WorldMap/city_complete");
	IMAGE->AddImage("city_lock", "WorldMap/city_lock");
	IMAGE->AddImage("desert_button", "WorldMap/desert_button");
	IMAGE->AddImage("desert_complete", "WorldMap/desert_complete");
	IMAGE->AddImage("desert_lock", "WorldMap/desert_lock");
	IMAGE->AddImage("ice_button", "WorldMap/ice_button");
	IMAGE->AddImage("ice_complete", "WorldMap/ice_complete");
	IMAGE->AddImage("ice_lock", "WorldMap/ice_lock");
	IMAGE->AddImage("jungle_button", "WorldMap/jungle_button");
	IMAGE->AddImage("jungle_complete", "WorldMap/jungle_complete");
	IMAGE->AddImage("jungle_lock", "WorldMap/jungle_lock");
	IMAGE->AddImage("ocean_button", "WorldMap/ocean_button");
	IMAGE->AddImage("ocean_complete", "WorldMap/ocean_complete");
	IMAGE->AddImage("ocean_lock", "WorldMap/ocean_lock");
	IMAGE->AddImage("church_All", "WorldMap/Details/Church/All");
	IMAGE->AddImage("city_All", "WorldMap/Details/City/All");
	IMAGE->AddImage("city(night)_All", "WorldMap/Details/City(night)/All");
	IMAGE->AddImage("desert_All", "WorldMap/Details/Desert/All");
	IMAGE->AddImage("ice_All", "WorldMap/Details/Ice/All");
	IMAGE->AddImage("jungle_All", "WorldMap/Details/Jungle/All");
	IMAGE->AddImage("ocean_All", "WorldMap/Details/Ocean/All");
	IMAGE->AddImage("StageStartB", "WorldMap/Details/Public/Start");
	IMAGE->AddImage("cloud1", "WorldMap/cloud/cloud1");
	IMAGE->AddImage("cloud2", "WorldMap/cloud/cloud2");
	IMAGE->AddImage("cloud3", "WorldMap/cloud/cloud3");
	IMAGE->AddImage("cloud4", "WorldMap/cloud/cloud4");

	// ingame
	{
		IMAGE->AddImage("player", "Ingame/player");
		IMAGE->AddImage("h_player", "Ingame/h_player");

		//  start
		IMAGE->AddImage("start_1", "Ingame/Start/1");
		IMAGE->AddImage("start_2", "Ingame/Start/2");
		IMAGE->AddImage("start_3", "Ingame/Start/3");
		IMAGE->AddImage("start_start", "Ingame/Start/start");
		IMAGE->AddImage("start_game", "Ingame/Start/game");

		//  stop
		IMAGE->AddImage("stop_BG", "Ingame/Stop/BG");
		IMAGE->AddImage("stop_text", "Ingame/Stop/text");
		IMAGE->AddImage("stop_back", "Ingame/Stop/back");
		IMAGE->AddImage("stop_restart", "Ingame/Stop/restart");
		IMAGE->AddImage("stop_worldmap", "Ingame/Stop/worldmap");
		IMAGE->AddImage("stop_pointline", "Ingame/Stop/pointline");

		// clear / fail
		IMAGE->AddImage("CFgetItem", "Ingame/Clear,Fail/getItem");
		IMAGE->AddImage("CFpercent", "Ingame/Clear,Fail/percent");
		IMAGE->AddImage("CFscore", "Ingame/Clear,Fail/score");
		IMAGE->AddImage("CFtime", "Ingame/Clear,Fail/time");
		IMAGE->AddImage("CFBG", "Ingame/Clear,Fail/BG");
		IMAGE->AddImage("CFnext", "Ingame/Clear,Fail/next");

		// clear
		{
			IMAGE->AddImage("Clear", "Ingame/Clear,Fail/Clear/clear");
			IMAGE->AddImage("C", "Ingame/Clear,Fail/Clear/1. c");
			IMAGE->AddImage("L", "Ingame/Clear,Fail/Clear/2. l");
			IMAGE->AddImage("E", "Ingame/Clear,Fail/Clear/3. e");
			IMAGE->AddImage("A", "Ingame/Clear,Fail/Clear/4. a");
			IMAGE->AddImage("R", "Ingame/Clear,Fail/Clear/5. r");
			IMAGE->AddImage("!", "Ingame/Clear,Fail/Clear/6. !");
		}

		// fail
		{
			IMAGE->AddImage("Over", "Ingame/Clear,Fail/Fail/over");
			IMAGE->AddImage("O", "Ingame/Clear,Fail/Fail/1. o");
			IMAGE->AddImage("V", "Ingame/Clear,Fail/Fail/2. v");
			IMAGE->AddImage("OVER_E", "Ingame/Clear,Fail/Fail/3. e");
			IMAGE->AddImage("OVER_R", "Ingame/Clear,Fail/Fail/4. r");
		}

		// ice
		{
			IMAGE->AddImage("ice_Under", "Ingame/Ice/under");
			IMAGE->AddImage("ice_High", "Ingame/Ice/high");

			// mob
			{
				IMAGE->AddImage("ice_mob1", "Ingame/Ice/mob/mob1/mob1", 6);
				IMAGE->AddImage("ice_mob2", "Ingame/Ice/mob/mob2/mob2", 6);
				IMAGE->AddImage("ice_boss", "Ingame/Ice/mob/boss/boss", 11);
			}
		}

		// city
		{
			IMAGE->AddImage("city_Under", "Ingame/City/under");
			IMAGE->AddImage("city_High", "Ingame/City/high");

			//mob
			{
				IMAGE->AddImage("city_mob1", "Ingame/City/mob/mob1/mob1", 15);
				IMAGE->AddImage("city_mob2", "Ingame/City/mob/mob2/mob2", 6);
				IMAGE->AddImage("city_boss", "Ingame/City/mob/boss/boss", 10);
			}
		}

		// city(night)
		{
			IMAGE->AddImage("city(night)_Under", "Ingame/city(night)/under");
			IMAGE->AddImage("city(night)_high", "Ingame/city(night)/high");

			//mob
			{
				IMAGE->AddImage("city(night)_mob1", "Ingame/city(night)/mob/mob1/mob1", 11);
				IMAGE->AddImage("city(night)_mob2", "Ingame/city(night)/mob/mob2/mob2", 8);
				IMAGE->AddImage("city(night)_boss", "Ingame/city(night)/mob/boss/boss", 8);
			}
		}

		// ocean
		{
			IMAGE->AddImage("ocean_Under", "Ingame/Ocean/under");
			IMAGE->AddImage("ocean_High", "Ingame/Ocean/high");

			//mob
			{
				IMAGE->AddImage("ocean_mob1", "Ingame/Ocean/mob/mob1/mob1", 7);
				IMAGE->AddImage("ocean_mob2", "Ingame/Ocean/mob/mob2/mob2", 9);
				IMAGE->AddImage("ocean_boss", "Ingame/Ocean/mob/boss/boss", 8);
			}
		}

		// desert
		{
			IMAGE->AddImage("desert_Under", "Ingame/Desert/desert_Under");
			IMAGE->AddImage("desert_High", "Ingame/Desert/desert_High");

			//mob
			{
				IMAGE->AddImage("desert_mob1", "Ingame/Desert/mob/mob1/mob1", 6);
				IMAGE->AddImage("desert_mob2", "Ingame/Desert/mob/mob2/mob2", 6);
				IMAGE->AddImage("desert_boss1", "Ingame/Desert/mob/boss/1/boss1", 8);
				IMAGE->AddImage("desert_boss2", "Ingame/Desert/mob/boss/2/boss2", 8);
			}
		}
		    
		// church
		{
			IMAGE->AddImage("church_Under", "Ingame/Church/under");
			IMAGE->AddImage("church_high", "Ingame/Church/high");

			//mob
			{
				IMAGE->AddImage("church_mob1", "Ingame/Church/mob/mob1/mob1", 19);
				IMAGE->AddImage("church_mob2", "Ingame/Church/mob/mob2/mob2", 17);
				IMAGE->AddImage("church_boss", "Ingame/Church/mob/boss/boss", 10);
			}
		}

		// jungle
		{
			IMAGE->AddImage("jungle_Under", "Ingame/Jungle/under");
			IMAGE->AddImage("jungle_High", "Ingame/Jungle/high");

			// mob
			{
				IMAGE->AddImage("jungle_mob1", "Ingame/Jungle/mob/mob1/mob1", 14);
				IMAGE->AddImage("jungle_mob2", "Ingame/Jungle/mob/mob2/mob2", 10);
				IMAGE->AddImage("jungle_mob3", "Ingame/Jungle/mob/mob3/mob3", 5);
				IMAGE->AddImage("jungle_boss", "Ingame/Jungle/mob/boss/boss", 8);
			}
		}

		// UI
		IMAGE->AddImage("IngameBG", "Ingame/UI/AllBG");
		IMAGE->AddImage("Ingame_HP", "Ingame/UI/HP");
		IMAGE->AddImage("Ingame_HP0", "Ingame/UI/HP0");
		IMAGE->AddImage("Ingame_HP1", "Ingame/UI/HP1");
		IMAGE->AddImage("Ingame_HP2", "Ingame/UI/HP2");
		IMAGE->AddImage("Ingame_HP3", "Ingame/UI/HP3");
		IMAGE->AddImage("Ingame_Item", "Ingame/UI/item");
		IMAGE->AddImage("colon", "Ingame/UI/colon");
	}

	// text
	for (int i = 0; i < 10; i++)
	{
		char key[5] = "";
		sprintf(key, "%d", i);
		char path[128] = "";
		sprintf(path, "Text/%d", i);
		IMAGE->AddImage(key, path);
	}
	IMAGE->AddImage("percent", "Text/%");

	// public
	IMAGE->AddImage("Arrow", "Public/Arrow");
	IMAGE->AddImage("_Arrow", "Public/_Arrow");
	IMAGE->AddImage("Cursor", "Public/Cursor");
	IMAGE->AddImage("Blur", "Public/Blur");

	// EndScene
	IMAGE->AddImage("end_restart", "EndScene/restart");
	IMAGE->AddImage("end_title", "EndScene/title");
	IMAGE->AddImage("end_worldmap", "EndScene/worldmap");

	IMAGE->AddImage("Boss", "Boss");

	IMAGE->AddImage("hpBar", "hpBar");
	IMAGE->AddImage("Hp+", "Hp+");
	IMAGE->AddImage("Speed+", "Speed+");
	IMAGE->AddImage("Invincibility", "Invincibility");

	IMAGE->AddImage("bullet_enemy", "bullet_enemy");
}