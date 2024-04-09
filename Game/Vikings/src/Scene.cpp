#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
    level = nullptr;
	
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
				 1,  52,  51,  51,  51,  51,  51,  51,  51,  51,  51,  51,  51,  51,   51,	 1,
				 4,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 4,
				 5,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 5,
				 6,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 6,
				 7,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 7,
				 8,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 8,
				 9,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	 9,
			 	10,  25,  29,   0,  27,  26,  26,  26,  26,  26,  26,  26,  28,   0,   27,	10,
				11,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	11,
				12,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	12,
				13,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	13,
				14,  24,  29,   0,  27,  26,  26,  26,  26,  26,  26,  26,  28,   0,   27,	14,
				15,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	15,
				16,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	16,
				17,  50,   0,   0, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	17,
				18,  25,  29,   0,  27,  26,  26,  26,  26,  26,  26,  26,  28,   0,   27,	18,
				19,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	19,
				20,  50,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	0,	20,
				21,  22,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,  23,   23,	21,

				
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
					pos.x = x + TILE_SIZE_WIDTH * 2;
					pos.y = y + TILE_SIZE_HEIGHT * 17;
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
}