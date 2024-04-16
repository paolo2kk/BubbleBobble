#pragma once
#include "Entity.h"
<<<<<<< Updated upstream
#include "Player.h"
#include "TileMap.h"

//Representation model size: 32x32
#define BUBBLE_FRAME_SIZE		16
#define PADDING_X	4
#define PADDING_Y	6
//Logical model size: 12x28
#define BUBBLE_PHYSICAL_WIDTH	16
#define BUBBLE_PHYSICAL_HEIGHT	16

#define BUBBLE_SPEED			2
#define SHOOT_DELAY				2
#define SHOOT_RANGE				2
#define SHOOT_SPEED				2

#define GRAVITY_FORCE			1


enum class States { INSHOOT, CRUSHEDSIDE, CRUSHEDTOP, ENEMYCAGING, POP };
enum class Looks { RIGHT, LEFT };

enum class BubbleAnim {
	IDLE, INSHOOT, CRUSHED_SIDE, CRUSHED_TOP, ENEMY_CAGED, POPPED, NUM_ANIMATIONS
};

class Bubble : public Player
{
public:
	Bubble(const Point& p, State s, Look view);
	~Bubble();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	int shoot_delay;
	Point startPos;

private:

	//Bubble mechanics
	void MovementX();
	void MovementY();
	void StartFloating();
	bool MovementXfinished = false;

	//Animation management
	void SetAnimation(int id);
	void SetCrushedSideAnimation();
	void SetCrushedTopAnimation();
	void Stop();
	

	State state;
	Look look;
	float cFrame = 0, eFrame = 0, maxFrame = 8;
	Player* p;

	TileMap* map;

};
=======

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
	int Points() const;
	bool isAlive();
	void Release();

private:
	Direction dire;
	float spawnTime;
	float eTime;
	float lifeTime;
	float speed;
	int stages;
};





//#pragma once
//#include "Entity.h"
//#include "TileMap.h"
//
//#define BUBBLE_FRAME_SIZE 16
//
//#define BUBBLE_PHYSICAL_WIDTH	16
//#define BUBBLE_PHYSICAL_HEIGHT	16
//
//#define BUBBLE_SPEED			2
//#define GRAVITY_FORCE			1
//
//enum class BubbleAnim {
//	IDLE, NUM_ANIMATIONS
//};
//enum class States {
//	ALIVE, POPPED
//};
//enum class Looks {
//	LEFT, RIGHT
//};
//class Bubble : public Entity
//{
//
//public:
//	Bubble(const Point& p, States s, Looks view);
//	~Bubble();
//	void SetTileMap(TileMap * tilemap); 
//	void SetAnimation(int id);
//	void Update();
//	void Render();
//	AppStatus Initialise();
//	void DrawDebug(const Color& col) const;
//	void Release();
//private:
//	Looks look;
//	States state;
//
//};
>>>>>>> Stashed changes
