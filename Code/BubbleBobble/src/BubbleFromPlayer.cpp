#include "BubbleFromPlayer.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>
#include "Object.h"


BubbleFromPlayer::BubbleFromPlayer(const Point& p, Directions d) : Entity(p, BUBBLE_PHYSICAL_SIZE, BUBBLE_PHYSICAL_SIZE, BUBBLE_FRAME_SIZE, BUBBLE_FRAME_SIZE)
{
	particles = false;
	dire = d;
	speed = .3;
	stages = 0;
	logPosXL = pos.x - SHOOT_RANGE;
	logPosXR = pos.x + SHOOT_RANGE;
	eTime = 0;
	spawnTime = 0;
	player = nullptr;
	lifeTime = GetRandomValue(4, 6);
	Rectangle rc;
	inShoot = true;
	eTimePogo = 0;
	canCollide = true;
	issAlive = true;
	poped = false;
	framecounter = 0;
	framecounter2 = 0;
	fruit = false;
	ResourceManager::Instance().PlaySoundEffect(Resource::SFX_BUBBLE);
	popedParticles = false;

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
	if(isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_L);
	return AppStatus::OK;
	logPosXL = pos.x - SHOOT_RANGE;
	logPosXR = pos.x + SHOOT_RANGE;
}
void BubbleFromPlayer::Update()
{
	if (particles == true)
	{
		Draw();
		Sprite* sprite = dynamic_cast<Sprite*>(render);
		sprite->Update();
		return;
	}
	if (poped == false)
	{
		Movement(dire);
		pos += dir;
	}
	else
	{
		dire = BublePop(dire);
	}
	eAnimDebug += GetFrameTime();
	if (eAnimDebug < .2) {
		SetAnimation((int)Animations::SPAWN_BUBBLE_GREEN_L);
		if (isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_L);
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
	if (popedParticles == true)
	{
		if (framecounter2 / 60 > 0.5)
		{
			return false;
		}
		else
		{
			if (particles == false)
			{
				hasEndedFromCatch = true;
				SetAnimation((int)Animations::BUBBLE_POP);
			}
			framecounter2++;
			particles = true;
			return true;
		}
	}
	else if (!inCatch)
	{
		eTime += GetFrameTime();
		if (eTime >= lifeTime)
		{
			return false;
		}
		else if(eTime >= lifeTime - 0.5)
		{
			if (particles == false)
			{
				SetAnimation((int)Animations::BUBBLE_POP);
			}
			particles = true;
			return true;
		}
		else 
		{
			return true;
		}
	}
	else
	{
		if (framecounter2 / 60 > 0.5)
		{
			return false;
		}
		else if (bubbleStages == (int)BubbleStages::ENDED)
		{
			if (particles == false)
			{
				hasEndedFromCatch = true;
				SetAnimation((int)Animations::BUBBLE_POP);
			}
			framecounter2++;
			particles = true;
			return true;
		}
		else
		{
			return true;
		}
	}

	
}
void BubbleFromPlayer::ClampPos()
{
	if (diffWindMap == false) {
		if (pos.y < 32)
		{
			if (pos.x <= WINDOW_WIDTH / 2)
			{
				dir = { 1, 1 };
			}
			else {
				dir = { -1, 1 };
			}
		}
		if (pos.y == 32)
		{
			if (pos.x <= GetRandomValue(110, WINDOW_WIDTH / 2))
			{
				dir = { 1, 0 };
			}
			else if (pos.x > GetRandomValue(WINDOW_WIDTH / 2, 140))
			{

				dir = { -1, 0 };
			}
		}
	}
	else {
		int prev_y = pos.y;
		if (pos.y < WINDOW_HEIGHT / 2 + 32)
		{
			pos.y = prev_y + 2;
		}
		if (pos.y == WINDOW_HEIGHT / 2 + 32)
		{
			if (pos.x <= GetRandomValue(110, WINDOW_WIDTH / 2))
			{
				dir = { 1, 0 };
			}
			else if (pos.x > GetRandomValue(WINDOW_WIDTH / 2, 140))
			{

				dir = { -1, 0 };
			}
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
		if (player != nullptr && IsKeyDown(KEY_PERIOD))
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
void BubbleFromPlayer::FromDown()
{
	if (!inShoot && !popedParticles && eTimeBug <= 3)
	{
		AABB box = GetHitbox();
		if (player != nullptr)
		{
			if (player->TestCollisionFromBelow(box, &pos.y))
			{
				cameFromDown = true;
			}
		}
	}
	eTimeBug += GetFrameTime();
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
		if(isP2)SetAnimation((int)Animations::ZENCHAN_BUBBLE_BLUE);

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
			if (isP2)SetAnimation((int)Animations::DRUNK_BUBBLE_BLUE);

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
	FromDown();
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

			case 0:
				if (isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_L);
				stages++;

			case 1:
				if (pos.x < 20)
				{
					pos.x++;
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);
					if(isThund)  SetAnimation((int)Animations::THUNDER_BUBBLE_GREEN);
					stages++;
				}
				inShoot = true;

				dir = { -2, 0 };
				if (pos.x <= logPosXL) {
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_GREEN);
					if (isThund)  SetAnimation((int)Animations::THUNDER_BUBBLE_GREEN);
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
				if (isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_R);

			case 0:
				if (isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_L);
				stages++;

			case 1:
				if (pos.x > 226)
				{
					pos.x--;
					if (!inCatch)
					{
						SetAnimation((int)Animations::BUBBLE_GREEN);
						if (isP2) SetAnimation((int)Animations::BUBBLE_BLUE);
						if (isThund && !isP2)  SetAnimation((int)Animations::THUNDER_BUBBLE_GREEN);
						if (isThund && isP2)  SetAnimation((int)Animations::THUNDER_BUBBLE_BLUE);

					}
					stages++;
				}
				inShoot = true;

				dir = { 2, 0 };
				if (pos.x >= logPosXR) {
					if (!inCatch) {
						SetAnimation((int)Animations::BUBBLE_GREEN);
						if (isP2) SetAnimation((int)Animations::BUBBLE_BLUE);
						if (isThund && !isP2)  SetAnimation((int)Animations::THUNDER_BUBBLE_GREEN);
						if (isThund && isP2)  SetAnimation((int)Animations::THUNDER_BUBBLE_BLUE);

					}
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
		else if (d == Directions::RIGHTDEBUG)
		{

			switch (stages) {
				SetAnimation((int)Animations::SPAWN_BUBBLE_GREEN_L);

			case 0:
				if (isP2) SetAnimation((int)Animations::SPAWN_BUBBLE_BLUE_L);
				if(isThund) SetAnimation((int)Animations::THUNDER_BUBBLE_BLUE);
				stages++;

			case 1:
				if (pos.x < 20)
				{
					pos.x++;
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_BLUE);

					stages++;
				}
				inShoot = true;

				dir = { -2, 0 };
				if (pos.x <= logPosXL) {
					if (!inCatch) SetAnimation((int)Animations::BUBBLE_BLUE);
					if (isThund) SetAnimation((int)Animations::THUNDER_BUBBLE_BLUE);

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
	/*if (!map->TestCollisionAir(box)) {
		issAlive = false;
	}*/

}
void BubbleFromPlayer::MoveBubbleLeftPlayer()
{

	AABB box;
	direction = Directions::LEFT;
	pos += {-1, 0};
	box = GetHitbox();
	/*if (!map->TestCollisionAir(box)) {
		issAlive = false;
	}*/

}
void BubbleFromPlayer::SetIdle()
{
	SetAnimation((int)Animations::BUBBLE_GREEN);

}
void BubbleFromPlayer::HandleCollisionLogic()
{
	
}
void BubbleFromPlayer::StayBehind(BubbleFromPlayer* bub)
{
	pos.x = bub->pos.x - 16;
	
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

}
Directions BubbleFromPlayer::BublePop(Directions d)
{
	if (noZesty == false)
	{
		if (pos.x <= 16)
		{
			d = Directions::RIGHT;

		}
		if (pos.x + 16 >= 240)
		{
			d = Directions::LEFT;

		}


		if (d == Directions::LEFT)
		{
			if ((framecounter / 60) <= 0.5)
			{
				pos.x = pos.x - 1;
				pos.y = pos.y - 2;

				framecounter++;
			}
			else if (0.5 < (framecounter / 60) && (framecounter / 60) <= 1)
			{
				pos.x = pos.x - 1;
				pos.y = pos.y - 1;
				framecounter++;
			}
			else if (1 < (framecounter / 60))
			{
				pos.y = pos.y + 3;
				pos.x = pos.x - 1;

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
			else if (0.5 < (framecounter / 60) && (framecounter / 60) <= 1)
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
				if (map->TestCollisionGround(GetHitbox(), &pos.y) == true)
				{
					fruit = true;
				}
			}
			return Directions::RIGHT;

		}
	}
	
}