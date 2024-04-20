#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
	level = nullptr;
	singleBubble = nullptr;
	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom
	eBubblingTime = 0;
	eTimeSpawnX = GetRandomValue(-1, 1);
	eTimeSpawnY = GetRandomValue(-1, 1);
	debug = DebugMode::OFF;
	AllObjects = 0;
	HighScore = 0;

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
	if (singleBubble != nullptr)
	{
		singleBubble->Release();
		delete singleBubble;
		singleBubble = nullptr;
	}
	for (Entity* obj : objects)
	{
		delete obj;
	}
	for (Entity* bubl : bubbles)
	{
		delete bubl;
	}
	for (Entity* bubles : bubblesPlayer)
	{
		delete bubles;
	}
	for (Entity* enemy : enemies)
	{
		delete enemy;
	}
	objects.clear();
	enemies.clear();
	bubbles.clear();
	bubblesPlayer.clear();

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
	
		for (Enemy* enemy : enemies)
		{
			if (enemy != nullptr) {
				enemy->SetTileMap(level);

			}
		}

	return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage)
{
	int size;
	int x, y, i;
	Tile tile;
	Point pos;
	int* map = nullptr;
	Object* obj;
	Bubble* bubl;
	Enemy* ene;

	ClearLevel();
	size = LEVEL_WIDTH * LEVEL_HEIGHT;

	if (stage == 1)
	{
		map = new int[size] {
			1, 3,173,173,173,173,173,173,173,173,173,173,173,173,173, 2,
				2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 5, 0, 0, 0, 0, 0, 103, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 3, 4, 12, 11, 11, 11, 11, 11, 11, 11, 11, 13, 0, 16, 2,
				2, 5, 0, 0, 59, 0, 0, 103, 0, 0, 0, 59, 0, 0, 0, 2,
				2, 43, 21, 17, 42, 42, 42, 42, 42, 42, 42, 42, 18, 0, 42, 2,
				2, 9, 6, 10, 19, 19, 19, 19, 19, 19, 19, 19, 20, 0, 7, 2,
				2, 5, 0, 0, 59, 0, 0, 103,  0, 0, 0, 59, 0, 0, 0, 2,
				2, 3, 4, 12, 11, 11, 11, 11, 11, 11, 11, 11, 13, 0, 16, 2,
				2, 5, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
				2, 43, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 2
			};
		player->InitScore();


	}
	else if (stage == 2)
	{
		map = new int[size] {
			150, 158, 171, 171, 153, 0, 172, 171, 171, 153, 0, 172, 171, 171, 171, 151,
				151, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 151,
				151, 162, 156, 155, 155, 155, 157, 0, 0, 156, 155, 155, 155, 157, 0, 151,
				151, 162, 160, 164, 166, 166, 163, 0, 0, 165, 166, 166, 166, 161, 0, 151,
				151, 162, 160, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 161, 0, 151,
				151, 162, 160, 158, 152, 152, 152, 167, 0, 168, 152, 152, 152, 161, 0, 151,
				151, 162, 160, 162, 0, 0,102, 0, 0, 59, 59, 0, 0, 161, 0, 151,
				151, 162, 160, 159, 155, 155, 155, 157, 156, 155, 155, 155, 155, 161, 0, 151,
				151, 162, 165, 166, 166, 166, 166, 163, 165, 166, 166, 166, 166, 163, 0, 151,
				151, 162, 0, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 59, 0, 151,
				151, 158, 152, 170, 154, 152, 169, 0, 0, 0, 168, 170, 154, 152, 152, 151,
				151, 162, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 151,
				151, 159, 155, 155, 157,  0, 156, 155, 155, 157, 0, 156, 155, 155, 155, 151
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
			else if (tile == Tile::ZENCHAN)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				ene = new Enemy(pos, StateEnemy::IDLE,  LookEnemy::LEFT, Type::ZEN_CHAN);
				ene->Initialise();
				ene->SetTileMap(level);
				enemies.push_back(ene);				

				map[i] = 0;
			}
			else if (tile == Tile::BUBBLE)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				bubl = new Bubble(pos, Direction::LEFT);

				bubbles.push_back(bubl);
				map[i] = 0;
			}
			else if (tile == Tile::OBJECT)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos);
				objects.push_back(obj);
				AllObjects++;
				map[i] = 0;
			}
			
			++i;
		}
	}
	level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);

	return AppStatus::OK;
}
void Scene::RandomItemSpawn()
{
	
}
void Scene::BubbleSpawner()
{
	int maxTimeX = GetRandomValue(5, 10);
	int maxTimeY = GetRandomValue(5, 10);

	switch (stage)
	{
	case 2:
		Point p1 = { 80, 226 };
		Point p2 = { 160, 226 };
		if (eTimeSpawnX >= maxTimeX)
		{
			Bubble* bubl = new Bubble(p1, Direction::LEFT);
			bubbles.push_back(bubl);
			eTimeSpawnX = 0;
		}
		else if (eTimeSpawnY >= maxTimeY)
		{
			Bubble* bubl2 = new Bubble(p2, Direction::RIGHT);
			bubbles.push_back(bubl2);
			eTimeSpawnY = 0;
		}
		eTimeSpawnX += GetFrameTime();
		eTimeSpawnY += GetFrameTime();
	}
}
void Scene::PlayerBubbleSpawn()
{
	eBubblingTime += GetFrameTime();
	
	if (IsKeyPressed(KEY_S) && eBubblingTime >= .3)
	{
		if (player->IsLookingLeft())
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player->GetPos(), Directions::LEFT);
			buble->Initialise();
			bubblesPlayer.push_back(buble);
			BubbleFromPlayer* singleBubble = new BubbleFromPlayer(player->GetPos(), Directions::LEFT);

		}
		else 
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player->GetPos(), Directions::RIGHT);
			buble->Initialise();
			bubblesPlayer.push_back(buble);
			BubbleFromPlayer* singleBubble = new BubbleFromPlayer(player->GetPos(), Directions::LEFT);
		}
		eBubblingTime = 0;
	
	}
	
	
}
void Scene::Update()
{
	Point p1, p2;
	AABB box;
	PlayerBubbleSpawn();

	//Switch between the different debug modes: off, on (sprites & hitboxes), on (hitboxes) 
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}
	//Debug levels instantly
	if (IsKeyPressed(KEY_ONE))
	{
		stage = 1;
		LoadLevel(1);
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		stage = 2;
		LoadLevel(2);
	}
	level->Update();
	player->Update();
	for (Enemy* ene : enemies)
	{
		ene->Update();
	}
	UpdateBubbles();
	BubbleSpawner();
	for (BubbleFromPlayer* buble : bubblesPlayer)
	{
		buble->SetPlayer(player);
	}
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
void Scene::Release()
{
	level->Release();
	player->Release();
	for (Enemy* ene : enemies)
	{
		ene->Release();
	}
}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box, ene_box;

	player_box = player->GetHitbox();
	auto it = objects.begin();
	while (it != objects.end())
	{
		obj_box = (*it)->GetHitbox();
		if (player_box.TestAABB(obj_box))
		{
			ResourceManager::Instance().PlaySoundEffect(Resource::SFX_ITEM);

			player->IncrScore((*it)->Points());
			AllObjects--;

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
	auto it_enemies = enemies.begin();
	while (it_enemies != enemies.end())
	{
		ene_box = (*it_enemies)->GetHitbox();
		if (player_box.TestAABB(ene_box))
		{
			delete* it_enemies;
			it_enemies = enemies.erase(it_enemies);
		}
		else
		{
			++it_enemies;
		}
	}
	//auto iterator = bubbles.begin();
	//int i = 0;
	//while (iterator != bubbles.end() && i < bubbles.size())
	//{
	//	if (bubbles[i]->isAlive() == false)
	//	{
	//		//Delete the object
	//		delete* iterator;
	//		//Erase the object from the vector and get the iterator to the next valid element
	//		iterator = bubbles.erase(iterator);
	//	}
	//	else
	//	{
	//		//Move to the next object
	//		++iterator;
	//		++i;
	//	}
	//}
	//auto iterate = bubblesPlayer.begin();
	//int o = 0;
	//while (iterate != bubblesPlayer.end() && o < bubblesPlayer.size())
	//{
	//	if (bubblesPlayer[o]->isAlive() == false)
	//	{
	//		//Delete the object
	//		delete* iterate;
	//		//Erase the object from the vector and get the iterate to the next valid element
	//		iterate = bubblesPlayer.erase(iterate);
	//	}
	//	else
	//	{
	//		//Move to the next object
	//		++iterate;
	//		++o;
	//	}
	//}
}
void Scene::ClearLevel()
{
	for (Object* obj : objects)
	{
		delete obj;
	}
	objects.clear();
	for (Bubble* bubl : bubbles)
	{
		delete bubl;
	}
	bubbles.clear();
	for (BubbleFromPlayer* buble : bubblesPlayer)
	{
		delete buble;
	}
	bubblesPlayer.clear();
	for (Enemy* enemi : enemies)
	{
		delete enemi;
	}
	enemies.clear();
}
void Scene::UpdateBubbles()
{
	for (Bubble* bubl : bubbles)
	{
		bubl->Update();
	}
	for (BubbleFromPlayer* buble : bubblesPlayer)
	{
		buble->Update();
	}
}
void Scene::RenderObjects()
{
	for (Object* obj : objects)
	{
		obj->Draw();
	}
	for (Bubble* bubl : bubbles)
	{
		bubl->Draw();
	}
	auto it = bubblesPlayer.begin();
	while (it != bubblesPlayer.end())
	{

		(*it)->Draw();	
		++it;
	}
	for (Enemy* enemi : enemies)
	{
		enemi->Draw();
	}
	
}
void Scene::RenderObjectsDebug(const Color& col) const
{
	for (Object* obj : objects)
	{
		obj->DrawDebug(col);
	}
	for (Bubble* bubl : bubbles)
	{
		bubl->DrawDebug(col);
	}
	for (BubbleFromPlayer* buble : bubblesPlayer)
	{
		buble->DrawDebug(col);
	}
	for (Enemy* enemi : enemies)
	{
		enemi->DrawDebug(col);
	}
}
int Scene::highScore()
{
	if (this == nullptr)
	{
		return 000;
	}
	else if(player->GetScore()>=HighScore)
	{
		HighScore = player->GetScore();
	}
	return HighScore;

}
int Scene::Score() const
{
	if (this == nullptr)
	{
		return 000;
	}
	else
	{
		return player->GetScore();
	}
}
void Scene::ResetScore() const
{
	if(this != nullptr)
	{
		player->InitScore();
	}

}
