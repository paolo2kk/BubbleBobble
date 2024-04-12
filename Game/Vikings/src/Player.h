#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 32x32
#define PLAYER_FRAME_SIZE		17
#define PADDING_X	4
#define PADDING_Y	3
//Logical model size: 12x28
#define PLAYER_PHYSICAL_WIDTH	12
#define PLAYER_PHYSICAL_HEIGHT	12

//Horizontal speed and vertical speed while falling down
#define PLAYER_SPEED			2
#define OBJECTIVEJUMP_X			2
#define INJUMPXSPEED			2
//When jumping, initial jump speed and maximum falling speed
#define PLAYER_JUMP_FORCE		10
#define PLAYER_JUMP_LIMIT		9.5

//Frame delay for updating the jump velocity
#define PLAYER_JUMP_DELAY		2

//Player is levitating when abs(speed) <= this value
#define PLAYER_LEVITATING_SPEED	4

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

//Logic states
enum class State { IDLE, WALKING, JUMPING, FALLING, CLIMBING, DEAD };
enum class Look { RIGHT, LEFT };

//Rendering states
enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT,
	WALKING_LEFT, WALKING_RIGHT,
	JUMPING_LEFT, JUMPING_RIGHT,
	LEVITATING_LEFT, LEVITATING_RIGHT,
	FALLING_LEFT, FALLING_RIGHT,
	CLIMBING_LEFT, CLIMBING_RIGHT,
	SHOCK_LEFT, SHOCK_RIGHT,
	TELEPORT_LEFT, TELEPORT_RIGHT,
	LASER_ANIM, SHOOT_BUBBLE,
	NUM_ANIMATIONS
};

class Player: public Entity
{
public:
	Player(const Point& p, State s, Look view);
	~Player();
	
	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	bool CreatingBubble();
	bool IsLookingRight() const;
	bool IsLookingLeft() const;
	bool BubbleIsBeingCreated = false;

private:
	
	//Player mechanics
	void MoveX();
	void MoveY();
	void LaserTag();
	void LaserProcedures();

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
	bool inLaser = false;
	bool isStill = true;
	bool initiallyLookingR = true;
	bool initiallyLookingL = true;

	State state;
	Look look;
	int jump_delay;
	float cFrame = 0, eFrame = 0, maxFrame = 8;
	
	TileMap *map;
};

