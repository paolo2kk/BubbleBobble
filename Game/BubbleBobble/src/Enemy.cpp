#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Enemy::Enemy(const Point& p, EnemyState s, EnemyLook l, EnemyType t ) :
	Entity(p, ENEMY_PHYSICAL_WIDTH, ENEMY_PHYSICAL_HEIGTH, ENEMY_FRAME_SIZE, ENEMY_FRAME_SIZE)
{
	state = s;
	look = l;
	angryTimer = 0;
	eJumpFrame = 0;
	type = t;
}
Enemy::~Enemy()
{
}
AppStatus Enemy::Initialise()
{
	int i;
	const int n = ENEMY_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ZENCHAN, "images/zenchan.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_ZENCHAN));
	if (render == nullptr)
	{
		LOG("failed to allocate memory for zenchan sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)ZenChanAnimations::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)ZenChanAnimations::WALK_RIGHT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)ZenChanAnimations::WALK_RIGHT, { (float)i * n, 0, -n, n });
	sprite->SetAnimationDelay((int)ZenChanAnimations::WALK_LEFT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)ZenChanAnimations::WALK_LEFT, { (float)i * n, 0, n, n });
	sprite->SetAnimationDelay((int)ZenChanAnimations::ANGRY_LEFT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)ZenChanAnimations::ANGRY_LEFT, { (float)i * n, n, n, n });
	sprite->SetAnimationDelay((int)ZenChanAnimations::ANGRY_RIGHT, ANIM_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)ZenChanAnimations::ANGRY_RIGHT, { (float)i * n, n, -n, n });
	
	if (type == EnemyType::ZENCHAN) {
		if (look == EnemyLook::LEFT) sprite->SetAnimation((int)ZenChanAnimations::WALK_LEFT);
		if (look == EnemyLook::RIGHT) sprite->SetAnimation((int)ZenChanAnimations::WALK_RIGHT);

	}
	else {
		if (look == EnemyLook::LEFT) sprite->SetAnimation((int)ZenChanAnimations::ANGRY_LEFT);
		if (look == EnemyLook::RIGHT) sprite->SetAnimation((int)ZenChanAnimations::ANGRY_RIGHT);

	}
	

	return AppStatus::OK;
}
void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
void Enemy::Update()
{

	switch (type) {
	case EnemyType::ZENCHAN:
		MoveXzenchan();
		break;

	case EnemyType::BANEBOU:
		MoveXbanebou();
		break;
	}
	MoveY();
	Warp();
	
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Enemy::MoveXzenchan()
{
	int prev_x = pos.x;
	AABB box = GetHitbox();
	Sprite* sprite = dynamic_cast<Sprite*>(render);

	if (IsLookingRight()) {
		pos.x += 1;
	}
	else if (IsLookingLeft()) {
		pos.x -= 1;
	}
	if (map->TestCollisionWallLeft(box)) {
		pos.x = prev_x;

		look = EnemyLook::RIGHT;
	}
	else if (map->TestCollisionHalfWallLeft(box)) {
		look = EnemyLook::LEFT;
		sprite->SetAnimation((int)ZenChanAnimations::WALK_LEFT);
	}
	if (pos.x == 17)
	{
		look = EnemyLook::RIGHT;
		sprite->SetAnimation((int)ZenChanAnimations::WALK_RIGHT);

	}
	if (pos.x == WINDOW_WIDTH - 26)
	{
		sprite->SetAnimation((int)ZenChanAnimations::WALK_LEFT);

		look = EnemyLook::LEFT;

	}
	else if (map->TestCollisionWallRight(box)) {
		sprite->SetAnimation((int)ZenChanAnimations::WALK_LEFT);

		look = EnemyLook::LEFT;
	}
	else if (map->TestCollisionHalfWallRight(box))
	{
		sprite->SetAnimation((int)ZenChanAnimations::WALK_RIGHT);

		look = EnemyLook::RIGHT;
	}


}
void Enemy::MoveXbanebou()
{
	int prev_x = pos.x;
	AABB box = GetHitbox();
	Sprite* sprite = dynamic_cast<Sprite*>(render);

	if (IsLookingRight()) {
		pos.x += 1;
	}
	else if (IsLookingLeft()) {
		pos.x -= 1;
	}
	if (map->TestCollisionWallLeft(box)) {
		pos.x = prev_x;

		look = EnemyLook::RIGHT;
	}
	else if (map->TestCollisionHalfWallLeft(box)) {
		look = EnemyLook::LEFT;
		sprite->SetAnimation((int)ZenChanAnimations::ANGRY_LEFT);
	}
	if (pos.x == 17)
	{
		look = EnemyLook::RIGHT;
		sprite->SetAnimation((int)ZenChanAnimations::ANGRY_RIGHT);

	}
	if (pos.x == WINDOW_WIDTH - 26)
	{
		sprite->SetAnimation((int)ZenChanAnimations::ANGRY_LEFT);

		look = EnemyLook::LEFT;

	}
	else if (map->TestCollisionWallRight(box)) {
		sprite->SetAnimation((int)ZenChanAnimations::ANGRY_LEFT);

		look = EnemyLook::LEFT;
	}
	else if (map->TestCollisionHalfWallRight(box))
	{
		sprite->SetAnimation((int)ZenChanAnimations::ANGRY_RIGHT);

		look = EnemyLook::RIGHT;
	}


}
bool Enemy::IsLookingRight()
{
	return look == EnemyLook::RIGHT;
}
bool Enemy::IsLookingLeft()
{
	return look == EnemyLook::LEFT;
}
void Enemy::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != EnemyState::JUMPING)
	{
	
		pos.y += 2;
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == EnemyState::FALLING) Stop();

			if (IsKeyPressed(KEY_SPACE))
				StartJumping();
		}
		else
		{
			if (state != EnemyState::FALLING) StartFalling();
		}
		if (state == EnemyState::FALLING) {
			if (look == EnemyLook::RIGHT) {
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
			else if (look == EnemyLook::LEFT) {
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
			/*if (isStill == false) {
				if (look == Look::RIGHT) {
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
				else if (look == Look::LEFT)
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
			}*/

			prev_y = pos.y;
			prev_box = GetHitbox();

			pos.y += dir.y;
			dir.y += 1;
			jump_delay = 2;


			//Is the jump finished?
			if (dir.y > 9.5)
			{
				dir.y = 1;
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
void Enemy::StartFalling()
{
	dir.y = 2;
	state = EnemyState::FALLING;
	
}
void Enemy::StartJumping()
{
	dir.y = -9.5;
	state = EnemyState::JUMPING;
	
	jump_delay = 2;
}
void Enemy::Stop()
{
	dir = { 0,0 };
	
}
void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_ZENCHAN);

	render->Release();
}