#include "Slime.h"
#include "Sprite.h"

Slime::Slime(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = SlimeState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
Slime::~Slime()
{
}
AppStatus Slime::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::ZENCHAN_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::ZENCHAN_WALK_R);

	visibility_area = area;


	return AppStatus::OK;
}
void Slime::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
bool Slime::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;

	MoveX();
	MoveY();
	StartFalling();
	Warp();
	CollideWithBubble();
	sprite->Update();

	return shoot;
}
void Slime::CollideWithBubble()
{
	AABB box = GetHitbox();
	AABB bubbleBox;
	for (BubbleFromPlayer* buble : bubbles) 
	{
		bubbleBox = buble->GetHitbox();
		bool hit = box.TestAABB(bubbleBox);

		if (hit)
		{
			pos.x = 100;
		}
	}	
	
	
}
void Slime::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (look == Look::RIGHT && state != SlimeState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += SLIME_SPEED;
		if (map->TestCollisionWallRight(box))
		{
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
	else if (look == Look::LEFT && state != SlimeState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += -SLIME_SPEED;
		if (map->TestCollisionWallLeft(box))
		{
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
void Slime::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Slime::StartFalling()
{
	dir.y = 1;
}
void Slime::Stop()
{
	dir = { 0,0 };
	state = SlimeState::ROAMING;
}
void Slime::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != SlimeState::JUMPING)
	{
		pos.y += 1;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == SlimeState::FALLING) Stop();
			if (IsKeyPressed(KEY_X))
				dir.y = -1;
		}
		else
		{
			if (state != SlimeState::FALLING) StartFalling();
		}
		
		
	}
	
	
}

void Slime::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::ZENCHAN_WALK_L ||
		anim == Animations::ZENCHAN_WALK_L ||
		anim == Animations::ZENCHAN_WALK_L) ? Look::LEFT : Look::RIGHT;
}
void Slime::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + SLIME_SHOT_OFFSET_X_LEFT;
		*d = { -SLIME_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + SLIME_SHOT_OFFSET_X_RIGHT;
		*d = { SLIME_SHOT_SPEED, 0 };
	}
	p->y = pos.y + SLIME_SHOT_OFFSET_Y;
}