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
	Rectangle rc;
	const int n = TILE_SIZE;
	const int p = PADDINGG_X;
	const int y = 16;

	ResourceManager& data = ResourceManager::Instance();
	data.LoadTexture(Resource::IMG_BUBBLES, "images/Bubbles.png");

	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	
	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + p), y, n, n });
    sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + p), y, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, ANIM_DELAY + 6);
	for(int i = 0; i < 6; ++i)
		sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { (float)i * n, 0, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::ZENCHANG, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANG, { 0, 2*y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANG, { n, 2*	y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANG, { 2*n, 2 * y, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::ZENCHANY, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANY, { 6*n, 2 * y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANY, { 7*n, 2 * y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANY, { 8 * n, 2 * y, n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::ZENCHANR, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANR, { 9 * n, 2 * y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANR, { 10 * n, 2 * y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::ZENCHANR, { 11 * n, 2 * y, n, n });



	sprite->SetAnimation((int)BubbleAnim::INSHOOT);
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
		SetAnimation((int)BubbleAnim::ZENCHANG);
		bubbleStages++;
		break;
	case (int)BubbleStages::GREENSTAGE_:
		if (eTimeCatch > eTimeCatchGreen) bubbleStages++;
		eTimeCatch += GetFrameTime();
		break;
	case (int)BubbleStages::YELLOWSTAGE:
		eTimeCatch = 0;
		SetAnimation((int)BubbleAnim::ZENCHANY);
		bubbleStages++;
		break;
	case (int)BubbleStages::YELLOWSTAGE_:
		if (eTimeCatch > eTimeCatchYellow) bubbleStages++;
		eTimeCatch += GetFrameTime();
		break;
	case (int)BubbleStages::REDSTAGE:
		eTimeCatch = 0;
		SetAnimation((int)BubbleAnim::ZENCHANR);
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
				SetAnimation((int)BubbleAnim::INSHOOT);
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
				if(!inCatch) SetAnimation((int)BubbleAnim::IDLE);
				canCollide = false;

				inShoot = false;
				dir = { 0, -1 };
				break;


			}
		}
		else if (d == Directions::RIGHT)
		{

			switch (stages) {
				SetAnimation((int)BubbleAnim::INSHOOT);
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
				if (!inCatch) SetAnimation((int)BubbleAnim::IDLE);
				canCollide = false;

				inShoot = false;
				dir = { 0, -1 };

				break;

			}

		}
	}
	
}
void BubbleFromPlayer::DrawDebug(const Color & col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
void BubbleFromPlayer::Release()
{

	render->Release();
}
