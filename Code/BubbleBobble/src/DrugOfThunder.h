#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Player.h"
#include "Player2.h"
#include "Enemy.h"
#include "DrugOfThunder.h"

#define DT_PHYSICAL_SIZE	14
#define DT_FRAME_SIZE		16
#define POGOJUMP				-30

#define PADDINGG_X 0
#define PADDINGG_Y 6

#define SHOOT_RANGE 65


class DOT : public Entity
{
public:
	DOT(const Point& p, Directions d);
	~DOT();

	void Update();

	void Movement(Directions d);
	void MoveBubbleRightPlayer();
	void MoveBubbleLeftPlayer();
	void SetIdle();
	void MoveBubbleRightPlayerRandom();
	void MoveBubbleLeftPlayerRandom();
	void ClampPos();
	AppStatus Initialise();
	bool isAlive();
	void Release();
	Directions dire;
	int stages;
	void DrawDebug(const Color& col) const;
	void Stomp();
	void SetTileMap(TileMap* m);
	void SetPlayer(Player* p);
	void SetPlayer2(Player2* p);
	bool inCatch = false;
	bool hasEndedFromCatch = false;
	bool poped = false;
	bool particles = false;
	bool fruit = false;
	float framecounter;
	float framecounter2;
	bool canCollide;
	Point GetPos() const;
	void EnemyCatchSlime();
	void EnemyCatchDrunk();
	bool issAlive;
	void MoveBubbleToRandomNear();

	Directions BublePop(Directions d);
	void StayBehind(DOT* bub);

	void MoveBubbleToRandomNear(DOT* bubble2);

	bool inShoot;
	bool CollisionWall(const Point& p, int distance) const;
	int enemytype = 0;
	bool diffWindMap = false;
	bool popedParticles;
	bool isP2 = false;
private:
	void HandleCollisionLogic();
	bool isUp = false;

	//void DrawDebug(const Color& col) const;
	void SetAnimation(int id);
	int bubbleStages = (int)BubbleStages::GREENSTAGE;

	int logPosXL;
	int logPosXR;
	float spawnTime;
	float eTime;
	float eAnimDebug = 0;
	float eTimePogo;
	float eTimeCatch = 0;
	float eTimeCatchGreen = 1.5;
	float eTimeCatchYellow = 1;
	float eTimeCatchRed = 1;
	float lifeTime;
	float speed;
	Player* player;
	Player2* player2;
	TileMap* map;
	Directions direction;
};