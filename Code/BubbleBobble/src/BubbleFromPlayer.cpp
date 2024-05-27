#include "BubbleFromPlayer.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>
#include "Object.h"


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
	poped = false;
	framecounter = 0;
	fruit = false;
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
;
	if (poped == false)
	{
		Movement(dire);
		pos += dir;
	}
	else
	{
		dire = BublePop(dire);
	}
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
	HandleCollisionLogic();
	if (inCatch) {
		switch (enemytype)
		{
		case 0:
			EnemyCatchSlime();
			break;
		case 1:
			EnemyCatchDrunk();
			break;
		}
	}
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
void BubbleFromPlayer::SetPlayer2(Player2* p)
{
	player2 = p;
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
void BubbleFromPlayer::EnemyCatchSlime()
{
	if (poped == false)
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
}
void BubbleFromPlayer::EnemyCatchDrunk()
{
	if (poped == false)
	{
		switch (bubbleStages)
		{
		case (int)BubbleStages::GREENSTAGE:
			SetAnimation((int)Animations::DRUNK_BUBBLE_GREEN);
			bubbleStages++;
			break;
		case (int)BubbleStages::GREENSTAGE_:
			if (eTimeCatch > eTimeCatchGreen) bubbleStages++;
			eTimeCatch += GetFrameTime();
			break;
		case (int)BubbleStages::YELLOWSTAGE:
			eTimeCatch = 0;
			SetAnimation((int)Animations::DRUNK_BUBBLE_YELLOW);
			bubbleStages++;
			break;
		case (int)BubbleStages::YELLOWSTAGE_:
			if (eTimeCatch > eTimeCatchYellow) bubbleStages++;
			eTimeCatch += GetFrameTime();
			break;
		case (int)BubbleStages::REDSTAGE:
			eTimeCatch = 0;
			SetAnimation((int)Animations::DRUNK_BUBBLE_RED);
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
}
void BubbleFromPlayer::SetTileMap(TileMap* m) 
{
	map = m;
}
void BubbleFromPlayer::Movement(Directions d)
{
	ClampPos();
	Stomp();
	if (poped == true)
	{
		return;
	}

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
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);

					stages++;
				}
				inShoot = true;

				dir = { -2, 0 };
				if (pos.x <= logPosXL) {
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);

					stages++;
				}
				break;
			case 2:
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
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);

					stages++;
				}
				inShoot = true;

				dir = { 2, 0 };
				if (pos.x >= logPosXR) {
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);

					stages++;
				}
				break;
			case 2:
				canCollide = false;

				inShoot = false;
				
				dir = { 0, -1 };

				break;

			}

		}
	}
	
}
void BubbleFromPlayer::MoveBubbleRightPlayer()
{
	AABB box;
	direction = Directions::RIGHT;
	pos += {1, 0};
	box = GetHitbox();
	if (!map->TestCollisionAir(box)) {
		issAlive = false;
	}
}

void BubbleFromPlayer::MoveBubbleLeftPlayer()
{
	AABB box;
	direction = Directions::LEFT;
	pos += {-1, 0};
	box = GetHitbox();
	if (!map->TestCollisionAir(box)) {
		issAlive = false;
	}
}
void BubbleFromPlayer::HandleCollisionLogic()
{
	
}
void BubbleFromPlayer::MoveBubbleToRandomNear()
{
	float ranIndexX = GetRandomValue(0, 1);
	float ranIndexY = GetRandomValue(0, 1);

	pos.x -= ranIndexX;
	pos.y -= ranIndexY;
}
void BubbleFromPlayer::DrawDebug(const Color & col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
void BubbleFromPlayer::Release()
{

	render->Release();
}
Directions BubbleFromPlayer::BublePop(Directions d)
{

	if (pos.x<=16)
	{
		d = Directions::RIGHT;

	}
	if (pos.x+16>=240)
	{
		d = Directions::LEFT;

	}


		if (d == Directions::LEFT)
		{
			if ((framecounter / 60) <= 0.5)
			{
				pos.x = pos.x - 1;
				pos.y = pos.y - 2 ;

				framecounter++;
			}
			else if (0.5 < (framecounter / 60) && (framecounter / 60) <= 1)
			{
				pos.x= pos.x-1;
				pos.y=pos.y-1;
				framecounter++;
			}
			else if (1 < (framecounter / 60))
			{
				pos.y = pos.y + 3;
				pos.x=pos.x-1;

				framecounter++;
				if (map->TestCollisionGround(GetHitbox(), &pos.y) == true)
				{
					fruit = true;
				}
			}
			return Directions::LEFT;
		}
		else if (d == Directions::RIGHT)
		{

			if ((framecounter / 60) <= 0.5)
			{
				pos.x = pos.x + 2;
				pos.y = pos.y - 3;
				framecounter++;
			}
			else if (0.5 < (framecounter / 60) && (framecounter / 60 )<= 1)
			{
				pos.x = pos.x + 2;
				pos.y = pos.y - 2;

				framecounter++;
			}
			else if (1 < (framecounter / 60))
			{
				pos.y = pos.y + 4;
				pos.x = pos.x + 2;

				framecounter++;
				if (map->TestCollisionGround(GetHitbox(),&pos.y) == true)
				{
					fruit = true;
				}
			}
			return Directions::RIGHT;

		}
}