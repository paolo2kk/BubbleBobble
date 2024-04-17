#include "Bubble.h"
#include "Sprite.h"
#include "TileMap.h"
#include "StaticImage.h"
#include "Globals.h"
#include <raymath.h>

Bubble::Bubble(const Point& p, Direction d) : Entity(p, BUBBLE_PHYSICAL_SIZE, BUBBLE_PHYSICAL_SIZE, BUBBLE_FRAME_SIZE, BUBBLE_FRAME_SIZE)
{
	dire = d;
	speed = .3;
	stages = 1;
	Rectangle rc;
	const int n = TILE_SIZE;
	eTime = 0;
	spawnTime = 0;
	lifeTime = GetRandomValue(3, 5);
	
	switch (dire)
	{
	case Direction::LEFT: rc = { n, n, n, n }; break;
	case Direction::RIGHT: rc = { n, n, n, n }; break;

	default: LOG("Internal error: object creation of invalid type");
	}
	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_TILES), rc);
}
Bubble::~Bubble()
{
}
void Bubble::Update()
{

	pos += dir;

	LeftMovement(dire);

}
bool Bubble::isAlive()
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
void Bubble::LeftMovement(Direction d)
{

	if (d == Direction::LEFT)
	{
		switch (stages) {
		case 1:
			dir = { 0, -1 };
			if (pos.y <= 200) {
				stages++;
			}
			break;
		case 2:
			dir = { 1, 0 };
			if (pos.x >= 105) {
				stages++;
			}
			break;
		case 3:
			dir = { 0, -1 };
			if (pos.y <= 144) {
				stages++;
			}
			break;
		case 4:
			dir = { -1, 0 };
			if (pos.x <= 24) {
				stages++;
			}
			break;
		case 5:
			dir = { 0, -1 };

			break;
		}


	}
	else if (d == Direction::RIGHT)
	{

		switch (stages) {
		case 1:
			dir = { 0, -1 };
			if (pos.y <= 200) {
				stages++;
			}
			break;
		case 2:
			dir = { -1, 0 };
			if (pos.x <= 136) {
				stages++;
			}
			break;
		case 3:
			dir = { 0, -1 };
			if (pos.y <= 144) {
				stages++;
			}
			break;
		case 4:
			dir = { 1, 0 };
			if (pos.x >= 216) {
				stages++;
			}
			break;
		case 5:
			dir = { 0, -1 };

			break;
		}


	}
}
void Bubble::DrawDebug(const Color & col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
void Bubble::Release()
{

	render->Release();
}
