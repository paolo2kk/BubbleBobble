#pragma once
#include "Enemy.h"
#include "TileMap.h"
#include "BubbleFromPlayer.h"

#define SD_SPEED			1
#define SD_ANIM_DELAY	(2 * ANIM_DELAY)

#define SD_SHOT_OFFSET_X_LEFT	-14
#define SD_SHOT_OFFSET_X_RIGHT	 26
#define SD_SHOT_OFFSET_Y			-22

#define SD_SHOT_SPEED	4

enum class SDState { ROAMING, ATTACK, FALLING, JUMPING };
enum class SDdir {NE, ES, SW, WN, STOP, INBUBBLE, DED, DED2};
enum class SDAnim {
	IDLE_LEFT, IDLE_RIGHT, WALKING_LEFT, WALKING_RIGHT,
	ATTACK_LEFT, ATTACK_RIGHT, NUM_ANIMATIONS
};

struct Stepss
{
	Point speed;	//direction
	int frames;		//duration in number of frames
	int anim;		//graphical representation
};

class SD : public Enemy
{
public:
	SD(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* map);
	~SD();

	//Initialize the enemy with the specified look and area
	AppStatus Initialise(Look look, const AABB& area) override;

	void BubbleSetter(BubbleFromPlayer* bub);

	//Update the enemy according to its logic, return true if the enemy must shoot
	bool Update(const AABB& box) override;


	//Retrieve the position and direction of the shot to be thrown
	void GetShootingPosDir(Point* pos, Point* dir) const override;
	bool bossDed = false; 

private:
	//Create the pattern behaviour
	float eTimeLerp = 0;

	void MoveX();
	void SetAnimation(int id);
	void StartFalling();
	void Stop();
	//Update looking direction according to the current step of the pattern
	void UpdateLook(int anim_id);
	bool defusehitbox = false;
	bool hasAlreadyJumped = false;
	int attack_delay;	//delay between attacks
	SDState state;
	TileMap* map;
	int current_step;	//current step of the pattern
	int current_frames;	//number of frames in the current step
	std::vector<Stepss> pattern;
	std::vector<BubbleFromPlayer*> bubbles;
	float jumpCooldownTimer = 0;
	float jumpCooldownDuration = 1.0f; 
	SDdir direction = SDdir::NE;
};

