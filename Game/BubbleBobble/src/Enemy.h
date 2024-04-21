#pragma once
#include "Entity.h"
#include "TileMap.h"

//Representation model size: 16x16
#define ENEMY_FRAME_SIZE		16

//Logical model size
#define	ENEMY_PHYSICAL_WIDTH	10
#define ENEMY_PHYSICAL_HEIGTH	12

//

enum class EnemyState { NORMAL, ANGRY, JUMPING, FALLING };
enum class EnemyLook { RIGHT, LEFT };
enum class EnemyType {ZENCHAN, BANEBOU};
enum class ZenChanAnimations {
	WALK_RIGHT, WALK_LEFT,
	ANGRY_LEFT, ANGRY_RIGHT,
	DEAD, BUBBLE_P1,
	NUM_ANIMATIONS
};
enum class BanebouAnimations {
	WALK_RIGHT, WALK_LEFT,
	ANGRY_LEFT, ANGRY_RIGHT,
	DEAD, BUBBLE_P1,
	NUM_ANIMATIONS
};

class Enemy : public Entity {
public:
	Enemy(const Point& p, EnemyState s, EnemyLook l, EnemyType t);
	~Enemy();

	AppStatus Initialise();
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	void SetTileMap(TileMap* tilemap);

private:

	//Movement
	void MoveXzenchan();
	void MoveXbanebou();

	void MoveY();
	void StartJumping();
	void StartFalling();
	bool IsLookingRight();
	bool IsLookingLeft();

	//Animations
	void SetAnimation(int id);
	void Stop();
	EnemyType type;

	EnemyState state;
	EnemyLook look;
	float angryTimer;
	float eJumpFrame;
	float jump_delay = 0;
	TileMap* map;

};