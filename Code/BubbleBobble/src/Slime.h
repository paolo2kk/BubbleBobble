#pragma once
#include "Enemy.h"
#include "TileMap.h"
#include "BubbleFromPlayer.h"

#define SLIME_SPEED			1
#define SLIME_ANIM_DELAY	(2 * ANIM_DELAY)

#define SLIME_SHOT_OFFSET_X_LEFT	-14
#define SLIME_SHOT_OFFSET_X_RIGHT	 26
#define SLIME_SHOT_OFFSET_Y			-22

#define SLIME_SHOT_SPEED	4

enum class SlimeState { ROAMING, ATTACK, FALLING, JUMPING };
enum class SlimeAnim {
	IDLE_LEFT, IDLE_RIGHT, WALKING_LEFT, WALKING_RIGHT,
	ATTACK_LEFT, ATTACK_RIGHT, NUM_ANIMATIONS
};

struct Step
{
	Point speed;	//direction
	int frames;		//duration in number of frames
	int anim;		//graphical representation
};

class Slime : public Enemy
{
public:
	Slime(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* map);
	~Slime();

	//Initialize the enemy with the specified look and area
	AppStatus Initialise(Look look, const AABB& area) override;

	void BubbleSetter(BubbleFromPlayer* bub);

	//Update the enemy according to its logic, return true if the enemy must shoot
	bool Update(const AABB& box) override;


	//Retrieve the position and direction of the shot to be thrown
	void GetShootingPosDir(Point* pos, Point* dir) const override;
	EnemyType GetEnemyType() const;

private:
	//Create the pattern behaviour
	float eTimeLerp = 0;
	void MoveX();
	void SetAnimation(int id);
	void MoveY();
	void StartFalling();
	void Stop();
	//Update looking direction according to the current step of the pattern
	void UpdateLook(int anim_id);
	bool defusehitbox = false;
	bool hasAlreadyJumped = false;
	int attack_delay;	//delay between attacks
	SlimeState state;
	TileMap* map;
	int current_step;	//current step of the pattern
	int current_frames;	//number of frames in the current step
	std::vector<Step> pattern;
	std::vector<BubbleFromPlayer*> bubbles;
};

