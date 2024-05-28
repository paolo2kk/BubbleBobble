#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
	player2 = nullptr;
	level = nullptr;
	enemies = nullptr;
	shots = nullptr;
	particles = nullptr;
	P2in = false;
	P1in = true;

	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom
	eBubblingTime = 0;
	eTimeSpawnX = GetRandomValue(-1, 1);
	eTimeSpawnY = GetRandomValue(-1, 1);
	debug = DebugMode::OFF;
	AllObjects = 0;
	enemy = nullptr;

}
Scene::~Scene()
{
	if (player != nullptr)
	{
		player->Release();
		delete player;
		player = nullptr;
	}
	if (player2 != nullptr)
	{
		player2->Release();
		delete player2;
		player2 = nullptr;
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
		obj = nullptr;
	}
	for (Entity* bubl : bubbles)
	{
		delete bubl;
		bubl = nullptr;
	}
	for (BubbleFromPlayer* bubles : bubblesPlayer)
	{
		bubles->Release();
		delete bubles;
		bubles = nullptr;
		
	}
	if (enemies != nullptr)
	{
		enemies->Release();
		delete enemies;
		enemies = nullptr;
	}
	if (shots != nullptr)
	{
		delete shots;
		shots = nullptr;
	}
	if (particles != nullptr)
	{
		delete particles;
		particles = nullptr;
	}
	projectiles.clear();
	objects.clear();
	bubbles.clear();
	bubblesPlayer.clear();

}
AppStatus Scene::Init()
{
	player = new Player({ 0,0 }, State::IDLE, Look::RIGHT);
	if (player == nullptr)
	{
		LOG("Failed to allocate memory for Player");
		return AppStatus::ERROR;
	}
	player2 = new Player2({ 0,0 }, State2::IDLE, Look::LEFT);
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
	if (player2->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Player");
		return AppStatus::ERROR;
	}

	//Create enemy manager
	enemies = new EnemyManager();
	if (enemies == nullptr)
	{
		LOG("Failed to allocate memory for Enemy Manager");
		return AppStatus::ERROR;
	}
	//Initialise enemy manager
	if (enemies->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Enemy Manager");
		return AppStatus::ERROR;
	}

	//Create shot manager 
	shots = new ShotManager();
	if (shots == nullptr)
	{
		LOG("Failed to allocate memory for Shot Manager");
		return AppStatus::ERROR;
	}
	//Initialise shot manager
	if (shots->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Shot Manager");
		return AppStatus::ERROR;
	}

	//Create particle manager 
	particles = new ParticleManager();
	if (particles == nullptr)
	{
		LOG("Failed to allocate memory for Particle Manager");
		return AppStatus::ERROR;
	}
	//Initialise particle manager
	if (particles->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Particle Manager");
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
	enemies->SetTileMap(level);

	//Load level
	if (LoadLevel(1) != AppStatus::OK)
	{
		LOG("Failed to load Level 1");
		return AppStatus::ERROR;
	}

	//Assign the tile map reference to the player to check collisions while navigating
	player->SetTileMap(level);
	player2->SetTileMap(level);
	//Assign the tile map reference to the shot manager to check collisions when shots are shot
	shots->SetTileMap(level);
	//Assign the particle manager reference to the shot manager to add particles when shots collide
	shots->SetParticleManager(particles);
	//Assign the shot manager reference to the enemy manager so enemies can add shots
	enemies->SetShotManager(shots);

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
	AABB hitbox, area;


	ClearLevel();
	size = LEVEL_WIDTH * LEVEL_HEIGHT;

	if (stage == 1)
	{
		map = new int[size] {
			    1,   3, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173,  2,
				2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				2,   5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  2,
				2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				2,   5,   0,   0,  59,   0,   0,   0, 103,   0,   0,  59,   0,   0,   0,  2,
				2,  43,  21,  17,  42,  42,  42,  42,  42,  42,  42,  42,  18,   0,  42,  2,
				2,   9,   6,  10,  19,  19,  19,  19,  19,  19,  19,  19,  20,   0,   7,  2,
				2,   5,   0,   0,  59,  0 ,   0,   0, 103,   0,   0,  59,   0,   0,   0,  2,
				2,   3,   4,  12,  11,  11,  11,  11,  11,  11,  11,  11,  13,   0,  16,  2,
				2,   5, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 106,   0,  2,
				2,  43,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  2
			};
		player->InitScore();


	}
	else if (stage == 2)
	{
		map = new int[size] {
			    150, 158, 171, 171, 153,   0, 172, 171, 171, 153,   0, 172, 171, 171, 171, 151,
				151, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 151,
				151, 162, 156, 155, 155, 155, 157,   0,   0, 156, 155, 155, 155, 157,   0, 151,
				151, 162, 160, 164, 166, 166, 163,   0,   0, 165, 166, 166, 166, 161,   0, 151,
				151, 162, 160, 162,   0,   0,   0,   0,   0,   0,   0,   0,   0, 161,   0, 151,
				151, 162, 160, 158, 152, 152, 152, 167,   0, 168, 152, 152, 152, 161,   0, 151,
				151, 162, 160, 162,   0,   0, 102,   0,   0,  59,  59,   0,   0, 161,   0, 151,
				151, 162, 160, 159, 155, 155, 155, 157, 156, 155, 155, 155, 155, 161,   0, 151,
				151, 162, 165, 166, 166, 166, 166, 163, 165, 166, 166, 166, 166, 163,   0, 151,
				151, 162,   0,  59,   0,   0,   0,   0,   0,   0,   0,   0,   0,  59,   0, 151,
				151, 158, 152, 170, 154, 152, 169,   0,   0,   0, 168, 170, 154, 152, 152, 151,
				151, 162, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0, 103, 106,   0, 151,
				151, 159, 155, 155, 157,   0, 156, 155, 155, 157,   0, 156, 155, 155, 155, 151
			};
	}
	else if (stage == 3)
	{
		map = new int[size] {
			174, 207, 193, 175, 192, 215, 207, 215, 215, 192, 193, 207, 215, 217, 192, 175,
			175, 208, 210, 214, 185, 212, 208, 210, 210, 185, 216, 208, 209, 211, 185, 175,
			175, 208, 209, 211, 185, 208, 208, 209, 210, 185, 208, 208, 210, 214, 192, 175,
			175, 192, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 175,
			175, 185, 105,   0,   0, 107, 107,   0, 107, 105,   0, 105,   0,   0, 105, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 185, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 175,
			175, 176, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 175
		};
	}
	else if (stage == 4)
	{
		map = new int[size] {
				197, 199, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 196,
				196, 201,   0,   0,   0,   0,   0,   0, 105,   0,   0,   0,   0,   0,   0, 196,
				196, 202, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 196,
				196, 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 196,
				196, 201, 105,	 0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 105,   0, 196,
				196, 199, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 196,
				196, 201,   0, 105,   0,   0,   0,   0,   0,   0,   0,   0, 105,   0,   0, 196,
				196, 202, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 196,
				196, 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 196,
				196, 201, 105,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 105,   0, 196,
				196, 199, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 196,
				196, 201, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 106,   0, 196,
				196, 202, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 196
			};
	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;
	}
	level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);

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
			else if (tile == Tile::PLAYER2)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				player2->SetPos(pos);
				map[i] = 0;
			}
			else if (tile == Tile::ZENCHAN)
			{

				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				hitbox = enemies->GetEnemyHitBox(pos, EnemyType::SLIME);
				area = level->GetSweptAreaX(hitbox);
				enemies->Add(pos, EnemyType::SLIME, area);
			}
			else if (tile == Tile::DRUNK)
			{

				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;				
				hitbox = enemies->GetEnemyHitBox(pos, EnemyType::SLIME);
				area = level->GetSweptAreaX(hitbox);
				enemies->Add(pos, EnemyType::DRUNK, area);
			}
			else if (tile == Tile::DRUNKR)
			{

				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				hitbox = enemies->GetEnemyHitBox(pos, EnemyType::SLIME);
				area = level->GetSweptAreaX(hitbox);
				enemies->Add(pos, EnemyType::DRUNK, area);
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
	delete[] map;

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
	
	if (IsKeyPressed(KEY_L) && eBubblingTime >= .3 && !player->STOP)
	{
		
		if (player->IsLookingLeft())
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player->GetPos(), Directions::LEFT);
			buble->Initialise();
			buble->SetTileMap(level);
			bubblesPlayer.push_back(buble);

		}
		else 
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player->GetPos(), Directions::RIGHT);
			buble->Initialise();
			buble->SetTileMap(level);
			bubblesPlayer.push_back(buble);
		}
		eBubblingTime = 0;
	
	}
	if ((IsKeyPressed(KEY_H) && eBubblingTime >= .3 && !player2->STOP)&&(P2in==true))
	{

		if (player2->IsLookingLeft())
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player2->GetPos(), Directions::LEFT);
			buble->Initialise();
			buble->SetTileMap(level);
			bubblesPlayer2.push_back(buble);

		}
		else
		{
			BubbleFromPlayer* buble = new BubbleFromPlayer(player2->GetPos(), Directions::RIGHT);
			buble->Initialise();
			buble->SetTileMap(level);
			bubblesPlayer2.push_back(buble);
		}
		eBubblingTime = 0;

	}
	
	
}
void Scene::Update()
{
	Point p1, p2;
	AABB box;
	AABB hitbox;

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
	else if (IsKeyPressed(KEY_THREE))
	{
		stage = 3;
		LoadLevel(3);
	}
	else if (IsKeyPressed(KEY_FOUR))
	{
		stage = 4;
		LoadLevel(4);
	}
	level->Update();
	hitbox = player->GetHitbox();
	hitbox = player2->GetHitbox();
	if (P2in == true)
	{
		player2->Update();
	}
	if (P1in == true)
	{
		player->Update();
	}
	for (Projectile* proj : projectiles)
	{
		proj->Update();
	}
	enemies->Update(hitbox);
	shots->Update(hitbox);
	particles->Update();
	UpdateBubbles();
	BubbleSpawner();
	BubbleDespawn();

	if (P1in==true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer)
		{
			buble->SetPlayer(player);

		}
	}


	if (P2in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer2)
		{
			buble->SetPlayer2(player2);

		}
	}

	CheckCollisions();
}
void Scene::Render()
{
	BeginMode2D(camera);
	level->Render();

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES) {
		RenderObjects();
		enemies->Draw();
		player->Draw();
		player2->Draw();
		shots->Draw();
	}

	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES) {
		RenderObjectsDebug(YELLOW);
		enemies->DrawDebug();
		if (P1in == true)
		{
			player->DrawDebug(GREEN);
		}
		if (P2in == true)
		{
			player->DrawDebug(GREEN);
		}
		shots->DrawDebug(GRAY);
	}
	if (player->IsGod()) {
		DrawText("God Mode", 0, WINDOW_HEIGHT - TILE_SIZE, 100, GOLD);
	}
	if (player2->IsGod()) {
		DrawText("God Mode p2", 0, WINDOW_HEIGHT - TILE_SIZE, 100, GOLD);
	}
	EndMode2D();
}
void Scene::Release()
{
	level->Release();
	player->Release();
	player2->Release();
}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box, ene_box,player2_box;
	if (P1in == true)
	{
		player_box = player->GetHitbox();
	}
	if (P2in == true)
	{
		player2_box = player2->GetHitbox();
	}

	if (P1in == true)
	{
		for (Enemy* enemy : enemies->GetEnemies())
		{
			AABB player_boxx;
			AABB player2_boxx;
			if (P1in == true)
			{
				player_boxx = player->GetHitbox();
			}
			if (P2in == true)
			{
				player2_boxx = player2->GetHitbox();
			}

			AABB enemy_box;
			enemy_box = enemy->GetHitArea();
			if (!enemy->noSpawnMore)
			{

				eTimeBottle += GetFrameTime();

				if (player_boxx.TestAABB(enemy_box) && (P1in == true)) {


					enemy->isshooting = true;

				}

				if ((player2_boxx.TestAABB(enemy_box)) && (P2in == true)) {

					enemy->isshooting = true;
				}
				if (enemy->isshooting && !enemy->noSpawnMore && eTimeBottle > GetRandomValue(5, 8) && (stage == 4 || stage == 3))
				{
					enemy->isshooting = false;
					if (player->GetPos().y > 32 && stage == 4) {

						enemy->lerping = true;

					}
					Projectile* proj = new Projectile(enemy->GetPos(), enemy->GetDir());
					projectiles.push_back(proj);
					eTimeBottle = 0;


				}


			}

		}
		for (BubbleFromPlayer* bubble : bubblesPlayer)
		{
			AABB bubble_box = bubble->GetHitbox();
			for (BubbleFromPlayer* bubble2 : bubblesPlayer)
			{
				if (bubble == bubble2) continue;
				AABB bubble_box2 = bubble2->GetHitbox();

				if (bubble_box.TestAABB(bubble_box2))
				{
					bubble->MoveBubbleToRandomNear();
					bubble2->MoveBubbleToRandomNear();

					break;
				}
			}
			if (player->IsMoving()) {
				if (player->IsLookingRight() && bubble_box.TestAABB(player_box))
				{
					bubble->MoveBubbleRightPlayer();

				}
				if (player->IsLookingLeft() && bubble_box.TestAABB(player_box))
				{
					bubble->MoveBubbleLeftPlayer();

				}
			}

			for (Enemy* enemy : enemies->GetEnemies())
			{

				AABB enemy_box = enemy->GetHitbox();
				if (bubble_box.TestAABB(enemy_box) && bubble->canCollide && !bubble->inCatch)
				{
					if (stage == 1 || stage == 2) {
						bubble->enemytype = 0;
					}
					else if (stage == 4 || stage == 3) {
						bubble->enemytype = 1;

					}
					enemies->DestroyEnemy(enemy);
					bubble->SetAlive(false);
					bubble->inCatch = true;

					break;
				}


			}
			if (bubble_box.TestAABB(player_box) && bubble->inCatch && !bubble->inShoot)
			{
				ResourceManager::Instance().PlaySoundEffect(Resource::SFX_BUBBLE_POP);
				if (bubble->poped == false)
				{
					Point pos = bubble->GetPos();
					BubbleFromPlayer* part = new BubbleFromPlayer(pos,bubble->dire);
					part->Initialise();
					part->popedParticles = true;
					bubblesPlayer.push_back(part);
					
				}
				bubble->poped = true;
				bubble->SetAnimationE((int)Animations::ZENCHAN_DEATH);

				break;
			}
			if ((bubble->hasEndedFromCatch) && (bubble->poped == false)) {
				Point pos = bubble->GetPos();
				pos.x += (SLIME_FRAME_SIZE - SLIME_PHYSICAL_WIDTH) / 2;
				AABB hitbox = enemies->GetEnemyHitBox(pos, EnemyType::SLIME);
				AABB area = level->GetSweptAreaX(hitbox);
				switch (bubble->enemytype) {
				case 0:

					bubble->hasEndedFromCatch = false;
					enemies->Add(pos, EnemyType::SLIME, area);
					break;
				case 1:

					bubble->hasEndedFromCatch = false;
					enemies->Add(pos, EnemyType::DRUNK, area);
					break;

				}

			}
			if (bubble->fruit == true)
			{
				Object* obj = new Object(bubble->GetPos());
				objects.push_back(obj);
				AllObjects++;
				bubble->issAlive = false;
			}

		}

	}
	if (P2in == true)
	{
		for (BubbleFromPlayer* bubble : bubblesPlayer2)
		{
			AABB bubble_box = bubble->GetHitbox();
			for (BubbleFromPlayer* bubble2 : bubblesPlayer2)
			{
				if (bubble == bubble2) continue;
				AABB bubble_box2 = bubble2->GetHitbox();

				if (bubble->dire == Directions::LEFT && bubble2->dire == Directions::LEFT)
				{
					bubble2->StayBehind(bubble);
				}
				/*if (bubble_box.TestAABB(bubble_box2))
				{
					bubble->MoveBubbleToRandomNear();
					bubble2->MoveBubbleToRandomNear();

					break;
				}*/
			}
			if (player2->IsMoving()) {
				if (player2->IsLookingRight() && bubble_box.TestAABB(player2_box))
				{
					bubble->MoveBubbleRightPlayer();

				}
				if (player2->IsLookingLeft() && bubble_box.TestAABB(player_box))
				{
					bubble->MoveBubbleLeftPlayer();

				}
			}

			for (Enemy* enemy : enemies->GetEnemies())
			{

				AABB enemy_box = enemy->GetHitbox();
				if (bubble_box.TestAABB(enemy_box) && bubble->canCollide && !bubble->inCatch)
				{
					if (stage == 1 || stage == 2) {
						bubble->enemytype = 0;
					}
					else if (stage == 4) {
						bubble->enemytype = 1;

					}
					enemies->DestroyEnemy(enemy);
					bubble->SetAlive(false);
					bubble->inCatch = true;

					break;
				}


			}
			if (bubble_box.TestAABB(player2_box) && bubble->inCatch && !bubble->inShoot)
			{
				ResourceManager::Instance().PlaySoundEffect(Resource::SFX_BUBBLE_POP);
				bubble->poped = true;
				bubble->SetAnimationE((int)Animations::ZENCHAN_DEATH);

				break;
			}
			if ((bubble->hasEndedFromCatch) && (bubble->poped == false)) {
				Point pos = bubble->GetPos();
				pos.x += (SLIME_FRAME_SIZE - SLIME_PHYSICAL_WIDTH) / 2;
				AABB hitbox = enemies->GetEnemyHitBox(pos, EnemyType::SLIME);
				AABB area = level->GetSweptAreaX(hitbox);
				switch (bubble->enemytype) {
				case 0:

					enemies->Add(pos, EnemyType::SLIME, area);
					bubble->issAlive = false;
					break;
				case 1:

					enemies->Add(pos, EnemyType::DRUNK, area);
					bubble->issAlive = false;
					break;

				}

			}
			if (bubble->fruit == true)
			{
				Object* obj = new Object(bubble->GetPos());
				objects.push_back(obj);
				AllObjects++;
				bubble->issAlive = false;
			}

		}
	}

	auto it = objects.begin();
	while (it != objects.end())
	{
		obj_box = (*it)->GetHitbox();
		if (player_box.TestAABB(obj_box) && P1in == true)
		{
			ResourceManager::Instance().PlaySoundEffect(Resource::SFX_PICKUP);

			player->IncrScore((*it)->Points());
			(*it)->DeleteHitbox();
			(*it)->point = true;


		}
		else if (player2_box.TestAABB(obj_box) && P2in==true)
		{
			ResourceManager::Instance().PlaySoundEffect(Resource::SFX_PICKUP);

			player2->IncrScore((*it)->Points());
			(*it)->DeleteHitbox();
			(*it)->point = true;
			(*it)->P1 = false;

		}
		else
		{
			//Move to the next object
			++it;
		}
	}
	for (Projectile* proj : projectiles)
	{
		AABB projectile_box = proj->GetHitbox();
		if (player_box.TestAABB(projectile_box) && P1in == true)
		{
			if (player->Ikilleable) {
				Point posplayer = player->GetPos();
				posplayer.y -= 16;
				player->SetPos(posplayer);
				player->SetDeathAnim();
				player->toogleWasHit();
				player->DecLiv();

			}
		}
		if (player2_box.TestAABB(projectile_box)&& P2in==true)
		{
			if (player2->Ikilleable) {
				Point posplayer = player2->GetPos();
				posplayer.y -= 16;
				player2->SetPos(posplayer);
				player2->SetDeathAnim();
				player2->toogleWasHit();
				player2->DecLiv();

			}
		}
	}
	
	if (IsKeyDown(KEY_O)) {

		if (P1in == true)
		{
			Point positionPlayer;
			positionPlayer = player->GetPos();
			AABB hitbox = player->GetHitbox();
			AABB area = level->GetSweptAreaX(hitbox);
			enemies->Add(positionPlayer, EnemyType::BOTTLE, area);
		}

		if (P2in == true)
		{
			Point positionPlayer;
			positionPlayer = player2->GetPos();
			AABB hitbox = player2->GetHitbox();
			AABB area = level->GetSweptAreaX(hitbox);
			enemies->Add(positionPlayer, EnemyType::BOTTLE, area);
		}
	}
}
void Scene::BubbleDespawn()
{
	auto iterator = bubbles.begin();
	int i = 0;
	while (iterator != bubbles.end() && i < bubbles.size())
	{
		if (bubbles[i]->isAlive() == false)
		{
			//Delete the object
			delete* iterator;
			//Erase the object from the vector and get the iterator to the next valid element
			iterator = bubbles.erase(iterator);
		}
		else
		{
			//Move to the next object
			++iterator;
			++i;
		}
	}
	if (P1in == true)
	{
		auto iterate = bubblesPlayer.begin();
		int o = 0;
		while (iterate != bubblesPlayer.end() && o < bubblesPlayer.size())
		{
			if (bubblesPlayer[o]->isAlive() == false || !bubblesPlayer[o]->issAlive)
			{
				//Delete the object
				delete* iterate;
				//Erase the object from the vector and get the iterate to the next valid element
				iterate = bubblesPlayer.erase(iterate);
			}
			else
			{
				//Move to the next object
				++iterate;
				++o;
			}
		}
	}

	if (P2in == true)
	{
		auto iterate = bubblesPlayer2.begin();
		int o = 0;
		while (iterate != bubblesPlayer2.end() && o < bubblesPlayer2.size())
		{
			if (bubblesPlayer2[o]->isAlive() == false || !bubblesPlayer2[o]->issAlive)
			{
				//Delete the object
				delete* iterate;
				//Erase the object from the vector and get the iterate to the next valid element
				iterate = bubblesPlayer2.erase(iterate);
			}
			else
			{
				//Move to the next object
				++iterate;
				++o;
			}
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
	for (Projectile* proj : projectiles)
	{
		delete proj;
	}
	projectiles.clear();
	for (Bubble* bubl : bubbles)
	{
		delete bubl;
	}
	bubbles.clear();
	if (P1in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer)
		{
			delete buble;
		}
		bubblesPlayer.clear();
	}
	if (P2in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer2)
		{
			delete buble;
		}
		bubblesPlayer2.clear();
	}
	enemies->Release();
	shots->Clear();
	particles->Clear();
}
void Scene::UpdateBubbles()
{
	for (Bubble* bubl : bubbles)
	{
		bubl->Update();
	}
	if (P1in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer)
		{
			buble->Update();
		}
	}
	if(P2in==true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer2)
		{
			buble->Update();
		}
	}

}
void Scene::RenderObjects()
{
	auto at = objects.begin();
	while (at != objects.end())
	{
		
		if ((*at)->point==true)
		{
			if ((*at)->pastTime(1) == false)
			{
				(*at)->Draw();
				(*at)->DrawPoints();
				if ((int)(*at)->framecounter % 3 ==0)
				{
					(*at)->PointsAnimation();
				}
			}
			else
			{
				//Delete the object
				delete* at;
				//Erase the object from the vector and get the iterator to the next valid element
				at=objects.erase(at);
				AllObjects--;
				
			}
			
		}
		else
		{
			(*at)->Draw();
		}
		if (at != objects.end())
		{
			++at;
		}

	}

	for (Projectile* proje : projectiles)
	{
		proje->Draw();
	}
	for (Bubble* bubl : bubbles)
	{
		bubl->Draw();
	}
	if (P1in == true)
	{
		auto it = bubblesPlayer.begin();
		while (it != bubblesPlayer.end())
		{

			(*it)->Draw();
			++it;
		}
	}

	if (P2in == true)
	{
		auto it = bubblesPlayer2.begin();
		while (it != bubblesPlayer2.end())
		{

			(*it)->Draw();
			++it;
		}
	}

}
void Scene::RenderObjectsDebug(const Color& col) const
{
	for (Object* obj : objects)
	{
		obj->DrawDebug(col);
	}
	for (Projectile* proj : projectiles)
	{
		proj->DrawDebug(col);
	}
	for (Bubble* bubl : bubbles)
	{
		bubl->DrawDebug(BLUE);
	}
	if (P1in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer)
		{
			buble->DrawDebug(BLUE);
		}
	}
	if (P2in == true)
	{
		for (BubbleFromPlayer* buble : bubblesPlayer2)
		{
			buble->DrawDebug(BLUE);
		}
	}
	
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
int Scene::Score2() const
{
	if (this == nullptr)
	{
		return 000;
	}
	else
	{
		return player2->GetScore();
	}
}
void Scene::ResetScore() const
{
	if(this != nullptr)
	{
		player->InitScore();
		player2->InitScore();
	}

}

