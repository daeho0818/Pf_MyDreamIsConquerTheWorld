#include "DXUT.h"
#include "cLoadingScene.h"
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

cLoadingScene::cLoadingScene()
{
}

cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	IMAGE->AddImage("Cursor", "Public/Cursor");
	loadCount++;

	// text
	for (int i = 0; i < 10; i++)
	{
		char key[5] = "";
		sprintf(key, "%d", i);
		char path[128] = "";
		sprintf(path, "Text/%d", i);
		IMAGE->AddImage(key, path);
		loadCount++;
	}
	IMAGE->AddImage("percent", "Text/%");
	loadCount++;

}

bool loading = false;
void cLoadingScene::Update()
{
	if (t_Delay != nullptr) t_Delay->Update();

	if (loadCount == 172)
	SCENE->ChangeScene("cTitleScene");

	if (loading) AddResource();

	if (INPUT->KeyDown(VK_RETURN))
	{
		loading = true;
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
	}
}

void cLoadingScene::Render()
{
	
}

void cLoadingScene::UIRender()
{
	
}

void cLoadingScene::Release()
{
	SAFE_DELETE(t_Delay);
}


void cLoadingScene::AddResource()
{
	if (bundle == 0)
	{
		// title
		IMAGE->AddImage("TitleBG", "title/TitleBG");
		loadCount++;
		IMAGE->AddImage("Logo", "title/Logo");
		loadCount++;
		IMAGE->AddImage("start_note", "title/start_note");
		loadCount++;
		IMAGE->AddImage("start_button", "title/start_button");
		loadCount++;
		IMAGE->AddImage("guide_note", "title/guide_note");
		loadCount++;
		IMAGE->AddImage("guide_button", "title/guide_button");
		loadCount++;
		IMAGE->AddImage("adven_note", "title/adven_note");
		loadCount++;
		IMAGE->AddImage("adven_button", "title/adven_button");
		loadCount++;
		IMAGE->AddImage("develop_note", "title/develop_note");
		loadCount++;
		IMAGE->AddImage("develop_button", "title/develop_button");
		loadCount++;
		IMAGE->AddImage("quit_note", "title/quit_note");
		loadCount++;
		IMAGE->AddImage("quit_button", "title/quit_button");
		loadCount++;
		IMAGE->AddImage("pattern", "title/pattern");
		loadCount++;
		bundle++;
	}

	if (bundle == 1 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{
				// guide Note
				IMAGE->AddImage("guide_BG", "title/GuideBook/BG");
				loadCount++;
				IMAGE->AddImage("guide_Arrow", "title/GuideBook/arrow");
				loadCount++;
				IMAGE->AddImage("guide_close", "title/GuideBook/close");
				loadCount++;
				IMAGE->AddImage("guide_text1", "title/GuideBook/text1");
				loadCount++;
				IMAGE->AddImage("guide_text2", "title/GuideBook/text2");
				loadCount++;
				t_Delay = nullptr;
				bundle++;
			});
	}

	if (bundle == 2 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{
				//adventure Note
				IMAGE->AddImage("adven_Back", "title/AdvenBook/back");
				loadCount++;
				IMAGE->AddImage("adven_BG", "title/AdvenBook/BG");
				loadCount++;
				IMAGE->AddImage("adven_BGRect", "title/AdvenBook/BGRect");
				loadCount++;
				IMAGE->AddImage("adven_Chain", "title/AdvenBook/chains");
				loadCount++;
				IMAGE->AddImage("adven_Lock", "title/AdvenBook/lock");
				loadCount++;
				IMAGE->AddImage("adven_CircleDown", "title/AdvenBook/circleDown");
				loadCount++;
				IMAGE->AddImage("adven_CircleUp", "title/AdvenBook/circleUp");
				loadCount++;
				IMAGE->AddImage("adven_CollectionPer", "title/AdvenBook/collectionPer");
				loadCount++;
				IMAGE->AddImage("adven_CollectionPerBG", "title/AdvenBook/collectionPerBG");
				loadCount++;
				IMAGE->AddImage("adven_CollectionPerRect", "title/AdvenBook/collectionPerRect");
				loadCount++;
				IMAGE->AddImage("adven_ContentRect", "title/AdvenBook/contentRect");
				loadCount++;
				IMAGE->AddImage("adven_ContentBG", "title/AdvenBook/contentBG");
				loadCount++;
				IMAGE->AddImage("adven_Handle", "title/AdvenBook/handle");
				loadCount++;
				IMAGE->AddImage("adven_HandleBG", "title/AdvenBook/handleBG");
				loadCount++;
				IMAGE->AddImage("adven_ItemRect", "title/AdvenBook/itemRect");
				loadCount++;
				IMAGE->AddImage("adven_DontClear", "title/AdvenBook/dontClear");
				loadCount++;
				IMAGE->AddImage("adven_textBG", "title/AdvenBook/textBG");
				loadCount++;
				t_Delay = nullptr;
				bundle++;
			});
	}

	if (bundle == 3 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{
				// world map
				IMAGE->AddImage("WorldMap", "WorldMap/map");
				loadCount++;
				IMAGE->AddImage("WorldEmblem", "WorldMap/Emblem");
				loadCount++;
				IMAGE->AddImage("X", "WorldMap/Details/public/x");
				loadCount++;
				IMAGE->AddImage("church_button", "WorldMap/church_button");
				loadCount++;
				IMAGE->AddImage("church_complete", "WorldMap/church_complete");
				loadCount++;
				IMAGE->AddImage("church_lock", "WorldMap/church_lock");
				loadCount++;
				IMAGE->AddImage("city(night)_button", "WorldMap/city(night)_button");
				loadCount++;
				IMAGE->AddImage("city(night)_complete", "WorldMap/city(night)_complete");
				loadCount++;
				IMAGE->AddImage("city(night)_lock", "WorldMap/city(night)_lock");
				loadCount++;
				IMAGE->AddImage("city_button", "WorldMap/city_button");
				loadCount++;
				IMAGE->AddImage("city_complete", "WorldMap/city_complete");
				loadCount++;
				IMAGE->AddImage("city_lock", "WorldMap/city_lock");
				loadCount++;
				IMAGE->AddImage("desert_button", "WorldMap/desert_button");
				loadCount++;
				IMAGE->AddImage("desert_complete", "WorldMap/desert_complete");
				loadCount++;
				IMAGE->AddImage("desert_lock", "WorldMap/desert_lock");
				loadCount++;
				IMAGE->AddImage("ice_button", "WorldMap/ice_button");
				loadCount++;
				IMAGE->AddImage("ice_complete", "WorldMap/ice_complete");
				loadCount++;
				IMAGE->AddImage("ice_lock", "WorldMap/ice_lock");
				loadCount++;
				IMAGE->AddImage("jungle_button", "WorldMap/jungle_button");
				loadCount++;
				IMAGE->AddImage("jungle_complete", "WorldMap/jungle_complete");
				loadCount++;
				IMAGE->AddImage("jungle_lock", "WorldMap/jungle_lock");
				loadCount++;
				IMAGE->AddImage("ocean_button", "WorldMap/ocean_button");
				loadCount++;
				IMAGE->AddImage("ocean_complete", "WorldMap/ocean_complete");
				loadCount++;
				IMAGE->AddImage("ocean_lock", "WorldMap/ocean_lock");
				loadCount++;
				IMAGE->AddImage("church_All", "WorldMap/Details/Church/All");
				loadCount++;
				IMAGE->AddImage("city_All", "WorldMap/Details/City/All");
				loadCount++;
				IMAGE->AddImage("city(night)_All", "WorldMap/Details/City(night)/All");
				loadCount++;
				IMAGE->AddImage("desert_All", "WorldMap/Details/Desert/All");
				loadCount++;
				IMAGE->AddImage("ice_All", "WorldMap/Details/Ice/All");
				loadCount++;
				IMAGE->AddImage("jungle_All", "WorldMap/Details/Jungle/All");
				loadCount++;
				IMAGE->AddImage("ocean_All", "WorldMap/Details/Ocean/All");
				loadCount++;
				IMAGE->AddImage("StageStartB", "WorldMap/Details/Public/Start");
				loadCount++;
				IMAGE->AddImage("cloud1", "WorldMap/cloud/cloud1");
				loadCount++;
				IMAGE->AddImage("cloud2", "WorldMap/cloud/cloud2");
				loadCount++;
				IMAGE->AddImage("cloud3", "WorldMap/cloud/cloud3");
				loadCount++;
				IMAGE->AddImage("cloud4", "WorldMap/cloud/cloud4");
				loadCount++;
				t_Delay = nullptr;
				bundle++;
			});
	}

	if (bundle == 4 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{
				// ingame
				{
					IMAGE->AddImage("player", "Ingame/player");
					loadCount++;
					IMAGE->AddImage("h_player", "Ingame/h_player");
					loadCount++;

					//  start
					IMAGE->AddImage("start_1", "Ingame/Start/1");
					loadCount++;
					IMAGE->AddImage("start_2", "Ingame/Start/2");
					loadCount++;
					IMAGE->AddImage("start_3", "Ingame/Start/3");
					loadCount++;
					IMAGE->AddImage("start_start", "Ingame/Start/start");
					loadCount++;
					IMAGE->AddImage("start_game", "Ingame/Start/game");
					loadCount++;

					//  stop
					IMAGE->AddImage("stop_BG", "Ingame/Stop/BG");
					loadCount++;
					IMAGE->AddImage("stop_text", "Ingame/Stop/text");
					loadCount++;
					IMAGE->AddImage("stop_back", "Ingame/Stop/back");
					loadCount++;
					IMAGE->AddImage("stop_restart", "Ingame/Stop/restart");
					loadCount++;
					IMAGE->AddImage("stop_worldmap", "Ingame/Stop/worldmap");
					loadCount++;
					IMAGE->AddImage("stop_pointline", "Ingame/Stop/pointline");
					loadCount++;

					// clear / fail
					IMAGE->AddImage("CFgetItem", "Ingame/Clear,Fail/getItem");
					loadCount++;
					IMAGE->AddImage("CFpercent", "Ingame/Clear,Fail/percent");
					loadCount++;
					IMAGE->AddImage("CFscore", "Ingame/Clear,Fail/score");
					loadCount++;
					IMAGE->AddImage("CFtime", "Ingame/Clear,Fail/time");
					loadCount++;
					IMAGE->AddImage("CFBG", "Ingame/Clear,Fail/BG");
					loadCount++;
					IMAGE->AddImage("CFnext", "Ingame/Clear,Fail/next");
					loadCount++;

					// clear
					{
						IMAGE->AddImage("Clear", "Ingame/Clear,Fail/Clear/clear");
						loadCount++;
						IMAGE->AddImage("C", "Ingame/Clear,Fail/Clear/1. c");
						loadCount++;
						IMAGE->AddImage("L", "Ingame/Clear,Fail/Clear/2. l");
						loadCount++;
						IMAGE->AddImage("E", "Ingame/Clear,Fail/Clear/3. e");
						loadCount++;
						IMAGE->AddImage("A", "Ingame/Clear,Fail/Clear/4. a");
						loadCount++;
						IMAGE->AddImage("R", "Ingame/Clear,Fail/Clear/5. r");
						loadCount++;
						IMAGE->AddImage("!", "Ingame/Clear,Fail/Clear/6. !");
						loadCount++;
					}

					// fail
					{
						IMAGE->AddImage("Over", "Ingame/Clear,Fail/Fail/over");
						loadCount++;
						IMAGE->AddImage("O", "Ingame/Clear,Fail/Fail/1. o");
						loadCount++;
						IMAGE->AddImage("V", "Ingame/Clear,Fail/Fail/2. v");
						loadCount++;
						IMAGE->AddImage("OVER_E", "Ingame/Clear,Fail/Fail/3. e");
						loadCount++;
						IMAGE->AddImage("OVER_R", "Ingame/Clear,Fail/Fail/4. r");
						loadCount++;
					}
				}
				t_Delay = nullptr;
				bundle++;
			});
	}

	if (bundle == 5 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{

				// ice
				{
					IMAGE->AddImage("ice_Under", "Ingame/Ice/under");
					loadCount++;
					IMAGE->AddImage("ice_High", "Ingame/Ice/high");
					loadCount++;

					// mob
					{
						IMAGE->AddImage("ice_mob1", "Ingame/Ice/mob/mob1/mob1", 6);
						loadCount++;
						IMAGE->AddImage("ice_mob2", "Ingame/Ice/mob/mob2/mob2", 6);
						loadCount++;
						IMAGE->AddImage("ice_boss", "Ingame/Ice/mob/boss/boss", 11);
						loadCount++;
					}
				}

				// city
				{
					IMAGE->AddImage("city_Under", "Ingame/City/under");
					loadCount++;
					IMAGE->AddImage("city_High", "Ingame/City/high");
					loadCount++;

					//mob
					{
						IMAGE->AddImage("city_mob1", "Ingame/City/mob/mob1/mob1", 15);
						loadCount++;
						IMAGE->AddImage("city_mob2", "Ingame/City/mob/mob2/mob2", 6);
						loadCount++;
						IMAGE->AddImage("city_boss", "Ingame/City/mob/boss/boss", 10);
						loadCount++;
					}
				}

				// city(night)
				{
					IMAGE->AddImage("city(night)_Under", "Ingame/city(night)/under");
					loadCount++;
					IMAGE->AddImage("city(night)_high", "Ingame/city(night)/high");
					loadCount++;

					//mob
					{
						IMAGE->AddImage("city(night)_mob1", "Ingame/city(night)/mob/mob1/mob1", 11);
						loadCount++;
						IMAGE->AddImage("city(night)_mob2", "Ingame/city(night)/mob/mob2/mob2", 8);
						loadCount++;
						IMAGE->AddImage("city(night)_boss", "Ingame/city(night)/mob/boss/boss", 8);
						loadCount++;
					}
				}

				// ocean
				{
					IMAGE->AddImage("ocean_Under", "Ingame/Ocean/under");
					loadCount++;
					IMAGE->AddImage("ocean_High", "Ingame/Ocean/high");
					loadCount++;

					//mob
					{
						IMAGE->AddImage("ocean_mob1", "Ingame/Ocean/mob/mob1/mob1", 7);
						loadCount++;
						IMAGE->AddImage("ocean_mob2", "Ingame/Ocean/mob/mob2/mob2", 9);
						loadCount++;
						IMAGE->AddImage("ocean_boss", "Ingame/Ocean/mob/boss/boss", 8);
						loadCount++;
					}
				}

				// desert
				{
					IMAGE->AddImage("desert_Under", "Ingame/Desert/desert_Under");
					loadCount++;
					IMAGE->AddImage("desert_High", "Ingame/Desert/desert_High");
					loadCount++;

					//mob
					{
						IMAGE->AddImage("desert_mob1", "Ingame/Desert/mob/mob1/mob1", 6);
						loadCount++;
						IMAGE->AddImage("desert_mob2", "Ingame/Desert/mob/mob2/mob2", 6);
						loadCount++;
						IMAGE->AddImage("desert_boss1", "Ingame/Desert/mob/boss/1/boss1", 8);
						loadCount++;
						IMAGE->AddImage("desert_boss2", "Ingame/Desert/mob/boss/2/boss2", 8);
						loadCount++;
					}
				}

				// church
				{
					IMAGE->AddImage("church_Under", "Ingame/Church/under");
					loadCount++;
					IMAGE->AddImage("church_high", "Ingame/Church/high");
					loadCount++;

					//mob
					{
						IMAGE->AddImage("church_mob1", "Ingame/Church/mob/mob1/mob1", 19);
						loadCount++;
						IMAGE->AddImage("church_mob2", "Ingame/Church/mob/mob2/mob2", 17);
						loadCount++;
						IMAGE->AddImage("church_boss", "Ingame/Church/mob/boss/boss", 10);
						loadCount++;
					}
				}

				// jungle
				{
					IMAGE->AddImage("jungle_Under", "Ingame/Jungle/under");
					loadCount++;
					IMAGE->AddImage("jungle_High", "Ingame/Jungle/high");
					loadCount++;

					// mob
					{
						IMAGE->AddImage("jungle_mob1", "Ingame/Jungle/mob/mob1/mob1", 14);
						loadCount++;
						IMAGE->AddImage("jungle_mob2", "Ingame/Jungle/mob/mob2/mob2", 10);
						loadCount++;
						IMAGE->AddImage("jungle_mob3", "Ingame/Jungle/mob/mob3/mob3", 5);
						loadCount++;
						IMAGE->AddImage("jungle_boss", "Ingame/Jungle/mob/boss/boss", 8);
						loadCount++;
					}
				}

				// UI
				IMAGE->AddImage("IngameBG", "Ingame/UI/AllBG");
				loadCount++;
				IMAGE->AddImage("Ingame_HP", "Ingame/UI/HP");
				loadCount++;
				IMAGE->AddImage("Ingame_HP0", "Ingame/UI/HP0");
				loadCount++;
				IMAGE->AddImage("Ingame_HP1", "Ingame/UI/HP1");
				loadCount++;
				IMAGE->AddImage("Ingame_HP2", "Ingame/UI/HP2");
				loadCount++;
				IMAGE->AddImage("Ingame_HP3", "Ingame/UI/HP3");
				loadCount++;
				IMAGE->AddImage("Ingame_Item", "Ingame/UI/item");
				loadCount++;
				IMAGE->AddImage("colon", "Ingame/UI/colon");
				loadCount++;
				t_Delay = nullptr;
				bundle++;
			});
	}

	if (bundle == 6 && t_Delay == nullptr)
	{
		t_Delay = new cTimer(2, [&]()->void
			{
				// public
				IMAGE->AddImage("Arrow", "Public/Arrow");
				loadCount++;
				IMAGE->AddImage("_Arrow", "Public/_Arrow");
				loadCount++;
				//IMAGE->AddImage("Cursor", "Public/Cursor");
				IMAGE->AddImage("Blur", "Public/Blur");
				loadCount++;

				// EndScene
				IMAGE->AddImage("end_restart", "EndScene/restart");
				loadCount++;
				IMAGE->AddImage("end_title", "EndScene/title");
				loadCount++;
				IMAGE->AddImage("end_worldmap", "EndScene/worldmap");
				loadCount++;

				IMAGE->AddImage("Boss", "Boss");
				loadCount++;

				IMAGE->AddImage("Hp+", "Hp+");
				loadCount++;
				IMAGE->AddImage("Speed+", "Speed+");
				loadCount++;
				IMAGE->AddImage("Invincibility", "Invincibility");
				loadCount++;

				IMAGE->AddImage("bullet_enemy", "bullet_enemy");
				loadCount++;
				
				IMAGE->AddImage("bullet_enemy1", "bullet_enemy1");
				loadCount++;

				IMAGE->AddImage("bullet_enemy2", "bullet_enemy2");
				loadCount++;

				t_Delay = nullptr;
				bundle++;
			});
	}
}