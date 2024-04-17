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
	EMPTY = -1,
	AIR = 0,

	// 0 < id < 50: static tiles
	BLOCKWITH1 = 1, BLOCKWITHOUT1, CORNER, SHADOW, SHADOW2, SHADOW3, SHADOW4, SHADOW5, SHADOW6, SHADOW7,
	PLATFORMBASIC, PLATFORMBEGINNING, PLATFORMEND, PLATFORMCORNERRIGHT = 16, PLATFORMMIDDLESTART, PLATFORMMIDDLEFINISH,
	SHADOWDOWN, SHADOWOTRA, SHADOWOTRA2,
	LADDER_L = 22, LADDER_R, LADDER_TOP_L, LADDER_TOP_R,
	LOCK_RED = 30, LOCK_YELLOW,
	LASER_L = 40, LASER_R, FLOOR, FLOORSTART,

	// 50 <= id < 100: special tiles
	DOOR = 50,
	KEY_RED = 60, YELLOW_KEY, ITEM_APPLE, ITEM_CHILI,
	LASER = 70, LASER_FRAME0, LASER_FRAME1, LASER_FRAME2,

	// id >= 100: entities' initial locations
	PLAYER = 100, BUBBLE, BUBBLE2,

	//second level tiles
	BLOCKWITH3 = 150, BLOCKWITHOUT3, PLATFORMLVL2, PLATFORMCORNERRIGHTLVL2, 
	PLATFORMCORNERLEFTLVL2,  FLOORLVL2, FLOORLVL2RIGHT, FLOORLVL2LEFT,
	CORNERPLATFORMLVL2, CORNERFLOORLVL2, HALFWALLRIGHTLVL2, HALWALLLEFTLVL2,  
	//SHADOWMANAGEMENTLVL2
	SHADOWLVL2, LILSHADOWLVL2, CORNERSHADOWLVL2, LILSHADOWRIGHTLVL2, FLOORSHADOWBOTTOMLVL2, PLATFORMSHADOWWALLLVL2,
	PLATFORMDEDOS, ASHADOWLVL2, ULTIMAPLATFORMLVL2,

	DEBUG_WARP_1, DEBUG_WARP_2,

	//Intervals
	STATIC_FIRST = BLOCKWITH1,
	STATIC_LAST = BLOCKWITHOUT1,
	SOLID_FIRST = PLATFORMBASIC,
	SOLID_LAST = PLATFORMBASIC,
	HALF_FIRST = PLATFORMBEGINNING,
	HALF_LAST = PLATFORMBEGINNING,
	FLOOR_FIRST = FLOOR,
	FLOOR_LAST = FLOORSTART,
	SPECIAL_FIRST = DOOR,
	SPECIAL_LAST = LASER,
	ENTITY_FIRST = PLAYER,
	ENTITY_LAST = PLAYER,
	LASER_FIRST = LASER,
	LASER_LAST = LASER_FRAME2
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

	bool TestCollisionHalfWallLeft(const AABB& box) const;

	bool TestCollisionHalfWallRight(const AABB& box) const;

	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int* py) const;

	bool TestCollisionHead(const AABB& box, int* posY) const;

	bool TestCollisionLaser(const AABB& box, int* posY) const;

	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileStatic(Tile tile) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLaser(Tile tile) const;
	bool IsTileMario(Tile tile) const;
	bool IsTileHalfCubeRight(Tile tile) const;
	bool IsTileHalfCubeRightDEBUG(Tile tile) const;
	bool IsTileHalfCubeLeft(Tile tile) const;
	bool IsTileHalfCubeLeftDEBUG(Tile tile) const;
	bool IsTileHalfWallLeft(Tile tile) const;
	bool IsTileHalfWallRight(Tile tile) const;
	bool IsTileFloor(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionXHalfLeft(const Point& p, int distance) const;
	bool CollisionXHalfRight(const Point& p, int distance) const;
	bool CollisionXFLOOR(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;

	bool CollisionYHalfRight(const Point& p, int distance) const;

	bool CollisionYHalfLeft(const Point& p, int distance) const;

	bool CollisionYHalfRightDEBUG(const Point& p, int distance) const;

	bool CollisionYHalfLeftDEBUG(const Point& p, int distance) const;

	bool CollisionYFLOOR(const Point& p, int distance) const;




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

