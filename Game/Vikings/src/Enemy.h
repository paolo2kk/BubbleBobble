#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 32x32
#define ENEMY_FRAME_SIZE		16
//Logical model size: 12x28
#define ENEMY_PHYSICAL_WIDTH	10
#define ENEMY_PHYSICAL_HEIGHT	12

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED			2
#define OBJECTIVEJUMP_X			2
#define INJUMPXSPEED			2

//When jumping, initial jump speed and maximum falling speed
#define ENEMY_JUMP_FORCE		10
#define ENEMY_JUMP_LIMIT		9.5

//Frame delay for updating the jump velocity
#define ENEMY_JUMP_DELAY		2

//Enemy is levitating when abs(speed) <= this value
#define ENEMY_LEVITATING_SPEED	2

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

//Logic states
enum class StateEnemy { IDLE, WALKING, JUMPING, FALLING, CLIMBING, DEAD, TRANSITIONING };
enum class LookEnemy { RIGHT, LEFT };
enum class Type { ZEN_CHAN, };

//Rendering states
enum class EnemyAnim {
	WALKING_LEFT, WALKING_RIGHT,
	ENOJAO_LEFT, ENOJAO_RIGHT,
	CAGAO_LEFT, CAGAO_RIGHT,
	SPINNER, BUBBLE_P1,
	NUM_ANIMATIONS,
};

class Enemy: public Entity
{
public:
	Enemy(const Point& p, StateEnemy s, LookEnemy view, Type enemyType);
	~Enemy();
	
	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	bool IsLookingRight() const;
	bool IsLookingLeft() const;
	bool canJump = true;
private:
	
	//Enemy mechanics
	void MoveX();
	void MoveY();

	//Animation management
	void SetAnimation(int id);
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartFalling();
	void StartJumping();
	void ChangeAnimRight();
	void ChangeAnimLeft();

	//Jump steps
	bool IsAscending() const;
	bool IsLevitating() const;
	bool IsDescending() const;
	bool isStill = false;
	

	StateEnemy state;
	LookEnemy look;
	Type type;
	int jump_delay;
	float cFrame = 0, eFrame = 0, maxFrame = 8;
	int score;
	TileMap *map;

};

