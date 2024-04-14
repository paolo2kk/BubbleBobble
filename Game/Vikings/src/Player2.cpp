#include "Player.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Bubble::Bubble(const Point& p, State s, Look view) :
	Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE, PLAYER_FRAME_SIZE)
{
	state = s;
	look = view;
	jump_delay = PLAYER_JUMP_DELAY;
	map = nullptr;
	score = 0;
	bubble = nullptr;
}
Bubble::~Bubble()
{
}
AppStatus Bubble::Initialise()
{
	int i;
	const int n = PLAYER_FRAME_SIZE;
	const int p = PADDING_X;
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_PLAYER, "images/Bub.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_PLAYER));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE_RIGHT, 30);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE_RIGHT, { 0, 0, -n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE_RIGHT, { 2 * (n + PADDING_X), 0, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::IDLE_LEFT, 30);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE_LEFT, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE_LEFT, { 2 * (n + PADDING_X), 0, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 5; ++i)
		sprite->AddKeyFrame((int)BubbleAnim::WALKING_RIGHT, { (float)i * (n + PADDING_X), (float)0, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 5; ++i)
		sprite->AddKeyFrame((int)BubbleAnim::WALKING_LEFT, { (float)i * (n + PADDING_X), (float)0, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::FALLING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::FALLING_RIGHT, { 8 * (n + PADDING_X), PADDING_Y + n, -n, n });
	sprite->AddKeyFrame((int)BubbleAnim::FALLING_RIGHT, { 9 * (n + PADDING_X),  PADDING_Y + n, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::FALLING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::FALLING_LEFT, { 8 * (n + PADDING_X),  PADDING_Y + n, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::FALLING_LEFT, { 9 * (n + PADDING_X), PADDING_Y + n, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::JUMPING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::JUMPING_RIGHT, { 10 * (n + PADDING_X),  PADDING_Y + n, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::JUMPING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::JUMPING_LEFT, { 10 * (n + PADDING_X),  PADDING_Y + n, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::LEVITATING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::LEVITATING_RIGHT, { 11 * (n + PADDING_X),  PADDING_Y + n, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::LEVITATING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::LEVITATING_LEFT, { 11 * (n + PADDING_X), PADDING_Y + n, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::SHOOT_BUBBLE, ANIM_DELAY);
	for (i = 7; i < 10; ++i)
		sprite->AddKeyFrame((int)BubbleAnim::SHOOT_BUBBLE, { (float)i * (n + PADDING_X), 0, n, n });

	sprite->SetAnimation((int)BubbleAnim::IDLE_RIGHT);


	return AppStatus::OK;
}
void Bubble::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
void Bubble::InitScore()
{
	score = 0;
}
void Bubble::IncrScore(int n)
{
	score += n;
}
int Bubble::GetScore()
{
	return score;
}
bool Bubble::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Bubble::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Bubble::IsAscending() const
{
	return dir.y < -PLAYER_LEVITATING_SPEED;
}
bool Bubble::IsLevitating() const
{
	return abs(dir.y) <= PLAYER_LEVITATING_SPEED;
}
bool Bubble::IsDescending() const
{
	return dir.y > PLAYER_LEVITATING_SPEED;
}
void Bubble::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Bubble::Stop()
{
	dir = { 0,0 };
	state = State::IDLE;
	isStill = true;
	if (IsLookingRight())	SetAnimation((int)BubbleAnim::IDLE_RIGHT);
	else					SetAnimation((int)BubbleAnim::IDLE_LEFT);
}

void Bubble::StartWalkingLeft()
{
	state = State::WALKING;
	look = Look::LEFT;
	SetAnimation((int)BubbleAnim::WALKING_LEFT);
}
void Bubble::StartWalkingRight()
{
	state = State::WALKING;
	look = Look::RIGHT;
	SetAnimation((int)BubbleAnim::WALKING_RIGHT);
}
void Bubble::StartFalling()
{
	dir.y = PLAYER_SPEED + 1;
	state = State::FALLING;
	if (IsLookingRight())	SetAnimation((int)BubbleAnim::FALLING_RIGHT);
	else					SetAnimation((int)BubbleAnim::FALLING_LEFT);
}
void Bubble::StartJumping()
{
	dir.y = -PLAYER_JUMP_LIMIT;
	state = State::JUMPING;
	if (IsLookingRight())	SetAnimation((int)BubbleAnim::JUMPING_RIGHT);
	else					SetAnimation((int)BubbleAnim::JUMPING_LEFT);
	jump_delay = PLAYER_JUMP_DELAY;
}
void Bubble::ChangeAnimRight()
{
	look = Look::RIGHT;
	switch (state)
	{
		case State::IDLE:	 SetAnimation((int)BubbleAnim::IDLE_RIGHT);    break; 
		case State::WALKING: SetAnimation((int)BubbleAnim::WALKING_RIGHT); break;
		case State::JUMPING: SetAnimation((int)BubbleAnim::JUMPING_RIGHT); break;
		case State::FALLING: SetAnimation((int)BubbleAnim::FALLING_RIGHT); break;
	}
}
void Bubble::ChangeAnimLeft()
{
	look = Look::LEFT;
	switch (state)
	{
		case State::IDLE:	 SetAnimation((int)BubbleAnim::IDLE_LEFT);    break;
		case State::WALKING: SetAnimation((int)BubbleAnim::WALKING_LEFT); break;
		case State::JUMPING: SetAnimation((int)BubbleAnim::JUMPING_LEFT); break;
		case State::FALLING: SetAnimation((int)BubbleAnim::FALLING_LEFT); break;
	}
}
void Bubble::Update()
{
	//Bubble doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
	//Instead, uses an independent behaviour for each axis.
	MoveX();
	MoveY();
	LaserTag();
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
	if (inLaser) {
		LaserProcedures();
	}
	
	CreatingBubble();
	Warp();
}

void Bubble::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	int objectiveJumpX = pos.x;

	
	if (IsKeyDown(KEY_LEFT) && initiallyLookingL)
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
	else if (IsKeyDown(KEY_RIGHT) && initiallyLookingR)
	{
		
		isStill = false;
		initiallyLookingR = true;
		initiallyLookingL = false;

		if (state != State::JUMPING) {
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
		if (state == State::WALKING) {
			Stop();
			isStill = true;
		}
	}
}
void Bubble::CreatingBubble() 
{

	if (IsKeyDown(KEY_S)) {
		
		SetAnimation((int)BubbleAnim::SHOOT_BUBBLE);
		bubble = new Bubble(pos, States::ALIVE, Looks::RIGHT);
	}
}

void Bubble::MoveY()
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

			if (IsKeyPressed(KEY_X))
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
			else if (look == Look::LEFT) {
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
				dir.y = PLAYER_SPEED;
				StartFalling();
			}
			else
			{
				//Jumping is represented with 3 different states
				if (IsAscending())
				{
					if (IsLookingRight())	SetAnimation((int)BubbleAnim::JUMPING_RIGHT);
					else					SetAnimation((int)BubbleAnim::JUMPING_LEFT);

					
				}
				else if (IsLevitating())
				{
					if (IsLookingRight())	SetAnimation((int)BubbleAnim::LEVITATING_RIGHT);
					else					SetAnimation((int)BubbleAnim::LEVITATING_LEFT);
				}
				else if (IsDescending())
				{
					if (IsLookingRight())	SetAnimation((int)BubbleAnim::FALLING_RIGHT);
					else					SetAnimation((int)BubbleAnim::FALLING_LEFT);
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
void Bubble::LaserTag()
{
	AABB box;

	box = GetHitbox();

	if (map->TestCollisionLaser(box,&pos.y )) {
		cFrame = 0;
		inLaser = true;
	}

}

void Bubble::LaserProcedures() 
{
	cFrame++;
	SetAnimation((int)BubbleAnim::SHOCK_LEFT);

	while (cFrame < 1) 
	{

		Stop();
	}
	cFrame = 0;
	pos = { 0, 0 };

	inLaser = false;
}
void Bubble::DrawDebug(const Color& col) const
{	
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	
	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18*16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Bubble::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);

	render->Release();
}