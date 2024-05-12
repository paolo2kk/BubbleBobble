#pragma once
#include "Entity.h"
#include "TileMap.h"

#define BUBBLE_PHYSICAL_SIZE	14
#define BUBBLE_FRAME_SIZE		16

#define POINTS_APPLE	10
#define POINTS_CHILI	20

enum class Direction { LEFT, RIGHT };

class Bubble : public Entity
{
public:
	Bubble(const Point& p, Direction d);
	~Bubble();

	void Update();

	void LeftMovement(Direction d);

	void DrawDebug(const Color& col) const;
	bool isAlive();
	void Release();
	Direction dire;

private:
	float spawnTime;
	float eTime;
	float lifeTime;
	float speed;
	int stages;
};