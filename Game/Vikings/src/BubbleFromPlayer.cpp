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
	lifeTime = GetRandomValue(3, 5);
	Rectangle rc;
	const int n = TILE_SIZE;
	const int y = 22;



	ResourceManager& data = ResourceManager::Instance();
	data.LoadTexture(Resource::IMG_BUBBLES, "images/Bubbles.png");

	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
	
	Sprite* sprite = dynamic_cast<Sprite*>(render);

	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, 30);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + 1), n + PADDINGG_Y, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { (n + 1), n + PADDINGG_Y, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, 30);
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 2 * (n), 0, n, n });

	sprite->SetAnimation((int)BubbleAnim::IDLE);
}
BubbleFromPlayer::~BubbleFromPlayer()
{
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

	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, 30);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { 2 * (n + p), y, n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, 30);
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 0, 0, n, n });
	sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { 2 * (n), 0, n, n });

	sprite->SetAnimation((int)BubbleAnim::IDLE); 
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
void BubbleFromPlayer::ClampPos(Directions d)
{

}
void BubbleFromPlayer::Movement(Directions d)
{

	if (d == Directions::LEFT)
	{
		switch (stages) {
		case 1:
			dir = { -2, 0 };
			if (pos.x <= logPosXL) {
				stages++;
			}
			break;
		case 2:
			dir = { 0, -1 };
			break;


		}
	}
	else if (d == Directions::RIGHT)
	{

		switch (stages) {
		case 1:
			dir = { 2, 0 };
			if (pos.x >= logPosXR) {
				stages++;
			}
			break;
		case 2:
			dir = { 0, -1 };

			break;

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
