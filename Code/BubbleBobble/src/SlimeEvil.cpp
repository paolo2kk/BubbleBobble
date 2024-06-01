#include "SlimeEvil.h"
#include "Sprite.h"

DSLIME::DSLIME(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = DSLIMEState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
DSLIME::~DSLIME()
{
}
AppStatus DSLIME::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_R);

	visibility_area = area;
	noSpawnMore = false;


	return AppStatus::OK;
}
void DSLIME::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
bool DSLIME::Update(const AABB& box)
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

void DSLIME::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (!defusehitbox) {
		if (look == Look::RIGHT && state != DSLIMEState::FALLING && map->TestCollisionGround(box, &pos.y)) {
			pos.x += DSLIME_SPEED + 1;

			if (map->TestCollisionWallRight(box)) {
				pos.x = prev_x;
				look = Look::LEFT;
				SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_L);
			}
			else if (map->TestCollisionHalfWallLeft(box)) {
				pos.x = prev_x;
				look = Look::LEFT;
				SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_R);
			}

		}
		else if (look == Look::LEFT && state != DSLIMEState::FALLING && map->TestCollisionGround(box, &pos.y)) {
			pos.x += -DSLIME_SPEED - 1;

			if (map->TestCollisionWallLeft(box)) {
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_R);
			}
			else if (map->TestCollisionHalfWallRight(box)) {
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::ZENCHAN_ANGRY_WALK_R);
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

EnemyType DSLIME::GetEnemyType() const
{
	return EnemyType::SLIME;
}
void DSLIME::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void DSLIME::StartFalling()
{
	dir.y = 1;
}	
void DSLIME::Stop()
{
	dir = { 0,0 };
	state = DSLIMEState::ROAMING;
}
void DSLIME::MoveY()
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
	if (state != DSLIMEState::JUMPING && !defusehitbox)
	{
		pos.y += 2;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == DSLIMEState::FALLING) Stop();
			if (IsKeyPressed(KEY_X))
				dir.y = -1;
		}
		else
		{
			if (state != DSLIMEState::FALLING) StartFalling();
		}
		
		
	}
	
	
}

void DSLIME::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::ZENCHAN_ANGRY_WALK_L ||
		anim == Animations::ZENCHAN_ANGRY_WALK_L ||
		anim == Animations::ZENCHAN_ANGRY_WALK_L) ? Look::LEFT : Look::RIGHT;
}
void DSLIME::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + DSLIME_SHOT_OFFSET_X_LEFT;
		*d = { -DSLIME_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + DSLIME_SHOT_OFFSET_X_RIGHT;
		*d = { DSLIME_SHOT_SPEED, 0 };
	}
	p->y = pos.y + DSLIME_SHOT_OFFSET_Y;
}