#pragma once
#include "Enemy.h"
#include "TileMap.h"
#include "BubbleFromPlayer.h"

#define BOTTLE_SPEED			1
#define BOTTLE_ANIM_DELAY	(2 * ANIM_DELAY)

#define BOTTLE_SHOT_OFFSET_X_LEFT	-14
#define BOTTLE_SHOT_OFFSET_X_RIGHT	 26
#define BOTTLE_SHOT_OFFSET_Y			-22

#define BOTTLE_SHOT_SPEED	4

enum class BottleState { ROAMING, ATTACK, FALLING, JUMPING };
enum class BottleAnim {
	IDLE_LEFT, IDLE_RIGHT, WALKING_LEFT, WALKING_RIGHT,
	ATTACK_LEFT, ATTACK_RIGHT, NUM_ANIMATIONS
};

struct Stepss
{
	Point speed;	//direction
	int frames;		//duration in number of frames
	int anim;		//graphical representation
};

class Bottle : public Enemy
{
public:
	Bottle(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* map);
	~Bottle();

	//Initialize the enemy with the specified look and area
	AppStatus Initialise(Look look, const AABB& area) override;

	void BubbleSetter(BubbleFromPlayer* bub);

	EnemyType GetEnemyType() const;

	//Update the enemy according to its logic, return true if the enemy must shoot
	bool Update(const AABB& box) override;


	//Retrieve the position and direction of the shot to be thrown
	void GetShootingPosDir(Point* pos, Point* dir) const override;
	
private:
	//Create the pattern behaviour
	void MoveX();
	void SetAnimation(int id);
	void MoveY();
	void StartFalling();
	void Stop();
	//Update looking direction according to the current step of the pattern
	void UpdateLook(int anim_id);

	int attack_delay;	//delay between attacks
	BottleState state;
	TileMap* map;
	int current_step;	//current step of the pattern
	int current_frames;	//number of frames in the current step
	std::vector<BubbleFromPlayer*> bubbles;
};

