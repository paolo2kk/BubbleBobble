#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
    level = nullptr;
	menu = nullptr;
	
	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom

	debug = DebugMode::OFF;
}
Scene::~Scene()
{
	if (player != nullptr)
	{
		player->Release();
		delete player;
		player = nullptr;
	}
    if (level != nullptr)
    {
		level->Release();
        delete level;
        level = nullptr;
    }
	if (menu != nullptr)
	{
		menu->Release();
		delete menu;
		menu = nullptr;
	}
}

AppStatus Scene::Init()
{
	//Create player
	player = new Player({ 0,0 }, State::IDLE, Look::RIGHT);
	if (player == nullptr)
	{
		LOG("Failed to allocate memory for Player");
		return AppStatus::ERROR;
	}
	//Initialise player
	if (player->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Player");
		return AppStatus::ERROR;
	}

	//Create level 
    level = new TileMap();
    if (level == nullptr)
    {
        LOG("Failed to allocate memory for Level");
        return AppStatus::ERROR;
    }
	//Initialise level
	if (level->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Level");
		return AppStatus::ERROR;
	}
	//Load level
	if (LoadLevel(1) != AppStatus::OK)
	{
		LOG("Failed to load Level 1");
		return AppStatus::ERROR;
	}
	//Assign the tile map reference to the player to check collisions while navigating
	player->SetTileMap(level);

	menu = new UI();
	if (menu == nullptr)
	{
		LOG("Failed to allocate memory for menu");
		return AppStatus::ERROR;
	}
	//Initialise level
	if (menu->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise menu");
		return AppStatus::ERROR;
	}
	//Load level
	if (LoadMenu(1) != AppStatus::OK)
	{
		LOG("Failed to load menu 1");
		return AppStatus::ERROR;
	}

    return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage)
{
	int size;
	int x, y, i;
	Tile tile;
	Point pos;
	
	if(stage == 1)
	{
		size = LEVEL_WIDTH * LEVEL_HEIGHT;
		int map[] = {
				 1,   3,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  21,  17,  42,  42,  42,  42,  42,  42,  42,  42,  18,   0,  42,  2,
				 2,   9,   6,  10,  19,  19,  19,  19,  19,  19,  19,  19,  20,   0,   7,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  2
		};																				   
		//Entities
		i = 0;
		for (y = 0; y < LEVEL_HEIGHT; ++y)
		{

			for (x = 0; x < LEVEL_WIDTH; ++x)
			{
				tile = (Tile)map[i];
				if (tile == Tile::PLAYER)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					player->SetPos(pos);
				}
				++i;
			}
		}
		//Tile map
		level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);
	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;	
	}
	return AppStatus::OK;
}
AppStatus Scene::LoadMenu(int stage)
{
	int size;
	int x, y, i;
	UI_elements tile;
	Point pos;

	if (stage == 1)
	{
		size = MENU_WIDTH * MENU_HEIGHT;
		int map[] = {
				 1,   3,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  21,  17,  42,  42,  42,  42,  42,  42,  42,  42,  18,   0,  42,  2,
				 2,   9,   6,  10,  19,  19,  19,  19,  19,  19,  19,  19,  20,   0,   7,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  2
		};
		//Entities
		i = 0;
		for (y = 0; y < MENU_HEIGHT; ++y)
		{
			for (x = 0; x < MENU_WIDTH; ++x)
			{
				tile = (UI_elements)map[i];
				++i;
			}
		}
		//Tile map
		menu->Load(map, MENU_WIDTH, MENU_HEIGHT);
	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load Menu, stage %d doesn't exist", stage);
		return AppStatus::ERROR;
	}
	return AppStatus::OK;
}
void Scene::Update()
{
	Point p1, p2;
	AABB box;

	//Switch between the different debug modes: off, on (sprites & hitboxes), on (hitboxes) 
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}

	level->Update();
	player->Update();
	menu->Update();
}
void Scene::Render()
 {

	BeginMode2D(camera);

    level->Render();

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		player->Draw();
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		player->DrawDebug(GREEN);

	EndMode2D();
}
void Scene::Release()
{
    level->Release();
	player->Release();
	menu->Release();
}