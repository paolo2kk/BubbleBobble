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
	const int n = TILE_SIZE;
	const int y = 22;
	inShoot = true;
	eTimePogo = 0;

	ResourceManager& data = ResourceManager::Instance();
	data.LoadTexture(Resource::IMG_BUBBLES, "images/Bubbles.png");

	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
	
	Sprite* sprite = dynamic_cast<Sprite*>(render);

	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + 1), n + PADDINGG_Y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + 1), n + PADDINGG_Y, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 2 * (n), 0, n, n });

	sprite->SetAnimation((int)BubbleAnim::INSHOOT);
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
	const int y = 22;

	ResourceManager& data = ResourceManager::Instance();
	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	
	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { 2 * (n + p), y, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 2 * (n), 0, n, n });

	sprite->SetAnimation((int)BubbleAnim::INSHOOT);
	return AppStatus::OK;

}
void BubbleFromPlayer::Update()
{
	pos += dir;
	Movement(dire);
}
bool BubbleFromPlayer::isAlive()
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

void BubbleFromPlayer::Movement(Directions d)
{
	ClampPos();
	Stomp();
	if (pos.y > 32)
	{
		if (d == Directions::LEFT)
		{
			switch (stages) {
			case 1:
				if (pos.x < 20)
				{

					pos.x++;
					stages++;
				}
				inShoot = true;
				SetAnimation((int)BubbleAnim::INSHOOT);

				dir = { -2, 0 };
				if (pos.x <= logPosXL) {
					stages++;
				}
				break;
			case 2:
				SetAnimation((int)BubbleAnim::IDLE);

				inShoot = false;
				dir = { 0, -1 };
				break;


			}
		}
		else if (d == Directions::RIGHT)
		{

			switch (stages) {
			case 1:
				if (pos.x > 226)
				{
					pos.x--;
					stages++;
				}
				inShoot = true;
				SetAnimation((int)BubbleAnim::INSHOOT);

				dir = { 2, 0 };
				if (pos.x >= logPosXR) {
					stages++;
				}
				break;
			case 2:
				SetAnimation((int)BubbleAnim::IDLE);

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
