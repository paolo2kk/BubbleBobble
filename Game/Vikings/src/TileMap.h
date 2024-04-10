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

	// 0 < id < 50: static tiles
	BLOCKWITH1 = 1, BLOCKWITHOUT1, CORNER,  SHADOW , SHADOW2, SHADOW3, SHADOW4, SHADOW5, SHADOW6, SHADOW7,
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
	PLAYER = 100,

	//Intervals
	STATIC_FIRST = BLOCKWITH1,
	STATIC_LAST = BLOCKWITHOUT1,
	SOLID_FIRST = PLATFORMBASIC,
	SOLID_LAST = PLATFORMCORNERRIGHT,
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
	bool IsTileFloor(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;

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

enum class UI_elements {
	NT = 0,

	EXCL_W, QM_W, HT_W, DOLARSIGN_W, PERCENT_W, AND_W, APOSTROPHE_W, PARENTHESIS_LEFT_W, PARENTHESIS_RIGHT_W, MULT_W, PLUS_W, COMA_W, MINUS_W, DOT_W, SLASH_W, ZERO_W, ONE_W, TWO_W, THREE_W, FOUR_W, FIVE_W, SIX_W, SEVEN_W, EIGHT_W, NINE_W, TWO_POINTS_W, DOT_COMA_W, SMALLER_THAN_W, EQUAL_W, GREATER_THAN_W, QMARK_W, COPYR_W, A_W, B_W, C_W, D_W, E_W, F_W, G_W, H_W, I_W, J_W, K_W, L_W, M_W, N_W, O_W, P_W, Q_W, R_W, S_W, T_W, U_W, V_W, W_W, X_W, Y_W, Z_W, CORX_LEFT_W, CORX_RIGHT_W,
	EXCL_G, QM_G, HT_G, DOLARSIGN_G, PERCENT_G, AND_G, APOSTROPHE_G, PARENTHESIS_LEFT_G, PARENTHESIS_RIGHT_G, MULT_G, PLUS_G, COMA_G, MINUS_G, DOT_G, SLASH_G, ZERO_G, ONE_G, TWO_G, THREE_G, FOUR_G, FIVE_G, SIX_G, SEVEN_G, EIGHT_G, NINE_G, TWO_POINTS_G, DOT_COMA_G, SMALLER_THAN_G, EQUAL_G, GREATER_THAN_G, QMARK_G, COPYR_G, A_G, B_G, C_G, D_G, E_G, F_G, G_G, H_G, I_G, J_G, K_G, L_G, M_G, N_G, O_G, P_G, Q_G, R_G, S_G, T_G, U_G, V_G, W_G, X_G, Y_G, Z_G, CORX_LEFT_G, CORX_RIGHT_G,
	EXCL_B, QM_B, HT_B, DOLARSIGN_B, PERCENT_B, AND_B, APOSTROPHE_B, PARENTHESIS_LEFT_B, PARENTHESIS_RIGHT_B, MULT_B, PLUS_B, COMA_B, MINUS_B, DOT_B, SLASH_B, ZERO_B, ONE_B, TWO_B, THREE_B, FOUR_B, FIVE_B, SIX_B, SEVEN_B, EIGHT_B, NINE_B, TWO_POINTS_B, DOT_COMA_B, SMALLER_THAN_B, EQUAL_B, GREATER_THAN_B, QMARK_B, COPYR_B, A_B, B_B, C_B, D_B, E_B, F_B, G_B, H_B, I_B, J_B, K_B, L_B, M_B, N_B, O_B, P_B, Q_B, R_B, S_B, T_B, U_B, V_B, W_B, X_B, Y_B, Z_B, CORX_LEFT_B, CORX_RIGHT_B,
	EXCL_R, QM_R, HT_R, DOLARSIGN_R, PERCENT_R, AND_R, APOSTROPHE_R, PARENTHESIS_LEFT_R, PARENTHESIS_RIGHT_R, MULT_R, PLUS_R, COMA_R, MINUS_R, DOT_R, SLASH_R, ZERO_R, ONE_R, TWO_R, THREE_R, FOUR_R, FIVE_R, SIX_R, SEVEN_R, EIGHT_R, NINE_R, TWO_POINTS_R, DOT_COMA_R, SMALLER_THAN_R, EQUAL_R, GREATER_THAN_R, QMARK_R, COPYR_R, A_R, B_R, C_R, D_R, E_R, F_R, G_R, H_R, I_R, J_R, K_R, L_R, M_R, N_R, O_R, P_R, Q_R, R_R, S_R, T_R, U_R, V_R, W_R, X_R, Y_R, Z_R, CORX_LEFT_R, CORX_RIGHT_R,
	EXCL_Y, QM_Y, HT_Y, DOLARSIGN_Y, PERCENT_Y, AND_Y, APOSTROPHE_Y, PARENTHESIS_LEFT_Y, PARENTHESIS_RIGHT_Y, MULT_Y, PLUS_Y, COMA_Y, MINUS_Y, DOT_Y, SLASH_Y, ZERO_Y, ONE_Y, TWO_Y, THREE_Y, FOUR_Y, FIVE_Y, SIX_Y, SEVEN_Y, EIGHT_Y, NINE_Y, TWO_POINTS_Y, DOT_COMA_Y, SMALLER_THAN_Y, EQUAL_Y, GREATER_THAN_Y, QMARK_Y, COPYR_Y, A_Y, B_Y, C_Y, D_Y, E_Y, F_Y, G_Y, H_Y, I_Y, J_Y, K_Y, L_Y, M_Y, N_Y, O_Y, P_Y, Q_Y, R_Y, S_Y, T_Y, U_Y, V_Y, W_Y, X_Y, Y_Y, Z_Y, CORX_LEFT_Y, CORX_RIGHT_Y
};

class UI {
private:

	UI_elements* scene;
	UI_elements GetTileIndex(int x, int y) const;
	int size, width, height;
	std::unordered_map<int, Rectangle> dict_rect;
	const Texture2D* Letters;
	void InitUIDictionary();

public:

	UI();
	~UI();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	Sprite* Title;

	void Update();
	void Render();
	void Release();

};