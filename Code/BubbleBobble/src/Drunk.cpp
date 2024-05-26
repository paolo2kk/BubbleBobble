#include "Drunk.h"
#include "Sprite.h"

Drunk::Drunk(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = DrunkState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
Drunk::~Drunk()
{
}
AppStatus Drunk::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::DRUNK_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::DRUNK_WALK_R);

	visibility_area = area;


	return AppStatus::OK;
}
void Drunk::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
EnemyType Drunk::GetEnemyType() const
{
	return EnemyType::DRUNK;
}
bool Drunk::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;

	MoveX();
	MoveY();
	StartFalling();
	Warp();
	sprite->Update();

	return shoot;
}

void Drunk::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (look == Look::RIGHT && state != DrunkState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += DRUNK_SPEED;

		
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			look = Look::LEFT;
			
			SetAnimation((int)Animations::DRUNK_WALK_L);
		}
		else if (map->TestCollisionHalfWallLeft(box)) {
			pos.x = prev_x;
			look = Look::LEFT;
			SetAnimation((int)Animations::DRUNK_WALK_R);


		}
		
	}
	if (lerping)
	{
		eTimeLerp += GetFrameTime();
		if (eTimeLerp <= 1.5f)
		{
			state = DrunkState::ROAMING;
		}
		else if (eTimeLerp > 1.5f && eTimeLerp < 3.0f)
		{
			state = DrunkState::JUMPING;
		}
		else if (eTimeLerp > 3.0f)
		{
			eTimeLerp = 0;
			lerping = false;
		}


	}
	
	else if (look == Look::LEFT && state != DrunkState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += -DRUNK_SPEED;

		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			look = Look::RIGHT;
			SetAnimation((int)Animations::DRUNK_WALK_R);
		}
		else if (map->TestCollisionHalfWallRight(box)) {
			pos.x = prev_x;
			look = Look::RIGHT;
			SetAnimation((int)Animations::DRUNK_WALK_R);

		}
	}
}


void Drunk::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Drunk::StartFalling()
{
	dir.y = 1;
}
void Drunk::Stop()
{
	dir = { 0,0 };
	state = DrunkState::ROAMING;
}
void Drunk::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != DrunkState::JUMPING)
	{
		pos.y += 1;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == DrunkState::FALLING) Stop();
			/*if (IsKeyDown(KEY_X))
				dir.y = -1;*/
		}
		else
		{
			if (state != DrunkState::FALLING) StartFalling();
		}
		
	}
	else if (state == DrunkState::JUMPING)
	{
		pos.y -= 1;
	}
	
	
}

void Drunk::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::DRUNK_WALK_L ||
		anim == Animations::DRUNK_WALK_L ||
		anim == Animations::DRUNK_WALK_L) ? Look::LEFT : Look::RIGHT;
}
void Drunk::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + DRUNK_SHOT_OFFSET_X_LEFT;
		*d = { -DRUNK_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + DRUNK_SHOT_OFFSET_X_RIGHT;
		*d = { DRUNK_SHOT_SPEED, 0 };
	}
	p->y = pos.y + DRUNK_SHOT_OFFSET_Y;
}