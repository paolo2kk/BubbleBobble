#include "Player2.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include "BubbleFromPlayer.h"
#include <raymath.h>


Player2::Player2(const Point& p, State2 s, Look view) :
	Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE, PLAYER_FRAME_SIZE)
{
	state = s;
	look = view;
	jump_delay = PLAYER_JUMP_DELAY;
	map = nullptr;
	score = 0;
}
Player2::~Player2()
{
}
AppStatus Player2::Initialise()
{
	SetAnimation((int)Animations::BOB_IDLE_L);
	return InitializeAnimations();
}
void Player2::NoP2() 
{
	Point p(210, 184);
	SetPos(p);
	SetAnimation((int)Animations::BOB_PUSH_BUTTON);
}
void Player2::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
void Player2::InitScore()
{
	score = 0;
}
void Player2::IncrScore(int n)
{
	score += n;
}
void Player2::HitProcedure()
{
	STOP = true;
	Ikilleable = false;

	eTimeHitted += GetFrameTime();
	if (eTimeHitted >= immuneThreshold) {
		SetPos({ WINDOW_WIDTH - 46, 192 });
		STOP = false;

		wasHit = false;
		eTimeImmune = 0;
		Ikilleable = true;



	}
}
int Player2::GetScore()
{
	return score;
}
bool Player2::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Player2::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Player2::IsAscending() const
{
	return dir.y < -PLAYER_LEVITATING_SPEED;
}
bool Player2::IsLevitating() const
{
	return abs(dir.y) <= PLAYER_LEVITATING_SPEED;
}
bool Player2::IsDescending() const
{
	return dir.y > PLAYER_LEVITATING_SPEED;
}
void Player2::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
bool Player2::IsMoving() const
{
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		return true;
	}
	else {
		return false;
	}

}
void Player2::toogleWasHit()
{
	wasHit = true;
}
void Player2::Stop()
{
	dir = { 0,0 };
	state = State2::IDLE;
	isStill = true;
	if (IsLookingRight())	SetAnimation((int)Animations::BOB_IDLE_R);
	else					SetAnimation((int)Animations::BOB_IDLE_L);
}
void Player2::IncLiv()
{
	lives++;
}
void Player2::DecLiv()
{

	if (Ikilleable == true) {

		lives--;
		HitProcedure();

	}
}
int Player2::GetLives() const
{
	return lives;
}
void Player2::StartFalling()
{
	dir.y = 1;
}
void Player2::StartWalkingLeft()
{
	state = State2::WALKING;
	look = Look::LEFT;
	SetAnimation((int)Animations::BOB_WALK_L);
}
void Player2::StartWalkingRight()
{
	state = State2::WALKING;
	look = Look::RIGHT;
	SetAnimation((int)Animations::BOB_WALK_R);
}
void Player2::SetDeathAnim()
{
	SetAnimation((int)Animations::BOB_DEATH);
}
void Player2::StartJumping()
{
	dir.y = -PLAYER_JUMP_LIMIT;
	state = State2::JUMPING;
	ResourceManager::Instance().PlaySoundEffect(Resource::SFX_JUMP);
	if (IsLookingRight())	SetAnimation((int)Animations::BOB_JUMP_R);
	else					SetAnimation((int)Animations::BOB_JUMP_L);
	jump_delay = PLAYER_JUMP_DELAY;
}
void Player2::ChangeAnimRight()
{
	look = Look::RIGHT;
	switch (state)
	{
	case State2::IDLE:	 SetAnimation((int)Animations::BOB_IDLE_R);    break;
	case State2::WALKING: SetAnimation((int)Animations::BOB_WALK_R); break;
	case State2::JUMPING: SetAnimation((int)Animations::BOB_JUMP_R); break;
	case State2::FALLING: SetAnimation((int)Animations::BOB_FALL_R); break;
	}
}
void Player2::ChangeAnimLeft()
{
	look = Look::LEFT;
	switch (state)
	{
	case State2::IDLE:	 SetAnimation((int)Animations::BOB_IDLE_L);    break;
	case State2::WALKING: SetAnimation((int)Animations::BOB_WALK_L); break;
	case State2::JUMPING: SetAnimation((int)Animations::BOB_JUMP_L); break;
	case State2::FALLING: SetAnimation((int)Animations::BOB_FALL_L); break;
	}
}
void Player2::Update()
{
	//Player2 doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
	//Instead, uses an independent behaviour for each axis.
	if (STOP != true) {
		MoveX();
		MoveY();
	}

	if (state == State2::PRESS)
	{
		SetAnimation((int)Animations::BOB_PUSH_BUTTON);
	}

	LaserTag();
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
	if (inLaser) {
		LaserProcedures();
	}
	if (IsKeyPressed(KEY_F2))
	{
		if (Ikilleable == false) {
			Ikilleable = true;
		}
		else {
			Ikilleable = false;
		}
	}
	if (IsLookingRight() && IsKeyPressed(KEY_H) && !STOP)
	{

		sprite->SetAnimation((int)Animations::BOB_ATACK_R);

	}
	else if (IsLookingLeft() && IsKeyPressed(KEY_H) && !STOP)
	{
		sprite->SetAnimation((int)Animations::BOB_ATACK_L);
	}

	if (sprite->IsAnimationComplete() == true)
	{
		Stop();
	}
	if (wasHit == true)
	{
		HitProcedure();
	}
	else {
		eTimeImmune += GetFrameTime();
		if (eTimeImmune >= 1)
		{

			eTimeHitted = 0;

		}


	}

	Warp();
}

void Player2::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	int objectiveJumpX = pos.x;


	if (IsKeyDown(KEY_A))
	{
		if (state != State2::JUMPING) {
			pos.x -= 1;

		}
		initiallyLookingL = true;
		initiallyLookingR = false;

		isStill = false;
		if (state == State2::IDLE) StartWalkingLeft();
		else
		{
			if (IsLookingRight()) ChangeAnimLeft();
		}

		box = GetHitbox();
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			if (state == State2::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallRight(box)) {
			pos.x = prev_x;
			if (state == State2::WALKING) Stop();

		}

	}
	else if (IsKeyDown(KEY_D))
	{

		isStill = false;
		initiallyLookingR = true;
		initiallyLookingL = false;

		if (state != State2::JUMPING)
		{
			pos.x += 1;
		}


		if (state == State2::IDLE) StartWalkingRight();
		else
		{
			if (IsLookingLeft()) ChangeAnimRight();
		}

		box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			if (state == State2::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallLeft(box)) {
			pos.x = prev_x;
			if (state == State2::WALKING) Stop();

		}
	}
	else
	{
		if (state == State2::WALKING)
		{
			Stop();
			isStill = true;
		}
	}
}
bool Player2::IsGod()
{
	return isGod;
}
void Player2::SetState(State2 state)
{
	this->state = state;
}
void Player2::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != State2::JUMPING)
	{
		initiallyLookingR = true;
		initiallyLookingL = true;

		pos.y += PLAYER_SPEED;
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == State2::FALLING) Stop();

			if (IsKeyPressed(KEY_B))
				StartJumping();
		}
		else
		{
			if (state != State2::FALLING) StartFalling();
		}
		if (state == State2::FALLING) {
			if (look == Look::RIGHT) {
				if (map->TestCollisionWallRight(box))
				{
					pos.x += 1;
				}
				if (map->TestCollisionHalfWallRight(box))
				{
					pos.x += 1;
				}
				if (map->TestCollisionHalfWallLeft(box))
				{
					pos.x += 1;
				}
			}
			else if (look == Look::LEFT) {
				if (map->TestCollisionWallLeft(box))
				{
					pos.x -= 1;
				}
				if (map->TestCollisionHalfWallLeft(box))
				{
					pos.x -= 1;
				}
				if (map->TestCollisionHalfWallRight(box))
				{
					pos.x -= 1;
				}
			}
		}
	}
	else //state == State2::JUMPING
	{
		box = GetHitbox();
		jump_delay--;
		if (jump_delay == 0)
		{
			if (isStill == false) {
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
			}

			prev_y = pos.y;
			prev_box = GetHitbox();

			pos.y += dir.y;
			dir.y += GRAVITY_FORCE;
			jump_delay = PLAYER_JUMP_DELAY;


			//Is the jump finished?
			if (dir.y > PLAYER_JUMP_LIMIT)
			{
				dir.y = 1;
				StartFalling();
			}
			else
			{
				//Jumping is represented with 3 different states
				if (IsAscending())
				{
					if (IsLookingRight())	SetAnimation((int)Animations::BOB_JUMP_R);
					else					SetAnimation((int)Animations::BOB_JUMP_L);
					canJump = false;

				}
				else if (IsLevitating())
				{
					if (IsLookingRight())	SetAnimation((int)Animations::BOB_IDLE_R);
					else					SetAnimation((int)Animations::BOB_IDLE_L);
					canJump = true;
				}
				else if (IsDescending())
				{
					if (IsLookingRight())	SetAnimation((int)Animations::BOB_FALL_R);
					else					SetAnimation((int)Animations::BOB_FALL_L);
				}
			}
			//We check ground collision when jumping down
			if (dir.y >= 0)
			{
				box = GetHitbox();

				//A ground collision occurs if we were not in a collision state previously.
				//This prevents scenarios where, after levitating due to a previous jump, we found
				//ourselves inside a tile, and the entity would otherwise be placed above the tile,
				//crossing it.
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
void Player2::LaserTag()
{
	AABB box;

	box = GetHitbox();

	if (map->TestCollisionLaser(box, &pos.y)) {
		cFrame = 0;
		inLaser = true;
	}
}
bool Player2::TestCollisionFromUp(const AABB& box, int* py)
{
	Point p(box.pos.x, *py);
	int tile_y;

	if (pos.y < p.y && IsStompingAbove(p, box.width) /*&& pos.y +30 > p.y*/)
	{
		tile_y = (p.y + TILE_SIZE) / TILE_SIZE;

		*py -= 10;
		return true;
	}
	else {
		return false;
	}
}
bool Player2::IsStompingAbove(const Point& p, int distance)
{

	AABB playerHitbox = GetHitbox();

	int displacement = 50;
	if (p.y <= playerHitbox.pos.y + playerHitbox.height &&
		p.y >= playerHitbox.pos.y - displacement &&
		p.x + distance >= playerHitbox.pos.x &&
		p.x <= playerHitbox.pos.x + playerHitbox.width

		)
	{
		return true;
	}
	return false;

}
void Player2::SetDir(Point p)
{
	dir += p;
}
void Player2::LaserProcedures()
{
	cFrame++;
	SetAnimation((int)Animations::BUBBLE);

	while (cFrame < 1)
	{

		Stop();
	}
	cFrame = 0;
	pos = { 0, 0 };

	inLaser = false;
}
void Player2::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Player2::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);
	map->Release();
	render->Release();
}
