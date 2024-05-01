#pragma once
#include "Enemy.h"

#define TURRET_SHOT_SPEED		4
#define TURRET_SHOOT_DELAY		30	//waiting time between states idle/attack

#define TURRET_SHOT_OFFSET_X_LEFT	 -5
#define TURRET_SHOT_OFFSET_X_RIGHT	 25
#define TURRET_SHOT_OFFSET_Y		-17

enum class TurretState { IDLE, ATTACK };
enum class TurretAnim { IDLE_LEFT, IDLE_RIGHT, ATTACK_LEFT, ATTACK_RIGHT, NUM_ANIMATIONS };

class Turret : public Enemy
{
public:
	Turret(const Point& p, int width, int height, int frame_width, int frame_height);
	~Turret();

	//Initialize the enemy with the specified look and area
	AppStatus Initialise(Look look, const AABB& area) override;

	//Update the enemy according to its logic, return true if the enemy must shoot
	bool Update(const AABB& box) override;

	//Retrieve the position and direction of the shot to be thrown
	void GetShootingPosDir(Point* pos, Point* dir) const override;

private:
	int attack_delay;	//delay between attacks
	TurretState state;
};

