#pragma once
#include "Entity.h"
#include "TileMap.h"

#define BUBBLE_FRAME_SIZE 16

#define BUBBLE_PHYSICAL_WIDTH	16
#define BUBBLE_PHYSICAL_HEIGHT	16

#define BUBBLE_SPEED			2
#define GRAVITY_FORCE			1

enum class BubbleAnim {
	IDLE, NUM_ANIMATIONS
};
enum class States {
	ALIVE, POPPED
};
enum class Looks {
	LEFT, RIGHT
};
class Bubble : public Entity
{

public:
	Bubble(const Point& p, States s, Looks view);
	~Bubble();
	void SetTileMap(TileMap * tilemap);
	void SetAnimation(int id);
	void Update();
	void Render();
	AppStatus Initialise();
	void DrawDebug(const Color& col) const;
	void Release();
private:
	Sprite* render;
	TileMap* map;
	Looks look;
	States state;

};
