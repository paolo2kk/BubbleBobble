#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
    level = nullptr;
	bubble = nullptr;
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
	for (Entity* obj : objects)
	{
		delete obj;
	}
	objects.clear();
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
	bubble = new Bubble({ 0,0 }, States::ALIVE, Looks::RIGHT);
	if (bubble == nullptr)
	{
		LOG("Failed to allocate memory for Player");
		return AppStatus::ERROR;
	}
	//Initialise player
	if (bubble->Initialise() != AppStatus::OK)
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
	int* map = nullptr;
	Object *obj;

	ClearLevel();
	size = LEVEL_WIDTH * LEVEL_HEIGHT;

	if(stage == 1)
	{
		map = new int[size] {
				 1,   3,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  11,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   5,   0,   0,  63,   0,   0, 101,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  21,  17,  42,  42,  42,  42,  42,  42,  42,  42,  18,   0,  42,  2,
				 2,   9,   6,  10,  19,  19,  19,  19,  19,  19,  19,  19,  20,   0,   7,  2,
				 2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				 2,   5, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				 2,  43,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  2
		};	
		player->InitScore();

		
	}else if (stage == 2)
	{
		map = new int[size] {
		  150, 158, 171, 171, 153,   0, 172, 171, 171, 153,   0, 172, 171, 171, 171, 151,
		  151, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 151,
		  151, 162, 156, 155, 155, 155, 157,   0,   0, 156, 155, 155, 155, 157,   0, 151,
		  151, 162, 160, 164, 166, 166, 163,   0,   0, 165, 166, 166, 166, 161,   0, 151,
		  151, 162, 160, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0, 161,   0, 151,
		  151, 162, 160, 158, 152, 152, 152, 167,   0, 168, 152, 152, 152, 161,   0, 151,
		  151, 162, 160, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0, 161,   0, 151,
		  151, 162, 160, 159, 155, 155, 155, 157, 156, 155, 155, 155, 155, 161,   0, 151,
		  151, 162, 165, 166, 166, 166, 166, 163, 165, 166, 166, 166, 166, 163,   0, 151,
		  151, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 151,
		  151, 158, 152, 170, 154, 152, 169,   0,   0,   0, 168, 170, 154, 152, 152, 151,
		  151, 162, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 151,
		  151, 159, 155, 155, 157,   0, 156, 155, 155, 157,   0, 156, 155, 155, 155, 151
		};
	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;	
	}
	i = 0;
	for (y = 0; y < LEVEL_HEIGHT; ++y)
	{
		for (x = 0; x < LEVEL_WIDTH; ++x)
		{
			tile = (Tile)map[i];
			if (tile == Tile::EMPTY)
			{
				map[i] = 0;
			}
			else if (tile == Tile::PLAYER)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				player->SetPos(pos);
				map[i] = 0;
			}
			else if (tile == Tile::BUBBLE)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				bubble->SetPos(pos);
				map[i] = 0;
			}
			else if (tile == Tile::ITEM_APPLE)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos, ObjectType::APPLE);
				objects.push_back(obj);
				map[i] = 0;
			}
			else if (tile == Tile::ITEM_CHILI)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos, ObjectType::CHILI);
				objects.push_back(obj);
				map[i] = 0;
			}
			++i;
		}
	}
	level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);

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
	//Debug levels instantly
	if (IsKeyPressed(KEY_ONE))		LoadLevel(1);
	else if (IsKeyPressed(KEY_TWO)) 
	{
		LoadLevel(2); 
	}
	level->Update();
	player->Update();
	bubble->Update();

	CheckCollisions();
}
void Scene::Render()
{
	BeginMode2D(camera);
    level->Render();

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES) {
		RenderObjects();
		player->Draw();
	}
		
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES) {
		RenderObjectsDebug(YELLOW);
		player->DrawDebug(GREEN);
	}


	EndMode2D();
}
void Scene::RenderMenu(const Texture2D* image)
{
	
	DrawTexture(*image, 0, 0, WHITE);
}
void Scene::Release()
{
    level->Release();
	player->Release();
}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box;

	player_box = player->GetHitbox();
	auto it = objects.begin();
	while (it != objects.end())
	{
		obj_box = (*it)->GetHitbox();
		if (player_box.TestAABB(obj_box))
		{
			player->IncrScore((*it)->Points());

			//Delete the object
			delete* it;
			//Erase the object from the vector and get the iterator to the next valid element
			it = objects.erase(it);
		}
		else
		{
			//Move to the next object
			++it;
		}
	}
}
void Scene::ClearLevel()
{
	for (Object* obj : objects)
	{
		delete obj;
	}
	objects.clear();
}
void Scene::RenderObjects() const
{
	for (Object* obj : objects)
	{
		obj->Draw();
	}
}
void Scene::RenderObjectsDebug(const Color& col) const
{
	for (Object* obj : objects)
	{
		obj->DrawDebug(col);
	}
}
void Scene::RenderGUI(const Texture2D image)
{
	//Temporal approach
	DrawTexture(image, 0, 0, WHITE);
	DrawText(TextFormat("%d", player->GetScore()), 38, 8, 3, WHITE);
}