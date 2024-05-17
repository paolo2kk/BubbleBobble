#include "BubbleFromPlayer.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

BubbleFromPlayer::BubbleFromPlayer(const Point& p, Directions d) : Entity(p, BUBBLE_PHYSICAL_SIZE, BUBBLE_PHYSICAL_SIZE, BUBBLE_FRAME_SIZE, BUBBLE_FRAME_SIZE)
{
	dire = d;
	speed = .3;
	stages = 1;
	logPosXL = pos.x - SHOOT_RANGE;
	logPosXR = pos.x + SHOOT_RANGE;
	eTime = 0;
	spawnTime = 0;
	player = nullptr;
	lifeTime = GetRandomValue(3, 5);
	Rectangle rc;
	inShoot = true;
	eTimePogo = 0;
	canCollide = true;
	issAlive = true;
	ResourceManager::Instance().PlaySoundEffect(Resource::SFX_BUBBLE);
}
BubbleFromPlayer::~BubbleFromPlayer()
{
}
void BubbleFromPlayer::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
AppStatus BubbleFromPlayer::Initialise()
{
	InitializeAnimations();

	SetAnimation((int)Animations::SPAWN_BUBBLE_GREEN_L);
	return AppStatus::OK;

}
void BubbleFromPlayer::Update()
{
	pos += dir;
	Movement(dire);
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();

	if (inCatch) EnemyCatch();
}
bool BubbleFromPlayer::isAlive()
{
	if (!inCatch)
	{
		eTime += GetFrameTime();
		if (eTime >= lifeTime)
		{
			return false;
		}
		else {
			return true;
		}
	}
	
}
void BubbleFromPlayer::ClampPos()
{
	
	if (pos.y < 32)
	{
		if (pos.x <= WINDOW_WIDTH / 2)
		{
			dir = {1, 1};
		}
		else {
			dir = { -1, 1 };
		}
	}
	if (pos.y == 32)
	{
		if (pos.x <= GetRandomValue(110, WINDOW_WIDTH / 2))
		{
			dir = {1, 0};
		}
		else if (pos.x > GetRandomValue(WINDOW_WIDTH / 2, 140))
		{
			dir = { -1, 0 };
		}
	}
	
}
void BubbleFromPlayer::SetPlayer(Player* p)
{
	player = p;
}
void BubbleFromPlayer::Stomp()
{
	if (!inShoot)
	{
		AABB box = GetHitbox();
		if (player != nullptr && IsKeyDown(KEY_X))
		{
			if (eTimePogo > 1)
			{
				if (player->TestCollisionFromUp(box, &pos.y))
				{
					player->SetPos(player->GetPos() += { 0, POGOJUMP });
					eTimePogo = 0;
				}
			}
		}
	}
	eTimePogo += GetFrameTime();
}
Point BubbleFromPlayer::GetPos() const
{
	return pos;
}
void BubbleFromPlayer::EnemyCatch()
{
	switch (bubbleStages)
	{
	case (int)BubbleStages::GREENSTAGE:
		SetAnimation((int)Animations::ZENCHAN_BUBBLE_GREEN);
		bubbleStages++;
		break;
	case (int)BubbleStages::GREENSTAGE_:
		if (eTimeCatch > eTimeCatchGreen) bubbleStages++;
		eTimeCatch += GetFrameTime();
		break;
	case (int)BubbleStages::YELLOWSTAGE:
		eTimeCatch = 0;
		SetAnimation((int)Animations::ZENCHAN_BUBBLE_YELLOW);
		bubbleStages++;
		break;
	case (int)BubbleStages::YELLOWSTAGE_:
		if (eTimeCatch > eTimeCatchYellow) bubbleStages++;
		eTimeCatch += GetFrameTime();
		break;
	case (int)BubbleStages::REDSTAGE:
		eTimeCatch = 0;
		SetAnimation((int)Animations::ZENCHAN_BUBBLE_RED);
		bubbleStages++;
		break;
	case (int)BubbleStages::REDSTAGE_:
		if (eTimeCatch > eTimeCatchRed) bubbleStages++;
		eTimeCatch += GetFrameTime();
		break;
	case(int)BubbleStages::ENDED:
		hasEndedFromCatch = true;
		break;
	}
}

void BubbleFromPlayer::Movement(Directions d)
{
	ClampPos();
	Stomp();
	if (pos.y > 32)
	{
		if (d == Directions::LEFT)
		{
			switch (stages) {
				SetAnimation((int)Animations::SPAWN_BUBBLE_GREEN_L);
			case 1:
				if (pos.x < 20)
				{
					pos.x++;
					stages++;
				}
				inShoot = true;

				dir = { -2, 0 };
				if (pos.x <= logPosXL) {
					stages++;
				}
				break;
			case 2:
				if(!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);
				canCollide = false;

				inShoot = false;
				dir = { 0, -1 };
				break;


			}
		}
		else if (d == Directions::RIGHT)
		{

			switch (stages) {
				SetAnimation((int)Animations::SPAWN_BUBBLE_GREEN_R);
			case 1:
				if (pos.x > 226)
				{
					pos.x--;
					stages++;
				}
				inShoot = true;

				dir = { 2, 0 };
				if (pos.x >= logPosXR) {
					stages++;
				}
				break;
			case 2:
				if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);
				canCollide = false;

				inShoot = false;
				dir = { 0, -1 };

				break;

			}

		}
	}
	
}
void BubbleFromPlayer::HandleCollisionLogic()
{
	AABB box, player_hitbox;

}

void BubbleFromPlayer::DrawDebug(const Color & col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
void BubbleFromPlayer::Release()
{

	render->Release();
}
