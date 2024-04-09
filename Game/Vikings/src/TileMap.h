#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {

	//  0: empty tile
	// -1: area covered by entity
	AIR = 0,

	// 0 < id < 50: solid tiles
	LVL1WALL = 1, LVL1WALL2 = 4, LVL1WALL3, LVL1WALL4, LVL1WALL5, LVL1WALL6, LVL1WALL7, LVL1WALL8, LVL1WALL9, 
	LVL1WALL10, LVL1WALL11, LVL1WALL12, LVL1WALL13, LVL1WALL14, LVL1WALL15, LVL1WALL16, LVL1WALL17, LVL1WALL18, LVL1WALL19,
	LVL1FLOORDEBUGEAO, LVL1FLOOR, PLATFORM1, PLATFORM1PATTERNDOS, PLATFORM3, SHADOWOFTHECOLOSSUS, PLATFORM2, PLATFORM2V2,
	PLACEHOLDER,
	
	// 50 <= id < 100: static tiles
	 LVL1SHADOW = 50, LVL1CEILING, LVL1WALLSHADOW,
	// id >= 100: entities' initial locations
	PLAYER = 100,

	//Intervals
	SOLID_FIRST = LVL1WALL,
	SOLID_LAST = LVL1FLOOR,
	PLATFORM_FIRST = PLATFORM1,
	PLATFORM_LAST = SHADOWOFTHECOLOSSUS,
	STATIC_FIRST = LVL1SHADOW,
	STATIC_LAST = LVL1WALLSHADOW,
	
	/*SPECIAL_FIRST = DOOR,
	SPECIAL_LAST = LASER,*/
	ENTITY_FIRST = PLAYER,
	ENTITY_LAST = PLAYER
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;
	
	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int *py) const;
	
	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;
	

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTilePlatform(Tile tile) const;

	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;

	//Tile map
	Tile *map;

	//Size of the tile map
	int size, width, height;
	
	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite *laser;
	
	//Tile sheet
	const Texture2D *img_tiles;
};

