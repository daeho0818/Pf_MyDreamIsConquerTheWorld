#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}

cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	IMAGE->AddImage("Cursor", "Public/Cursor");

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

	IMAGE->AddImage("TitleBG", "title/TitleBG");

	IMAGE->AddImage("LoadUI", "LoadScene/LoadUI");

	IMAGE->AddImage("LoadBar", "LoadScene/LoadBar");

	IMAGE->AddImage("BarContent", "LoadScene/BarContent");

	// title
	AddLoad("Logo", "title/Logo");

	AddLoad("start_note", "title/start_note");

	AddLoad("start_button", "title/start_button");

	AddLoad("guide_note", "title/guide_note");

	AddLoad("guide_button", "title/guide_button");

	AddLoad("adven_note", "title/adven_note");

	AddLoad("adven_button", "title/adven_button");

	AddLoad("develop_note", "title/develop_note");

	AddLoad("develop_button", "title/develop_button");

	AddLoad("quit_note", "title/quit_note");

	AddLoad("quit_button", "title/quit_button");

	AddLoad("pattern", "title/pattern");

	// guide Note
	AddLoad("guide_BG", "title/GuideBook/BG");

	AddLoad("guide_Arrow", "title/GuideBook/arrow");

	AddLoad("guide_close", "title/GuideBook/close");

	AddLoad("guide_text1", "title/GuideBook/text1");

	AddLoad("guide_text2", "title/GuideBook/text2");

	//adventure Note
	AddLoad("adven_BG", "title/AdvenBook/AllBG");

	AddLoad("adven_Back", "title/AdvenBook/back");

	AddLoad("adven_Chain", "title/AdvenBook/lock_chains");

	AddLoad("adven_CircleDown", "title/AdvenBook/circleDown");

	AddLoad("adven_CircleUp", "title/AdvenBook/circleUp");

	AddLoad("adven_CollectionPer", "title/AdvenBook/collectionPer");

	AddLoad("adven_CollectionPerBG", "title/AdvenBook/collectionPerBG");

	AddLoad("adven_CollectionPerRect", "title/AdvenBook/collectionPerRect");

	AddLoad("adven_ContentRect", "title/AdvenBook/contentRect");

	AddLoad("adven_DontClear", "title/AdvenBook/dontClear");

	AddLoad("symbol_church", "title/AdvenBook/Symbol/church");

	AddLoad("symbol_church_name", "title/AdvenBook/Symbol/church_name");

	AddLoad("symbol_city", "title/AdvenBook/Symbol/city");

	AddLoad("symbol_city_name", "title/AdvenBook/Symbol/city_name");

	AddLoad("symbol_city(night)", "title/AdvenBook/Symbol/city(night)");

	AddLoad("symbol_city(night)_name", "title/AdvenBook/Symbol/city(night)_name");

	AddLoad("symbol_desert", "title/AdvenBook/Symbol/desert");

	AddLoad("symbol_desert_name", "title/AdvenBook/Symbol/desert_name");

	AddLoad("symbol_ice", "title/AdvenBook/Symbol/ice");

	AddLoad("symbol_ice_name", "title/AdvenBook/Symbol/ice_name");

	AddLoad("symbol_ocean", "title/AdvenBook/Symbol/ocean");

	AddLoad("symbol_ocean_name", "title/AdvenBook/Symbol/ocean_name");

	AddLoad("symbol_jungle", "title/AdvenBook/Symbol/jungle");

	AddLoad("symbol_jungle_name", "title/AdvenBook/Symbol/jungle_name");

	// world map
	AddLoad("WorldMap", "WorldMap/map");

	AddLoad("WorldEmblem", "WorldMap/Emblem");

	AddLoad("X", "WorldMap/Details/public/x");

	AddLoad("church_button", "WorldMap/church_button");

	AddLoad("church_button_over", "WorldMap/church_button_over");

	AddLoad("church_button_down", "WorldMap/church_button_down");

	AddLoad("church_complete", "WorldMap/church_complete");

	AddLoad("church_lock", "WorldMap/church_lock");

	AddLoad("city(night)_button", "WorldMap/city(night)_button");

	AddLoad("city(night)_button_over", "WorldMap/city(night)_button_over");

	AddLoad("city(night)_button_down", "WorldMap/city(night)_button_down");

	AddLoad("city(night)_complete", "WorldMap/city(night)_complete");

	AddLoad("city(night)_lock", "WorldMap/city(night)_lock");

	AddLoad("city_button", "WorldMap/city_button");

	AddLoad("city_button_over", "WorldMap/city_button_over");

	AddLoad("city_button_down", "WorldMap/city_button_down");

	AddLoad("city_complete", "WorldMap/city_complete");

	AddLoad("city_lock", "WorldMap/city_lock");

	AddLoad("desert_button", "WorldMap/desert_button");

	AddLoad("desert_button_over", "WorldMap/desert_button_over");

	AddLoad("desert_button_down", "WorldMap/desert_button_down");

	AddLoad("desert_complete", "WorldMap/desert_complete");

	AddLoad("desert_lock", "WorldMap/desert_lock");

	AddLoad("ice_button", "WorldMap/ice_button");

	AddLoad("ice_button_over", "WorldMap/ice_button_over");

	AddLoad("ice_button_down", "WorldMap/ice_button_down");

	AddLoad("ice_complete", "WorldMap/ice_complete");

	AddLoad("ice_lock", "WorldMap/ice_lock");

	AddLoad("jungle_button", "WorldMap/jungle_button");

	AddLoad("jungle_button_over", "WorldMap/jungle_button_over");

	AddLoad("jungle_button_down", "WorldMap/jungle_button_down");

	AddLoad("jungle_complete", "WorldMap/jungle_complete");

	AddLoad("jungle_lock", "WorldMap/jungle_lock");

	AddLoad("ocean_button", "WorldMap/ocean_button");

	AddLoad("ocean_button_over", "WorldMap/ocean_button_over");

	AddLoad("ocean_button_down", "WorldMap/ocean_button_down");

	AddLoad("ocean_complete", "WorldMap/ocean_complete");

	AddLoad("ocean_lock", "WorldMap/ocean_lock");

	AddLoad("church_item", "Title/AdvenBook/성소");

	AddLoad("city_item", "Title/AdvenBook/도시낮");

	AddLoad("city(night)_item", "Title/AdvenBook/도시밤");

	AddLoad("desert_item", "Title/AdvenBook/사막");

	AddLoad("ice_item", "Title/AdvenBook/남극");

	AddLoad("jungle_item", "Title/AdvenBook/정글");

	AddLoad("ocean_item", "Title/AdvenBook/바다");

	AddLoad("church_con", "Title/AdvenBook/성소설명");

	AddLoad("city_con", "Title/AdvenBook/도시(낮)설명");

	AddLoad("city(night)_con", "Title/AdvenBook/도시(밤)설명");

	AddLoad("desert_con", "Title/AdvenBook/사막설명");

	AddLoad("ice_con", "Title/AdvenBook/남극설명");

	AddLoad("jungle_con", "Title/AdvenBook/정글설명");

	AddLoad("ocean_con", "Title/AdvenBook/바다설명");

	AddLoad("church_All", "WorldMap/Details/Church/All");

	AddLoad("city_All", "WorldMap/Details/City/All");

	AddLoad("city(night)_All", "WorldMap/Details/City(night)/All");

	AddLoad("desert_All", "WorldMap/Details/Desert/All");

	AddLoad("ice_All", "WorldMap/Details/Ice/All");

	AddLoad("jungle_All", "WorldMap/Details/Jungle/All");

	AddLoad("ocean_All", "WorldMap/Details/Ocean/All");

	AddLoad("StageStartB", "WorldMap/Details/Public/Start");

	AddLoad("cloud1", "WorldMap/cloud/cloud1");

	AddLoad("cloud2", "WorldMap/cloud/cloud2");

	AddLoad("cloud3", "WorldMap/cloud/cloud3");

	AddLoad("cloud4", "WorldMap/cloud/cloud4");

	// ingame
	{
		AddLoad("player", "Ingame/player");

		AddLoad("h_player", "Ingame/h_player");


		//  start
		AddLoad("start_1", "Ingame/Start/1");

		AddLoad("start_2", "Ingame/Start/2");

		AddLoad("start_3", "Ingame/Start/3");

		AddLoad("start_start", "Ingame/Start/start");

		AddLoad("start_game", "Ingame/Start/game");


		//  stop
		AddLoad("stop_BG", "Ingame/Stop/BG");

		AddLoad("stop_text", "Ingame/Stop/text");

		AddLoad("stop_back", "Ingame/Stop/back");

		AddLoad("stop_restart", "Ingame/Stop/restart");

		AddLoad("stop_worldmap", "Ingame/Stop/worldmap");

		AddLoad("stop_pointline", "Ingame/Stop/pointline");


		// clear / fail
		AddLoad("CFgetItem", "Ingame/Clear,Fail/getItem");

		AddLoad("CFpercent", "Ingame/Clear,Fail/percent");

		AddLoad("CFscore", "Ingame/Clear,Fail/score");

		AddLoad("CFtime", "Ingame/Clear,Fail/time");

		AddLoad("CFBG", "Ingame/Clear,Fail/BG");

		AddLoad("CFnext", "Ingame/Clear,Fail/next");

		// clear
		{
			AddLoad("Clear", "Ingame/Clear,Fail/Clear/clear");

			AddLoad("G", "Ingame/Clear,Fail/Clear/g");

			AddLoad("M", "Ingame/Clear,Fail/Clear/m");

			AddLoad("C", "Ingame/Clear,Fail/Clear/1. c");

			AddLoad("L", "Ingame/Clear,Fail/Clear/2. l");

			AddLoad("E", "Ingame/Clear,Fail/Clear/3. e");

			AddLoad("A", "Ingame/Clear,Fail/Clear/4. a");

			AddLoad("R", "Ingame/Clear,Fail/Clear/5. r");

			AddLoad("!", "Ingame/Clear,Fail/Clear/6. !");

		}

		// fail
		{
			AddLoad("Over", "Ingame/Clear,Fail/Fail/over");

			AddLoad("OVER_G", "Ingame/Clear,Fail/Fail/g");

			AddLoad("OVER_A", "Ingame/Clear,Fail/Fail/a");

			AddLoad("OVER_M", "Ingame/Clear,Fail/Fail/m");

			AddLoad("O", "Ingame/Clear,Fail/Fail/1. o");

			AddLoad("V", "Ingame/Clear,Fail/Fail/2. v");

			AddLoad("OVER_E", "Ingame/Clear,Fail/Fail/3. e");

			AddLoad("OVER_R", "Ingame/Clear,Fail/Fail/4. r");

		}
	}


	// ice
	{
		AddLoad("ice_Under", "Ingame/Ice/under");

		AddLoad("ice_High", "Ingame/Ice/high");


		// mob
		{
			AddLoad("ice_mob1", "Ingame/Ice/mob/mob1/mob1", 6);

			AddLoad("ice_mob2", "Ingame/Ice/mob/mob2/mob2", 6);

			AddLoad("ice_boss", "Ingame/Ice/mob/boss/boss", 11);

		}
	}

	// city
	{
		AddLoad("city_Under", "Ingame/City/under");

		AddLoad("city_High", "Ingame/City/high");


		//mob
		{
			AddLoad("city_mob1", "Ingame/City/mob/mob1/mob1", 15);

			AddLoad("city_mob2", "Ingame/City/mob/mob2/mob2", 6);

			AddLoad("city_boss", "Ingame/City/mob/boss/boss", 10);

		}
	}

	// city(night)
	{
		AddLoad("city(night)_Under", "Ingame/city(night)/under");

		AddLoad("city(night)_high", "Ingame/city(night)/high");


		//mob
		{
			AddLoad("city(night)_mob1", "Ingame/city(night)/mob/mob1/mob1", 11);

			AddLoad("city(night)_mob2", "Ingame/city(night)/mob/mob2/mob2", 8);

			AddLoad("city(night)_boss", "Ingame/city(night)/mob/boss/boss", 8);

		}
	}

	// ocean
	{
		AddLoad("ocean_Under", "Ingame/Ocean/under");

		AddLoad("ocean_High", "Ingame/Ocean/high");


		//mob
		{
			AddLoad("ocean_mob1", "Ingame/Ocean/mob/mob1/mob1", 7);

			AddLoad("ocean_mob2", "Ingame/Ocean/mob/mob2/mob2", 9);

			AddLoad("ocean_boss", "Ingame/Ocean/mob/boss/boss", 8);

		}
	}

	// desert
	{
		AddLoad("desert_Under", "Ingame/Desert/desert_Under");

		AddLoad("desert_High", "Ingame/Desert/desert_High");


		//mob
		{
			AddLoad("desert_mob1", "Ingame/Desert/mob/mob1/mob1", 6);

			AddLoad("desert_mob2", "Ingame/Desert/mob/mob2/mob2", 6);

			AddLoad("desert_boss1", "Ingame/Desert/mob/boss/1/boss1", 8);

			AddLoad("desert_boss2", "Ingame/Desert/mob/boss/2/boss2", 8);

		}
	}

	// church
	{
		AddLoad("church_Under", "Ingame/Church/under");

		AddLoad("church_high", "Ingame/Church/high");


		//mob
		{
			AddLoad("church_mob1", "Ingame/Church/mob/mob1/mob1", 19);

			AddLoad("church_mob2", "Ingame/Church/mob/mob2/mob2", 17);

			AddLoad("church_boss", "Ingame/Church/mob/boss/boss", 10);

		}
	}

	// jungle
	{
		AddLoad("jungle_Under", "Ingame/Jungle/under");

		AddLoad("jungle_High", "Ingame/Jungle/high");


		// mob
		{
			AddLoad("jungle_mob1", "Ingame/Jungle/mob/mob1/mob1", 14);

			AddLoad("jungle_mob2", "Ingame/Jungle/mob/mob2/mob2", 10);

			AddLoad("jungle_mob3", "Ingame/Jungle/mob/mob3/mob3", 5);

			AddLoad("jungle_boss", "Ingame/Jungle/mob/boss/boss", 8);

		}
	}

	// UI
	AddLoad("IngameBG", "Ingame/UI/AllBG");

	AddLoad("hp_blind", "Ingame/UI/blind");

	AddLoad("Ingame_HP", "Ingame/UI/HP");

	AddLoad("Ingame_HP0", "Ingame/UI/HP0");

	AddLoad("Ingame_HP1", "Ingame/UI/HP1");

	AddLoad("Ingame_HP2", "Ingame/UI/HP2");

	AddLoad("Ingame_HP3", "Ingame/UI/HP3");

	AddLoad("Ingame_Item", "Ingame/UI/item");

	AddLoad("colon", "Ingame/UI/colon");

	AddLoad("time_blind", "Ingame/UI/time_blind");

	// public
	AddLoad("Arrow", "Public/Arrow");

	AddLoad("_Arrow", "Public/_Arrow");

	AddLoad("Blur", "Public/Blur");


	// EndScene
	AddLoad("end_restart", "EndScene/restart");

	AddLoad("end_title", "EndScene/title");

	AddLoad("end_worldmap", "EndScene/worldmap");

	AddLoad("Boss", "Boss");

	AddLoad("Hp+", "Hp+");

	AddLoad("Speed+", "Speed+");

	AddLoad("Invincibility", "Invincibility");

	AddLoad("over_Start", "Title/over_Start");

	AddLoad("over_Adven", "Title/over_Adven");

	AddLoad("over_Develop", "Title/over_Develop");

	AddLoad("over_Guide", "Title/over_Guide");

	AddLoad("over_Quit", "Title/over_Quit");

	AddLoad("click_Start", "Title/click_Start");

	AddLoad("click_Adven", "Title/click_Adven");

	AddLoad("click_Develop", "Title/click_Develop");

	AddLoad("click_Guide", "Title/click_Guide");

	AddLoad("click_Quit", "Title/click_Quit");

	AddLoad("Credit", "Title/DevelopBook/Credit");

	// Bullets
	{
		// Church
		AddLoad("bullet_church_mob1", "Ingame/Church/bullets/mob1");
		AddLoad("bullet_church_mob2", "Ingame/Church/bullets/mob2");
		AddLoad("bullet_church_boss", "Ingame/Church/bullets/boss");

		// City
		AddLoad("bullet_city_mob1", "Ingame/City/bullets/mob1");
		AddLoad("bullet_city_mob2", "Ingame/City/bullets/mob2");
		AddLoad("bullet_city_boss", "Ingame/City/bullets/boss");

		// City (Night)
		AddLoad("bullet_city(night)_mob1", "Ingame/City(night)/bullets/mob1");
		AddLoad("bullet_city(night)_mob2", "Ingame/City(night)/bullets/mob2");
		AddLoad("bullet_city(night)_boss", "Ingame/City(night)/bullets/boss");

		// Desert
		AddLoad("bullet_desert_mob1", "Ingame/Desert/bullets/mob1");
		AddLoad("bullet_desert_mob2", "Ingame/Desert/bullets/mob2");
		AddLoad("bullet_desert_boss1", "Ingame/Desert/bullets/boss1");
		AddLoad("bullet_desert_boss2", "Ingame/Desert/bullets/boss2");

		// Ice
		AddLoad("bullet_ice_mob1", "Ingame/Ice/bullets/mob1");
		AddLoad("bullet_ice_mob2", "Ingame/Ice/bullets/mob2");
		AddLoad("bullet_ice_boss", "Ingame/Ice/bullets/boss");

		// Jungle
		AddLoad("bullet_jungle_mob1", "Ingame/Jungle/bullets/mob1");
		AddLoad("bullet_jungle_mob2", "Ingame/Jungle/bullets/mob2");
		AddLoad("bullet_jungle_mob3", "Ingame/Jungle/bullets/mob3");
		AddLoad("bullet_jungle_boss", "Ingame/Jungle/bullets/boss");

		// Ocean
		AddLoad("bullet_ocean_mob1", "Ingame/Ocean/bullets/mob1");
		AddLoad("bullet_ocean_mob2", "Ingame/Ocean/bullets/mob2");
		AddLoad("bullet_ocean_boss", "Ingame/Ocean/bullets/boss");
	}

	// Effect
	{
		// Church
		AddLoad("church_dead", "Ingame/Church/Effect/dead", 41);

		AddLoad("church_boss_effect", "Ingame/Church/bullets/boss_effect");
		AddLoad("church_mob1_effect", "Ingame/Church/bullets/mob1_effect");
		AddLoad("church_mob2_effect", "Ingame/Church/bullets/mob2_effect");

		// City
		AddLoad("city_dead", "Ingame/City/Effect/dead", 24);

		AddLoad("city_boss_effect", "Ingame/City/bullets/boss_effect");
		AddLoad("city_mob1_effect", "Ingame/City/bullets/mob1_effect");
		AddLoad("city_mob2_effect", "Ingame/City/bullets/mob2_effect");

		// City(Night)
		AddLoad("city(night)_dead", "Ingame/City(night)/Effect/dead", 33);

		AddLoad("city(night)_boss_effect", "Ingame/City(night)/bullets/boss_effect");
		AddLoad("city(night)_mob1_effect", "Ingame/City(night)/bullets/mob1_effect");
		AddLoad("city(night)_mob2_effect", "Ingame/City(night)/bullets/mob2_effect");

		// Jungle
		AddLoad("jungle_dead", "Ingame/Jungle/Effect/dead", 30);

		AddLoad("jungle_boss_effect", "Ingame/Jungle/bullets/boss_effect");
		AddLoad("jungle_mob1_effect", "Ingame/Jungle/bullets/mob1_effect");
		AddLoad("jungle_mob2_effect", "Ingame/Jungle/bullets/mob2_effect");
		AddLoad("jungle_mob3_effect", "Ingame/Jungle/bullets/mob3_effect");

		// Desert
		AddLoad("desert_gold_dead", "Ingame/Desert/Effect/gold/dead", 28);
		AddLoad("desert_silver_dead", "Ingame/Desert/Effect/silver/dead", 30);

		AddLoad("desert_boss1_effect", "Ingame/Desert/bullets/boss1_effect");
		AddLoad("desert_boss2_effect", "Ingame/Desert/bullets/boss2_effect");
		AddLoad("desert_mob1_effect", "Ingame/Desert/bullets/mob1_effect");
		AddLoad("desert_mob2_effect", "Ingame/Desert/bullets/mob2_effect");

		// Ice
		AddLoad("ice_dead", "Ingame/Ice/Effect/dead", 27);

		AddLoad("ice_boss_effect", "Ingame/Ice/bullets/boss_effect");
		AddLoad("ice_mob1_effect", "Ingame/Ice/bullets/mob1_effect");
		AddLoad("ice_mob2_effect", "Ingame/Ice/bullets/mob2_effect");

		// Ocean
		AddLoad("ocean_dead", "Ingame/Ocean/Effect/dead", 15);

		AddLoad("ocean_boss_effect", "Ingame/Ocean/bullets/boss_effect");
		AddLoad("ocean_mob1_effect", "Ingame/Ocean/bullets/mob1_effect");
		AddLoad("ocean_mob2_effect", "Ingame/Ocean/bullets/mob2_effect");

		// Color
		{
			AddLoad("white_effect", "Effect/white_Effect");
			AddLoad("red_effect", "Effect/red_Effect");
		}
	}

	SOUND->AddSound("draw_line", L"draw_line");
	SOUND->AddSound("button", L"button");
	SOUND->AddSound("fillplace", L"fillplace");
	SOUND->AddSound("attack", L"attack");
		
	listCount = loadList.size();

	//thread = new cThreadPool(1);
	//thread->EnqueueJob([&]()->void {AddResource(); });
}

void cLoadingScene::Update()
{
	if (!loadList.empty())
	{
		LoadInfo load = loadList.back();
		loadList.pop_back();

		IMAGE->AddImage(load.key, load.path, load.count);
	}

	else
	{
		BG->isLoadScene = false;
		BG->ptr[0] = IMAGE->FindImage("player");
		BG->ptr[1] = IMAGE->FindImage("player");

		SCENE->ChangeScene("cTitleScene");
	}
}

void cLoadingScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));

	RENDER->CenterRender(IMAGE->FindImage("LoadUI"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 1.5);
	int percent = 100 - (loadList.size() * 100 / listCount);

	int hon, ten, one;
	if (percent > 99) { hon = 1; ten = 0; one = 0; }
	else { hon = 0; ten = percent / 10; one = percent % 10; }

	char key[3];
	sprintf(key, "%d", hon);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 - 50));

	sprintf(key, "%d", ten);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 - 50, WINSIZEY / 2 - 50));

	sprintf(key, "%d", one);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 + 50, WINSIZEY / 2 - 50));

	RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(WINSIZEX / 2 + 160, WINSIZEY / 2 - 50));
}

void cLoadingScene::UIRender()
{
	float width = IMAGE->FindImage("LoadBar")->info.Width;
	float height = IMAGE->FindImage("LoadBar")->info.Height;
	RECT barRc = {
		0,
		0,
		width,
		height
	};
	RECT conRc = {
		0,
		0,
		width / 100 * (100 - (loadList.size() * 100 / listCount)),
		height
	};
	UI->CropRender(IMAGE->FindImage("BarContent"), Vec2(960, 580), conRc);
	UI->CropRender(IMAGE->FindImage("LoadBar"), Vec2(960, 580), barRc);
}

void cLoadingScene::Release()
{
	SAFE_DELETE(thread);
}


void cLoadingScene::AddLoad(string key, string path, int count)
{
	loadList.emplace_back(LoadInfo(key, path, count));
}

void cLoadingScene::AddResource()
{
	while(!loadList.empty())
	{
		LoadInfo load = loadList.back();
		loadList.pop_back();

		IMAGE->AddImage(load.key, load.path, load.count);
	}

	BG->isLoadScene = false;
	BG->ptr[0] = IMAGE->FindImage("player");
	BG->ptr[1] = IMAGE->FindImage("player");

	SCENE->ChangeScene("cTitleScene");
}
