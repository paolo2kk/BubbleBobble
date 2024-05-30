#include "SuperDrunk.h"
#include "Sprite.h"

SD::SD(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, 64, 64)
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
	if (look == Look::LEFT)        SetAnimation((int)Animations::SUPER_DRUNK_WALK_L);
	else if (look == Look::RIGHT) SetAnimation((int)Animations::SUPER_DRUNK_WALK_R);

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
	StartFalling();
	Warp();
	if (SDhp <= 0)
	{
		direction = SDdir::STOP;
	}
	sprite->Update();

	return shoot;
}

void SD::MoveX()
{
	AABB box;
	int prev_x = pos.x;
	box = GetHitbox();
	switch (direction)
	{
	case SDdir::NE:
		pos.x += 1;
		pos.y -= 1;
		if (map->TestCollisionWallRight(box))
		{
			direction = SDdir::WN;
		}
		else if (pos.y < 64)
		{
			direction = SDdir::ES;
		}
		break;
	case SDdir::ES:
		pos.x += 1;
		pos.y += 1;
		if (map->TestCollisionWallRight(box))
		{
			direction = SDdir::SW;
		}
		else if (pos.y > WINDOW_HEIGHT - 24)
		{
			direction = SDdir::NE;
		}
		break;
	case SDdir::SW:
		pos.x -= 1;
		pos.y += 1;
		if (map->TestCollisionWallLeft(box))
		{
			direction = SDdir::ES;
		}
		else if (pos.y > WINDOW_HEIGHT - 24)
		{
			direction = SDdir::WN;
		}
		break;
	case SDdir::WN:
		pos.x -= 1;
		pos.y -= 1;
		if (map->TestCollisionWallLeft(box))
		{
			direction = SDdir::NE;
		}
		else if (pos.y < 64)
		{
			direction = SDdir::SW;
		}
		break;
	case SDdir::STOP:
		pos.x += 0;
		pos.y += 0;
		SetAnimation((int)Animations::SUPER_DRUNK_BUBBLE);
		direction = SDdir::INBUBBLE;
		break;
	case SDdir::INBUBBLE:
		pos.x += 0;
		pos.y += 0;
		SDInBubble = true;
		break;
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


void SD::UpdateLook(int anim_id)
{
	Animations anim = (Animations)anim_id;
	look = (anim == Animations::SUPER_DRUNK_WALK_L ||
		anim == Animations::SUPER_DRUNK_WALK_L ||
		anim == Animations::SUPER_DRUNK_WALK_L) ? Look::LEFT : Look::RIGHT;
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