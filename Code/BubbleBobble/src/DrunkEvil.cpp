#include "DrunkEvil.h"
#include "Sprite.h"

DDRUNK::DDRUNK(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = DDRUNKState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
DDRUNK::~DDRUNK()
{
}
AppStatus DDRUNK::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::DRUNK_ANGRY_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::DRUNK_ANGRY_WALK_R);

	visibility_area = area;


	return AppStatus::OK;
}
void DDRUNK::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
EnemyType DDRUNK::GetEnemyType() const
{
	return EnemyType::DRUNK;
}
bool DDRUNK::Update(const AABB& box)
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

void DDRUNK::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (!defuseHitbox)
	{
		if (look == Look::RIGHT && state != DDRUNKState::FALLING && map->TestCollisionGround(box, &pos.y) && !defuseHitbox)
		{
			pos.x += DDRUNK_SPEED + 1;


			if (map->TestCollisionWallRight(box))
			{
				pos.x = prev_x;
				look = Look::LEFT;

				SetAnimation((int)Animations::DRUNK_ANGRY_WALK_L);
			}
			else if (map->TestCollisionHalfWallLeft(box)) {
				pos.x = prev_x;
				look = Look::LEFT;
				SetAnimation((int)Animations::DRUNK_WALK_R);


			}

		}


		else if (look == Look::LEFT && state != DDRUNKState::FALLING && map->TestCollisionGround(box, &pos.y) && !defuseHitbox)
		{
			pos.x += -DDRUNK_SPEED - 1;

			if (map->TestCollisionWallLeft(box))
			{
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::DRUNK_ANGRY_WALK_R);
			}
			else if (map->TestCollisionHalfWallRight(box)) {
				pos.x = prev_x;
				look = Look::RIGHT;
				SetAnimation((int)Animations::DRUNK_ANGRY_WALK_R);

			}
		}
	}
	

	if (lerping && !hasAlreadyJumped) {
		eTimeLerp += GetFrameTime();
		if (eTimeLerp < .1) {
			pos.y -= 1;
			defuseHitbox = true;
		}

		else if (eTimeLerp > .8) {
			hasAlreadyJumped = true;
			defuseHitbox = false;
			lerping = false;
			eTimeLerp = 0;
			jumpCooldownTimer = jumpCooldownDuration;
		}
	}
}


void DDRUNK::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void DDRUNK::StartFalling()
{
	dir.y = 1;
}
void DDRUNK::Stop()
{
	dir = { 0,0 };
	state = DDRUNKState::ROAMING;
}
void DDRUNK::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;

	if (lerping == true)
	{
		pos.y -= 1;
		defuseHitbox = true;
	}
	else {
		defuseHitbox = false;

	}
	if (pos.y < 40)
	{
		pos.y = 40;
	}
	if (state != DDRUNKState::JUMPING && !defuseHitbox)
	{
	
		pos.y += 2;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == DDRUNKState::FALLING) Stop();
			/*if (IsKeyDown(KEY_X))
				dir.y = -1;*/
		}
		else
		{
			if (state != DDRUNKState::FALLING) StartFalling();
		}
		
	}
	
	

	
}

void DDRUNK::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::DRUNK_ANGRY_WALK_L ||
		anim == Animations::DRUNK_ANGRY_WALK_L ||
		anim == Animations::DRUNK_ANGRY_WALK_L) ? Look::LEFT : Look::RIGHT;
}
void DDRUNK::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + DDRUNK_SHOT_OFFSET_X_LEFT;
		*d = { -DDRUNK_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + DDRUNK_SHOT_OFFSET_X_RIGHT;
		*d = { DDRUNK_SHOT_SPEED, 0 };
	}
	p->y = pos.y + DDRUNK_SHOT_OFFSET_Y;
}