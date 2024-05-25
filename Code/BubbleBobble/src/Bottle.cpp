#include "Bottle.h"
#include "Sprite.h"

Bottle::Bottle(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = BottleState::ROAMING;
	map = mapp;
	current_step = 0;
	current_frames = 0;
}
Bottle::~Bottle()
{
}
AppStatus Bottle::Initialise(Look look, const AABB& area)
{
	InitializeAnimations();

	this->look = look;
	if (look == Look::LEFT)        SetAnimation((int)Animations::DRUNK_PROJECTILE);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::DRUNK_PROJECTILE);

	visibility_area = area;


	return AppStatus::OK;
}
void Bottle::BubbleSetter(BubbleFromPlayer* bub)
{
	for(BubbleFromPlayer * buble: bubbles) {
		bubbles.push_back(bub);
	}
}
EnemyType Bottle::GetEnemyType() const
{
	return EnemyType::DRUNK;
}
bool Bottle::Update(const AABB& box)
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

void Bottle::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	if (look == Look::RIGHT && state != BottleState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += BOTTLE_SPEED;
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			look = Look::LEFT;
			SetAnimation((int)Animations::DRUNK_PROJECTILE);
		}
		else if (map->TestCollisionHalfWallLeft(box)) {
			pos.x = prev_x;
			look = Look::LEFT;
			SetAnimation((int)Animations::DRUNK_PROJECTILE);


		}
		
	}
	else if (look == Look::LEFT && state != BottleState::FALLING && map->TestCollisionGround(box, &pos.y))
	{
		pos.x += -BOTTLE_SPEED;
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			look = Look::RIGHT;
			SetAnimation((int)Animations::DRUNK_PROJECTILE);
		}
		else if (map->TestCollisionHalfWallRight(box)) {
			pos.x = prev_x;
			look = Look::RIGHT;
			SetAnimation((int)Animations::DRUNK_PROJECTILE);

		}
	}
}
void Bottle::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
void Bottle::StartFalling()
{
	dir.y = 1;
}
void Bottle::Stop()
{
	dir = { 0,0 };
	state = BottleState::ROAMING;
}
void Bottle::MoveY()
{
	AABB box, prev_box;
	int prev_x = pos.x;
	int prev_y = pos.y;


	if (state != BottleState::JUMPING)
	{
		pos.y += 1;
		
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == BottleState::FALLING) Stop();
			if (IsKeyPressed(KEY_X))
				dir.y = -1;
		}
		else
		{
			if (state != BottleState::FALLING) StartFalling();
		}
		
		
	}
	
	
}

void Bottle::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::DRUNK_PROJECTILE ||
		anim == Animations::DRUNK_PROJECTILE ||
		anim == Animations::DRUNK_PROJECTILE) ? Look::LEFT : Look::RIGHT;
}
void Bottle::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + BOTTLE_SHOT_OFFSET_X_LEFT;
		*d = { -BOTTLE_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + BOTTLE_SHOT_OFFSET_X_RIGHT;
		*d = { BOTTLE_SHOT_SPEED, 0 };
	}
	p->y = pos.y + BOTTLE_SHOT_OFFSET_Y;
}