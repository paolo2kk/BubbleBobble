#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"
#include "BubbleFromPlayer.h"

#define BUBBLE_PHYSICAL_SIZE	14
#define BUBBLE_FRAME_SIZE		16
#define POGOJUMP				-30

#define PADDINGG_X 0
#define PADDINGG_Y 6

#define SHOOT_RANGE 65

enum class Directions { LEFT, RIGHT };
enum class BubbleAnim {INSHOOT, IDLE, SMASHED, ZENCHANG, ZENCHANY, ZENCHANR, ZENCHANBLINK, NUM_ANIMATIONS};
class BubbleFromPlayer : public Entity
{
public:
	BubbleFromPlayer(const Point& p, Directions d);
	~BubbleFromPlayer();

	void Update();

	void Movement(Directions d);
	void ClampPos();
	AppStatus Initialise();
	bool isAlive();
	void Release();
	Directions dire;
	int stages;
	void DrawDebug(const Color& col) const;
	void Stomp();
	void EnemyCatch();
	void SetPlayer(Player* p);
	bool inCatch = false;
private:
	//void DrawDebug(const Color& col) const;
	void SetAnimation(int id);
	int bubbleStages = 0;

	bool inShoot;
	int logPosXL;
	int logPosXR;
	float spawnTime;
	float eTime;
	float eTimePogo;
	float lifeTime;
	float speed;
	Player* player;
};