#pragma once
#include <raylib.h>
#include "Point.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "AABB.h"
#include "Sprite.h"
enum class Look { RIGHT, LEFT };

enum class Animations
{
	ZENCHAN_WALK_R,
	ZENCHAN_WALK_L,
	ZENCHAN_ANGRY_WALK_R,
	ZENCHAN_ANGRY_WALK_L,
	ZENCHAN_DEATH,
	ZENCHAN_BUBBLE_BLUE,
	ZENCHAN_BUBBLE_GREEN,

	PULPUL_FLY,
	PULPUL_ANGRY_FLY,
	PULPUL_DEATH,
	PULPUL_BUBBLE_BLUE,
	PULPUL_BUBBLE_GREEN,

	BENEBOU_WALK_R,
	BENEBOU_WALK_L,
	BENEBOU_ANGRY_WALK_R,
	BENEBOU_ANGRY_WALK_L,
	BENEBOU_DEATH,
	BENEBOU_BUBBLE_BLUE,
	BENEBOU_BUBBLE_GREEN,

	HIDEGONS_WALK_R,
	HIDEGONS_WALK_L,
	HIDEGONS_SPECIAL_R,
	HIDEGONS_SPECIAL_L,
	HIDEGONS_ANGRY_WALK_R,
	HIDEGONS_ANGRY_WALK_L,
	HIDEGONS_ANGRY_SPECIAL_R,
	HIDEGONS_ANGRY_SPECIAL_L,
	HIDEGONS_DEATH,
	HIDEGONS_BUBBLE_BLUE,
	HIDEGONS_BUBBLE_GREEN,
	HIDEGONS_FIRE_R,
	HIDEGONS_FIRE_L,
	HIDEGONS_FIRE_ANGRY_R,
	HIDEGONS_FIRE_ANGRY_L,

	DRUNK_WALK_R,
	DRUNK_WALK_L,
	DRUNK_ANGRY_WALK_R,
	DRUNK_ANGRY_WALK_L,
	DRUNK_DRINK_R,
	DRUNK_DRINK_L,
	DRUNK_DRINK_ANGRY_R,
	DRUNK_DRINK_ANGRY_L,
	DRUNK_DEATH,
	DRUNK_BUBBLE_BLUE,
	DRUNK_BUBBLE_GREEN,
	DRUNK_PROJECTILE,

	SKEL_MONSTA_SPAWN,
	SKEL_MONSTA_WALK_R,
	SKEL_MONSTA_WALK_L,
	SKEL_MONSTA_DEATH,
	SKEL_MONSTA_BUBBLE_BLUE,
	SKEL_MONSTA_BUBBLE_GREEN,

	BUB_WALK_R,
	BUB_WALK_L,
	BUB_ATACK_R,
	BUB_ATACK_L,
	BUB_JUMP_R,
	BUB_JUMP_L,
	BUB_FALL_R,
	BUB_FALL_L,
	BUB_SQUISH_R,
	BUB_SQUISH_L,
	BUB_SQUASH_R,
	BUB_SQUASH_L,
	BUB_DEATH,
	BUB_PUSH_BUTTON,
	BUB_FIRE_DEATH,
	BUB_LEVEL_TRANSITION,

	BOB_WALK_R,
	BOB_WALK_L,
	BOB_ATACK_R,
	BOB_ATACK_L,
	BOB_JUMP_R,
	BOB_JUMP_L,
	BOB_FALL_R,
	BOB_FALL_L,
	BOB_SQUISH_R,
	BOB_SQUISH_L,
	BOB_SQUASH_R,
	BOB_SQUASH_L,
	BOB_DEATH,
	BOB_PUSH_BUTTON,
	BOB_FIRE_DEATH,
	BOB_LEVEL_TRANSITION,

	BUBBLE,

	NUM_ANIMATIONS
};

class Entity
{
public:

	Entity(){isAlive = false;}
	Entity(const Point& p, int width, int height);
	Entity(const Point& p, int width, int height, int frame_width, int frame_height);
	virtual ~Entity();
	
	AppStatus Initialize();

	void Set(const Point& p, const Point& d, int w, int h, int framew, int frameh);
	void SetPos(const Point& p);
	
	void SetAlive(bool b);
	bool IsAlive() const;
	void Update();
	AABB GetHitbox() const;

	//Draw representation model
	void Draw() const;
	void Warp();
	void DrawTint(const Color& col) const;
	
	//Draw logical/physical model (hitbox)
	void DrawHitbox(const Color& col) const;
	void DrawHitbox(int x, int y, int w, int h, const Color& col) const;
	Point GetPos();
protected:
	Point GetRenderingPosition() const;
	bool isAlive;

	const Texture2D* img_animations;
	RenderComponent* render_;

	//Logical/physical model
	Point pos, dir;
	int width, height;				
	float eFrame = 0;
	float maxSeconds = 1;
	//Representation model
	int frame_width, frame_height;
	RenderComponent *render;
};