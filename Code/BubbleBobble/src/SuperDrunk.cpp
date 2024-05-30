#include "SuperDrunk.h"
#include "Sprite.h"

SD::SD(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = SDState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
SD::~SD()
{
}
AppStatus SD::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::ZENCHAN_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::ZENCHAN_WALK_R);

	visibility_area = area;
	noSpawnMore = false;


	return AppStatus::OK;
}
void SD::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
bool SD::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;
	if (jumpCooldownTimer > 0) {
		jumpCooldownTimer -= GetFrameTime();
		hasAlreadyJumped = true;
	}
	else {
		hasAlreadyJumped = false;
	}
	
	MoveX();
	MoveY();
	StartFalling();
	Warp();
	sprite->Update();

	return shoot;
}

void SD::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (!defusehitbox) {
		if (look == Look::RIGHT && state != SDState::FALLING && map->TestCollisionGround(box, &pos.y)) {
			pos.x += SD_SPEED;

			if (map->TestCollisionWallRight(box)) {
				pos.x = prev_x;
				look = Look::LEFT;
				SetAnimation((int)Animations::ZENCHAN_WALK_L);
			}
			else if (map->TestCollisionHalfWallLeft(box)) {
				pos.x = prev_x;
				look = Look::LEFT;
				SetAnimation((int)Animations::ZENCHAN_WALK_R);
			}

		}
		else if (look == Look::LEFT && state != SDState::FALLING && map->TestCollisionGround(box, &pos.y)) {
			pos.x += -SD_SPEED;

			if (map->TestCollisionWallLeft(box)) {
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::ZENCHAN_WALK_R);
			}
			else if (map->TestCollisionHalfWallRight(box)) {
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::ZENCHAN_WALK_R);
			}
		}
	}

	if (lerping && !hasAlreadyJumped) {
		eTimeLerp += GetFrameTime();
		if (eTimeLerp < .1) {
			pos.y -= 1;
			defusehitbox = true;
		}
		
		else if (eTimeLerp > .8) {
			hasAlreadyJumped = true;
			defusehitbox = false;
			lerping = false;
			eTimeLerp = 0;
			jumpCooldownTimer = jumpCooldownDuration; 
		}
	}
}


void SD::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void SD::StartFalling()
{
	dir.y = 1;
}
void SD::Stop()
{
	dir = { 0,0 };
	state = SDState::ROAMING;
}
void SD::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;

	if (lerping == true)
	{
		pos.y -= 1;
		defusehitbox = true;
	}
	else {
		defusehitbox = false;

	}
	if (state != SDState::JUMPING && !defusehitbox)
	{
		pos.y += 1;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == SDState::FALLING) Stop();
			if (IsKeyPressed(KEY_X))
				dir.y = -1;
		}
		else
		{
			if (state != SDState::FALLING) StartFalling();
		}
		
		
	}
	
	
}

void SD::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::ZENCHAN_WALK_L ||
		anim == Animations::ZENCHAN_WALK_L ||
		anim == Animations::ZENCHAN_WALK_L) ? Look::LEFT : Look::RIGHT;
}
void SD::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + SD_SHOT_OFFSET_X_LEFT;
		*d = { -SD_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + SD_SHOT_OFFSET_X_RIGHT;
		*d = { SD_SHOT_SPEED, 0 };
	}
	p->y = pos.y + SD_SHOT_OFFSET_Y;
}