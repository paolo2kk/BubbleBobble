#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include "BubbleFromPlayer.h"
#include <raymath.h>

Enemy::Enemy(const Point& p, StateEnemy s, LookEnemy view, Type typeEnemy):
	Entity(p, ENEMY_PHYSICAL_WIDTH, ENEMY_PHYSICAL_HEIGHT, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
{
	state = s;
	look = view;
	type = typeEnemy;
	jump_delay = ENEMY_JUMP_DELAY;
	map = nullptr;
	
}
Enemy::~Enemy()
{

}
AppStatus Enemy::Initialise()
{
	int i;
	const int n = PLAYER_FRAME_SIZE;
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ZENCHAN, "images/zenchan.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_ZENCHAN));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { (float)i * n, (float)0, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float)i * n, (float)0, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::ENOJAO_RIGHT, ANIM_DELAY);
	for (i = 4; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::ENOJAO_RIGHT, { (float)i * n, (float)0, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::ENOJAO_LEFT, ANIM_DELAY);
	for (i = 4; i < 8; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::ENOJAO_LEFT, { (float)i * n, (float)0, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::CAGAO_RIGHT, ANIM_DELAY);
	for (i = 8; i < 14; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::CAGAO_RIGHT, { (float)i * n, (float)0, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::CAGAO_LEFT, ANIM_DELAY);
	for (i = 8; i < 14; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::CAGAO_LEFT, { (float)i * n, (float)0, n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::SPINNER, ANIM_DELAY);
	for (i = 14; i < 17; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::SPINNER, { (float)i * n, (float)0, -n, n });
	sprite->SetAnimationDelay((int)EnemyAnim::BUBBLE_P1, ANIM_DELAY);
	for (i = 17; i < 20; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::BUBBLE_P1, { (float)i * n, (float)0, n, n });


	sprite->SetAnimation((int)EnemyAnim::WALKING_LEFT);


	return AppStatus::OK;
}

void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}

void Enemy::Update()
{
	MoveX();
	MoveY();
	Warp();

}

void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}

void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);

	render->Release();
}

bool Enemy::IsLookingRight() const
{
	return look == LookEnemy::RIGHT;
}

bool Enemy::IsLookingLeft() const
{
	return look == LookEnemy::LEFT;
}

void Enemy::MoveX()
{

	AABB box;
	int prev_x = pos.x;
	int objectiveJumpX = pos.x;


	if (IsKeyDown(KEY_LEFT))
	{
		if (state != StateEnemy::JUMPING) {
			pos.x -= 1;

		}
		isStill = false;
		if (state == StateEnemy::IDLE) StartWalkingLeft();
		else
		{
			if (IsLookingRight()) ChangeAnimLeft();
		}

		box = GetHitbox();
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			if (state == StateEnemy::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallRight(box)) {
			pos.x = prev_x;
			if (state == StateEnemy::WALKING) Stop();

		}

	}
	else if (IsKeyDown(KEY_RIGHT))
	{

		isStill = false;

		if (state != StateEnemy::JUMPING)
		{
			pos.x += 1;
		}


		if (state == StateEnemy::IDLE) StartWalkingRight();
		else
		{
			if (IsLookingLeft()) ChangeAnimRight();
		}

		box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			if (state == StateEnemy::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallLeft(box)) {
			pos.x = prev_x;
			if (state == StateEnemy::WALKING) Stop();

		}
	}
	else
	{
		if (state == StateEnemy::WALKING)
		{
			Stop();
			isStill = true;
		}
	}
}

void Enemy::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != StateEnemy::JUMPING)
	{
	

		pos.y += PLAYER_SPEED;
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == StateEnemy::FALLING) Stop();

			if (IsKeyPressed(KEY_X))
				StartJumping();
		}
		else
		{
			if (state != StateEnemy::FALLING) StartFalling();
		}
		if (state == StateEnemy::FALLING) {
			if (look == LookEnemy::RIGHT) {
				if (map->TestCollisionWallRight(box))
				{
					pos.x -= 1;
				}
				if (map->TestCollisionHalfWallRight(box))
				{
					pos.x -= 1;
				}
				if (map->TestCollisionHalfWallLeft(box))
				{
					pos.x -= 1;
				}
			}
			else if (look == LookEnemy::LEFT) {
				if (map->TestCollisionWallLeft(box))
				{
					pos.x += 1;
				}
				if (map->TestCollisionHalfWallLeft(box))
				{
					pos.x += 1;
				}
				if (map->TestCollisionHalfWallRight(box))
				{
					pos.x += 1;
				}
			}
		}
	}
	else //state == State::JUMPING
	{
		box = GetHitbox();
		jump_delay--;
		if (jump_delay == 0)
		{
			if (isStill == false) {
				if (look == LookEnemy::RIGHT) {
					box = GetHitbox();
					if (map->TestCollisionWallRight(box))
					{
						pos.x -= 2;
					}
					if (map->TestCollisionHalfWallRight(box))
					{
						pos.x -= 2;
					}
					if (map->TestCollisionHalfWallLeft(box))
					{
						pos.x -= 2;
					}
					pos.x += OBJECTIVEJUMP_X;
				}
				else if (look == LookEnemy::LEFT)
				{
					if (map->TestCollisionWallLeft(box))
					{
						pos.x += 2;
					}
					if (map->TestCollisionHalfWallLeft(box))
					{
						pos.x += 2;
					}
					if (map->TestCollisionHalfWallRight(box))
					{
						pos.x += 2;
					}
					pos.x -= OBJECTIVEJUMP_X;

				}
			}

			prev_y = pos.y;
			prev_box = GetHitbox();

			pos.y += dir.y;
			dir.y += GRAVITY_FORCE;
			jump_delay = PLAYER_JUMP_DELAY;


			//Is the jump finished?
			if (dir.y > PLAYER_JUMP_LIMIT)
			{
				dir.y = PLAYER_SPEED;
				StartFalling();
			}
			
			//We check ground collision when jumping down
			if (dir.y >= 0)
			{
				box = GetHitbox();

	
				if (!map->TestCollisionGround(prev_box, &prev_y) &&
					map->TestCollisionGround(box, &pos.y))
				{
					Stop();
				}

			}
			else {
				box = GetHitbox();


				if (map->TestCollisionHead(box, &pos.y))
				{
					Stop();
				}
			}

		}

	}
}

void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Enemy::Stop()
{
	dir = { 0,0 };
	state = StateEnemy::IDLE;
	isStill = true;
	if (IsLookingRight())	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
	else					SetAnimation((int)EnemyAnim::WALKING_LEFT);
}

void Enemy::StartWalkingLeft()
{
	state = StateEnemy::WALKING;
	look = LookEnemy::LEFT;
	SetAnimation((int)EnemyAnim::WALKING_LEFT);
}

void Enemy::StartWalkingRight()
{
	state = StateEnemy::WALKING;
	look = LookEnemy::RIGHT;
	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}

void Enemy::StartFalling()
{

	dir.y = ENEMY_SPEED + 1;
	state = StateEnemy::FALLING;

}

void Enemy::StartJumping()
{
	dir.y = -ENEMY_JUMP_LIMIT;
	state = StateEnemy::JUMPING;
	jump_delay = PLAYER_JUMP_DELAY;
}

void Enemy::ChangeAnimRight()
{
	look = LookEnemy::RIGHT;
	switch (state)
	{
	case StateEnemy::WALKING: SetAnimation((int)EnemyAnim::WALKING_RIGHT); break;
	}
}

void Enemy::ChangeAnimLeft()
{
	look = LookEnemy::RIGHT;
	switch (state)
	{
	case StateEnemy::WALKING: SetAnimation((int)EnemyAnim::WALKING_LEFT); break;
	}
}

bool Enemy::IsAscending() const
{
	return dir.y < -ENEMY_LEVITATING_SPEED;
}

bool Enemy::IsLevitating() const
{
	return abs(dir.y) <= ENEMY_LEVITATING_SPEED;

}

bool Enemy::IsDescending() const
{
	return dir.y > ENEMY_LEVITATING_SPEED;
}
