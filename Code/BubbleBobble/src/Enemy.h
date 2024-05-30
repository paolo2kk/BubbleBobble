#pragma once
#include "Entity.h"
#include "BubbleFromPlayer.h"

//Representation model size: 32x32
#define SLIME_FRAME_SIZE		16
#define SD_FRAME_SIZE		    64

//Logical model size: 24x30
#define SLIME_PHYSICAL_WIDTH	6
#define SLIME_PHYSICAL_HEIGHT	7

#define SD_PHYSICAL_WIDTH    	6
#define SD_PHYSICAL_HEIGHT	    7

//Representation model size: 32x32
#define TURRET_FRAME_SIZE		16
//Logical model size: 0x0
#define TURRET_PHYSICAL_WIDTH	16
#define TURRET_PHYSICAL_HEIGHT	16

enum class EnemyType { SLIME, TURRET, DRUNK, BOTTLE, SD };

class Enemy : public Entity
{
public:
	Enemy(const Point& p, int width, int height, int frame_width, int frame_height);
	virtual ~Enemy();

	//Draw the maximum visibility area of the enemy
	void DrawVisibilityArea(const Color& col) const;

	//Pure virtual functions, any class inheriting from this class must provide its own implementations

	//Initialize the enemy with the specified look and area
	virtual AppStatus Initialise(Look look, const AABB& area) = 0;

	//Update the enemy according to its logic, return true if the enemy must shoot
	virtual bool Update(const AABB& box) = 0;
	bool lerping = false;

	//Retrieve the position and direction of the shot to be thrown
	virtual void GetShootingPosDir(Point* pos, Point* dir) const = 0;
	bool isshooting = false;
	Look GetDir();

	bool noSpawnMore = false;
protected:
	//Return true if the given hitbox is within the visibility area and the enemy is facing it
	bool IsVisible(const AABB& hitbox);
	Look look;
	AABB visibility_area;
};

