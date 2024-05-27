#include "Player.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include "BubbleFromPlayer.h"
#include <raymath.h>


Player::Player(const Point& p, State s, Look view) :
	Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE, PLAYER_FRAME_SIZE)
{
	state = s;
	look = view;
	jump_delay = PLAYER_JUMP_DELAY;
	map = nullptr;
	score = 0;
}
Player::~Player()
{
}
AppStatus Player::Initialise()
{
	state = State::IDLE;
	SetAnimation((int)Animations::BUB_IDLE_R);
	return InitializeAnimations();
}
void Player::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
void Player::NoP1()
{
	Point p(35, 184);
	SetPos(p);
	SetAnimation((int)Animations::BUB_PUSH_BUTTON);
}
void Player::InitScore()
{
	score = 0;
}
void Player::IncrScore(int n)
{
	score += n;
}
void Player::HitProcedure()
{
	STOP = true;
	isGod = true;
	Ikilleable = false;

	eTimeHitted += GetFrameTime();
	if (eTimeHitted >= immuneThreshold) {
		SetPos({32, 192});
		isGod = false;
		wasHit = false;
		eTimeHitted = 0;
		STOP = false;

		Ikilleable = true;
	}
}
int Player::GetScore()
{
	return score;
}
bool Player::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Player::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Player::IsAscending() const
{
	return dir.y < -PLAYER_LEVITATING_SPEED;
}
bool Player::IsLevitating() const
{
	return abs(dir.y) <= PLAYER_LEVITATING_SPEED;
}
bool Player::IsDescending() const
{
	return dir.y > PLAYER_LEVITATING_SPEED;
}
void Player::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
bool Player::IsMoving() const
{
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))
	{
		return true;
	}
	else {
		return false;
	}
	
}
void Player::toogleWasHit()
{
	wasHit = true;
}
void Player::Stop()
{
	dir = { 0,0 };
	state = State::IDLE;
	isStill = true;
	if (IsLookingRight())	SetAnimation((int)Animations::BUB_IDLE_R);
	else					SetAnimation((int)Animations::BUB_IDLE_L);
}
void Player::IncLiv()
{
	lives++;
}
void Player::DecLiv()
{

	if (isGod == false) {

		lives--;
		HitProcedure();

	}
}
int Player::GetLives() const
{
	return lives;
}
void Player::StartFalling()
{
	dir.y = 1;
}
void Player::StartWalkingLeft()
{
	state = State::WALKING;
	look = Look::LEFT;
	SetAnimation((int)Animations::BUB_WALK_L);
}
void Player::StartWalkingRight()
{
	state = State::WALKING;
	look = Look::RIGHT;
	SetAnimation((int)Animations::BUB_WALK_R);
}
void Player::SetDeathAnim()
{
	SetAnimation((int)Animations::BUB_DEATH);
}
void Player::StartJumping()
{
	dir.y = -PLAYER_JUMP_LIMIT;
	state = State::JUMPING;
	ResourceManager::Instance().PlaySoundEffect(Resource::SFX_JUMP);
	if (IsLookingRight())	SetAnimation((int)Animations::BUB_JUMP_R);
	else					SetAnimation((int)Animations::BUB_JUMP_L);
	jump_delay = PLAYER_JUMP_DELAY;
}
void Player::ChangeAnimRight()
{
	look = Look::RIGHT;
	switch (state)
	{
		case State::IDLE:	 SetAnimation((int)Animations::BUB_IDLE_R);    break;
		case State::WALKING: SetAnimation((int)Animations::BUB_WALK_R); break;
		case State::JUMPING: SetAnimation((int)Animations::BUB_JUMP_R); break;
		case State::FALLING: SetAnimation((int)Animations::BUB_FALL_R); break;
	}
}
void Player::ChangeAnimLeft()
{
	look = Look::LEFT;
	switch (state)
	{
		case State::IDLE:	 SetAnimation((int)Animations::BUB_IDLE_L);    break;
		case State::WALKING: SetAnimation((int)Animations::BUB_WALK_L); break;
		case State::JUMPING: SetAnimation((int)Animations::BUB_JUMP_L); break;
		case State::FALLING: SetAnimation((int)Animations::BUB_FALL_L); break;
	}
}
void Player::Update()
{
	//Player doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
	//Instead, uses an independent behaviour for each axis.
	if (STOP != true) {
		MoveX();
		MoveY();
	}
	
	LaserTag();
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
	if (inLaser) {
		LaserProcedures();
	}
	if (IsKeyPressed(KEY_F2))
	{
		if (isGod == false) {
			isGod = true;
		}
		else {
			isGod = false;
		}
	}
	if (IsLookingRight() && IsKeyPressed(KEY_L) && !STOP)
	{

		sprite->SetAnimation((int)Animations::BUB_ATACK_R);

	}
	else if (IsLookingLeft() && IsKeyPressed(KEY_L) && !STOP)
	{
		sprite->SetAnimation((int)Animations::BUB_ATACK_L);
	}

	if (sprite->IsAnimationComplete() == true)
	{
		Stop();
	}
	if (wasHit == true)
	{
		HitProcedure();
	}

	Warp();
}

void Player::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	int objectiveJumpX = pos.x;

	
	if (IsKeyDown(KEY_LEFT))
	{
		if (state != State::JUMPING) {
			pos.x -= 1;

		}
		initiallyLookingL = true;
		initiallyLookingR = false;

		isStill = false;
		if (state == State::IDLE) StartWalkingLeft();
		else
		{
			if (IsLookingRight()) ChangeAnimLeft();
		}

		box = GetHitbox();
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallRight(box)) {
			pos.x = prev_x ;
			if (state == State::WALKING) Stop();

		}
		
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		
		isStill = false;
		initiallyLookingR = true;
		initiallyLookingL = false;

		if (state != State::JUMPING) 
		{
			pos.x += 1;
		}
		
	
		if (state == State::IDLE) StartWalkingRight();
		else
		{
			if (IsLookingLeft()) ChangeAnimRight();
		}

		box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
		else if (map->TestCollisionHalfWallLeft(box)) {
			pos.x = prev_x ;
			if (state == State::WALKING) Stop();

		}
	}
	else
	{
		if (state == State::WALKING) 
		{
			Stop();
			isStill = true;
		}
	}
}
bool Player::IsGod()
{
	return isGod;
}
void Player::SetState(State state)
{
	this->state = state;
}
void Player::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != State::JUMPING)
	{
		initiallyLookingR = true;
		initiallyLookingL = true;

		pos.y += PLAYER_SPEED;
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == State::FALLING) Stop();

			if (IsKeyPressed(KEY_PERIOD))
				StartJumping();
		}
		else
		{
			if (state != State::FALLING) StartFalling();
		}
		if (state == State::FALLING) {
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
	else //state == State::JUMPING
	{
		box = GetHitbox();
		jump_delay--;
		if (jump_delay == 0)
		{
			if (isStill == false) {
				if (look == Look::RIGHT ) {
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
					if (IsLookingRight())	SetAnimation((int)Animations::BUB_JUMP_R);
					else					SetAnimation((int)Animations::BUB_JUMP_L);
					canJump = false;
					
				}
				else if (IsLevitating())
				{
					if (IsLookingRight())	SetAnimation((int)Animations::BUB_IDLE_R);
					else					SetAnimation((int)Animations::BUB_IDLE_L);
					canJump = true;
				}
				else if (IsDescending())
				{
					if (IsLookingRight())	SetAnimation((int)Animations::BUB_FALL_R);
					else					SetAnimation((int)Animations::BUB_FALL_L);
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
void Player::LaserTag()
{
	AABB box;

	box = GetHitbox();

	if (map->TestCollisionLaser(box,&pos.y )) {
		cFrame = 0;
		inLaser = true;
	}
}
bool Player::TestCollisionFromUp(const AABB& box, int* py) 
{
	Point p(box.pos.x, *py);	
	int tile_y;
	
	if (pos.y < p.y && IsStompingAbove(p, box.width) /*&& pos.y +30 > p.y*/)
	{
		tile_y = (p.y +TILE_SIZE )/ TILE_SIZE;

		*py -= 10;
		return true;
	}
	else {
		return false;
	}
}
bool Player::IsStompingAbove(const Point& p, int distance)
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
void Player::SetDir(Point p)
{
	dir += p;
}
void Player::LaserProcedures() 
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
void Player::DrawDebug(const Color& col) const
{	
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	
	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18*16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Player::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);
	map->Release();
	render->Release();
}
