#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	laser = nullptr;
	img_tiles = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	if (laser != nullptr)
	{
		laser->Release();
		delete laser;
		laser = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

	dict_rect[(int)Tile::BLOCKWITH1] = { 0, n, n, n };
	dict_rect[(int)Tile::BLOCKWITHOUT1] = { 0, 2 * n, n, n };
	dict_rect[(int)Tile::CORNER] = { n, n, n, n };

	dict_rect[(int)Tile::PLATFORMBASIC] = { 2 * n, n, n, n };
	dict_rect[(int)Tile::PLATFORMBEGINNING] = { 3* n, 6 * n, n, n };
	dict_rect[(int)Tile::PLATFORMEND] = { 12 * n, 6 * n, n, n };
	dict_rect[(int)Tile::PLATFORMCORNERRIGHT] = { 14 * n, 6 * n, n, n };
	dict_rect[(int)Tile::PLATFORMMIDDLESTART] = { 3 * n, 8 * n, n, n };
	dict_rect[(int)Tile::PLATFORMMIDDLEFINISH] = { 12 * n, 8 * n, n, n };

	dict_rect[(int)Tile::SHADOW] = { 2 * n, 6 * n, n, n };
	dict_rect[(int)Tile::SHADOW2] = { n, 3 * n, n, n };
	dict_rect[(int)Tile::SHADOW3] = { 2 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOW4] = { 14 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOW5] = { 12 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOW6] = {n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOW7] = { 3 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOWDOWN] = { 4 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOWOTRA] = { 12 * n, 9 * n, n, n };
	dict_rect[(int)Tile::SHADOWOTRA2] = { 2 * n, 8 * n, n, n };

	dict_rect[(int)Tile::FLOOR] = { 3 * n, 13 * n, n, n };
	dict_rect[(int)Tile::FLOORSTART] = { n, 13 * n, n, n };


	dict_rect[(int)Tile::LADDER_L] = { 2 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_R] = { 3 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_TOP_L] = { 4 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LADDER_TOP_R] = { 5 * n, 2 * n, n, n };

	dict_rect[(int)Tile::LOCK_RED] = { 6 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LOCK_YELLOW] = { 7 * n, 2 * n, n, n };

	dict_rect[(int)Tile::LASER_L] = { 0, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_R] = { 4 * n, 6 * n, n, n };
	
	dict_rect[(int)Tile::LASER_FRAME0] = { 1 * n, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_FRAME1] = { 2 * n, 6 * n, n, n };
	dict_rect[(int)Tile::LASER_FRAME2] = { 3 * n, 6 * n, n, n };

	//lvl 2 default Y = 15
	dict_rect[(int)Tile::BLOCKWITH3] = { 0, 15 * n, n, n };
	dict_rect[(int)Tile::BLOCKWITHOUT3] = { 0, 16 * n, n, n };
	dict_rect[(int)Tile::PLATFORMLVL2] = { 2* n, 15 * n, n, n };
	dict_rect[(int)Tile::PLATFORMCORNERRIGHTLVL2] = { 4 * n, 15 * n, n, n };
	dict_rect[(int)Tile::PLATFORMCORNERLEFTLVL2] = { 6 * n, 15 * n, n, n };
	dict_rect[(int)Tile::FLOORLVL2] = { 3 * n, 17 * n, n, n };
	dict_rect[(int)Tile::FLOORLVL2RIGHT] = { 2 * n, 17 * n, n, n };
	dict_rect[(int)Tile::FLOORLVL2LEFT] = { 6 * n, 17 * n, n, n };
	dict_rect[(int)Tile::CORNERPLATFORMLVL2] = { n, 15 * n, n, n };
	dict_rect[(int)Tile::CORNERFLOORLVL2] = { 3 * n, 22 * n, n, n };
	dict_rect[(int)Tile::HALFWALLRIGHTLVL2] = { 2 * n, 18 * n, n, n };
	dict_rect[(int)Tile::HALWALLLEFTLVL2] = { 13 * n, 18 * n, n, n };
	dict_rect[(int)Tile::PLATFORMDEDOS] = { 9 * n, 20 * n, n, n };
	dict_rect[(int)Tile::ULTIMAPLATFORMLVL2] = { 3 * n, 25 * n, n, n };

	dict_rect[(int)Tile::SHADOWLVL2] = { n, 16 * n, n, n };
	dict_rect[(int)Tile::LILSHADOWLVL2] = { 6 * n, 18 * n, n, n };
	dict_rect[(int)Tile::CORNERSHADOWLVL2] = { 3 * n, 18 * n, n, n };
	dict_rect[(int)Tile::LILSHADOWRIGHTLVL2] = { 9 * n, 18 * n, n, n };
	dict_rect[(int)Tile::FLOORSHADOWBOTTOMLVL2] = { 5 * n, 18 * n, n, n };
	dict_rect[(int)Tile::PLATFORMSHADOWWALLLVL2] = { 7 * n, 20 * n, n, n };
	dict_rect[(int)Tile::ASHADOWLVL2] = { 6 * n, 25 * n, n, n };
	dict_rect[(int)Tile::DEBUG_WARP_1] = { 2 * n, 15 * n, n, n };
	dict_rect[(int)Tile::DEBUG_WARP_2] = { 6 * n, 15 * n, n, n };
	dict_rect[(int)Tile::DEBUG_CEILINGLVL1] = { 2 * n, n, n, n };
	
	//lvl 3
	dict_rect[(int)Tile::BLOCKWITH30] = {  0, 29 * n, n, n };
	dict_rect[(int)Tile::BLOCKWITHOUT30] = { 0, 30 * n, n, n };
	dict_rect[(int)Tile::CORNERFLOOR30] = { n, 41 * n, n, n };
	dict_rect[(int)Tile::FLOOR30] = { 2* n, 41 * n, n, n };
	dict_rect[(int)Tile::FLOOR30L] = { 4 * n, 41 * n, n, n };
	dict_rect[(int)Tile::FLOOR30R] = { 6 * n, 41 * n, n, n };
	dict_rect[(int)Tile::FLOOR30WSHADOWL] = { n * 2, 33 * n, n, n };
	dict_rect[(int)Tile::FLOOR30WSHADOWR] = { n * 4, 33 * n, n, n };
	dict_rect[(int)Tile::WALLNOSHADE30] = { n * 4, 31 * n, n, n };
	dict_rect[(int)Tile::WALLWSHADETOP30] = { n * 2, 31 * n, n, n };
	dict_rect[(int)Tile::WALLWSHADE30] = { n * 2, 32 * n, n, n };

	//lvl3 shades
	dict_rect[(int)Tile::WALLSHADE_30] = { n, 30 * n, n, n };
	dict_rect[(int)Tile::WALLSHADETOP_30] = { 5* n, 31 * n, n, n };
	dict_rect[(int)Tile::PLATSHADE30FIRST] = { 2 * n, 34 * n, n, n };
	dict_rect[(int)Tile::PLATSHADE30] = { 3 * n, 34 * n, n, n };
	dict_rect[(int)Tile::PLATSHADE30CORNER] = { 5 * n, 34 * n, n, n };
	dict_rect[(int)Tile::PLAT2SHADE30FIRST] = { 6 * n, 34 * n, n, n };
	dict_rect[(int)Tile::PLAT2SHADE30LAST] = { 9 * n, 34 * n, n, n };

	//lvl3 debugs
	dict_rect[(int)Tile::DEBUG_WARP_30] = { n, 29 * n, n, n };
	dict_rect[(int)Tile::DEBUG_CEILINGLVL30] = { 2* n, 29 * n, n, n };
	dict_rect[(int)Tile::DEBUG30L] = { 4 * n, 29 * n, n, n };
	dict_rect[(int)Tile::DEBUG30R] = { 6 * n, 29 * n, n, n };

	//l4 Tiles

	dict_rect[(int)Tile::BLOCKWALL4] = { 0, 44 * n, n, n };
	dict_rect[(int)Tile::BLOCKWALL4NUMBER] = { 0, 43 * n, n, n };
	dict_rect[(int)Tile::CORNER_PLATAFORM4] = { n, 43 * n, n, n };
	dict_rect[(int)Tile::PLATAFORM_SHADOW4] = { n * 2, 43 * n, n, n };
	dict_rect[(int)Tile::DEBUGLVL4] = { n * 2, 43 * n, n, n };

	dict_rect[(int)Tile::WALL_SHADOW4] = { n, 44 * n, n, n };
	dict_rect[(int)Tile::WALL_PLATAFORM4] = { n, 45 * n, n, n };
	dict_rect[(int)Tile::PLATAFORM4] = { n * 2, 45 * n, n, n };
	dict_rect[(int)Tile::CORNER_SHADOW4] = { n , 46 * n, n, n };
	dict_rect[(int)Tile::BOTTOM_SHADW4] = { n * 2 , 46 * n, n, n };
	dict_rect[(int)Tile::DRUNKCartel] = { n , 56 * n, n * 13, n * 3 };

	//drunk level
	dict_rect[(int)Tile::YESYESYESNO] = { n , 57* n, n, n };
	dict_rect[(int)Tile::WALLSHADEDRUNK] = { n , 58 * n, n, n };
	dict_rect[(int)Tile::NOYESNOYES] = { n * 2 , 58 * n, n, n };
	dict_rect[(int)Tile::NOYESNONO] = { n * 2 , 59 * n, n, n };
	dict_rect[(int)Tile::ThatOne] = { n * 3 , 58 * n, n, n };
	dict_rect[(int)Tile::NOYESYESYES] = { n * 3 , 59 * n, n, n };
	dict_rect[(int)Tile::YESNOYESNO] = { n * 5 , 58 * n, n, n };
	dict_rect[(int)Tile::YESYESNOYES] = { n * 5 , 57 * n, n, n };
	dict_rect[(int)Tile::YESNONOYES2] = { 10 * n , 58 * n, n, n };
	dict_rect[(int)Tile::FINALY] = { 13 * n , 57 * n, n, n };

	//boss level
	dict_rect[(int)Tile::BLOCK100] = { 16 * n, n, n, n };
	dict_rect[(int)Tile::BLOCKNO100] = { 16 * n, 2* n, n, n };
	dict_rect[(int)Tile::SHADEW100] = { 17 * n, 2 * n, n, n };
	dict_rect[(int)Tile::CORNERARRIBAIZQ] = { 17 * n, n, n, n };
	dict_rect[(int)Tile::CORNERABAJOIZQ] = { 17 * n, 13 * n, n, n };
	dict_rect[(int)Tile::FLOOR100] = { 18 * n, 13 * n, n, n };
	dict_rect[(int)Tile::CEILING100] = { 18 * n,  n, n, n };
	dict_rect[(int)Tile::NONONOYES100] = { 20 * n, 3* n, n, n };
	dict_rect[(int)Tile::SHADE100] = { 20 * n, 4 * n, n, n };
	dict_rect[(int)Tile::SHADE2100] = { 21 * n, 4 * n, n, n };
	dict_rect[(int)Tile::NONOYESNO100] = { 21 * n, 3 * n, n, n };
	dict_rect[(int)Tile::PLAT100] = { 19 * n, 6 * n, n, n };
	dict_rect[(int)Tile::NOYESNONO100] = { 23 * n, 6 * n, n, n };
	dict_rect[(int)Tile::YESNONONO100] = { 24 * n, 6 * n, n, n };
	dict_rect[(int)Tile::SHADE3100] = { 29 * n, 6 * n, n, n };

}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "images/tilesLVL1.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	if (data.LoadTexture(Resource::IMG_TILES2, "images/dos.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	if (data.LoadTexture(Resource::IMG_BONUS, "images/tileset.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	img_tiles = data.GetTexture(Resource::IMG_TILES);

	laser = new Sprite(img_tiles);
	if (laser == nullptr)
	{
		LOG("Failed to allocate memory for laser sprite");
		return AppStatus::ERROR;
	}
	laser->SetNumberAnimations(1);
	laser->SetAnimationDelay(0, ANIM_DELAY);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME0]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME1]);
	laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME2]);
	laser->SetAnimation(0);

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w*h;
	width = w;
	height = h;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)	
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
	laser->Update();
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	if (this != nullptr) {
		int idx = x + y * width;
		if (idx < 0 || idx >= size)
		{
			LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
				return Tile::AIR;
		}
		return map[x + y * width];
	}
	
}
bool TileMap::IsTileStatic(Tile tile) const
{
	return (Tile::STATIC_FIRST <= tile && tile <= Tile::STATIC_LAST || tile == Tile::BLOCKWITH3 || tile == Tile::BLOCKWITHOUT3 ||
		tile == Tile::BLOCKWITH30 || tile == Tile::BLOCKWITHOUT30 || tile == Tile::BLOCKWALL4 || tile == Tile::BLOCKWALL4NUMBER);
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST || tile == Tile::CORNER || tile == Tile::PLATFORMCORNERRIGHT || tile == Tile::PLATFORMLVL2 ||
		tile == Tile::CORNERPLATFORMLVL2 || tile == Tile::PLATFORMDEDOS || tile == Tile::CORNER_PLATAFORM4 || tile == Tile::PLATAFORM_SHADOW4);
}
bool TileMap::IsTileLaser(Tile tile) const
{
	return (Tile::LASER_FIRST <= tile && tile <= Tile::LASER_LAST);
}
bool TileMap::IsTileMario(Tile tile) const
{
	return (tile == Tile::LOCK_RED);
}
bool TileMap::IsTileHalfCubeRight(Tile tile) const
{
	return (Tile::HALF_FIRST <= tile && tile <= Tile::HALF_LAST || tile == Tile::PLATFORMCORNERLEFTLVL2);
}
bool TileMap::IsTileHalfCubeRightDEBUG(Tile tile) const
{
	return (tile == Tile::PLATFORMMIDDLEFINISH || tile == Tile::FLOORLVL2LEFT || tile == Tile::FLOOR30L);
}
bool TileMap::IsTileHalfCubeLeft(Tile tile) const
{
	return (tile == Tile::PLATFORMEND || tile == Tile::ULTIMAPLATFORMLVL2);
}
bool TileMap::IsTileHalfCubeLeftDEBUG(Tile tile) const
{
	return (tile == Tile::PLATFORMMIDDLESTART || tile == Tile::FLOORLVL2RIGHT || tile == Tile::FLOOR30R);
}
bool TileMap::IsTileHalfWallLeft(Tile tile) const
{
	return (tile == Tile::HALWALLLEFTLVL2) ;
}
bool TileMap::IsTileHalfWallRight(Tile tile) const
{
	return (tile == Tile::HALFWALLRIGHTLVL2 || tile == Tile::WALLNOSHADE30 || tile == Tile::WALLWSHADE30 || tile == Tile::WALLWSHADETOP30);

}
bool TileMap::IsTileAir(Tile tile) const
{
	return (tile == Tile::AIR);

}
bool TileMap::IsTileFloor(Tile tile) const
{
	return (Tile::FLOOR_FIRST <= tile && tile <= Tile::FLOOR_LAST || tile == Tile::FLOORLVL2 || tile == Tile::CORNERFLOORLVL2 || tile == Tile::FLOOR30 || tile == Tile::CORNERFLOOR30
		|| tile == Tile::FLOOR30WSHADOWL || tile == Tile::FLOOR30WSHADOWR || tile == Tile::PLATAFORM4 || tile == Tile::WALL_PLATAFORM4);
}
bool TileMap::IsTileFloorNCeiling(Tile tile) const
{
	return (Tile::FLOOR_FIRST <= tile && tile <= Tile::FLOOR_LAST || tile == Tile::FLOORLVL2 || tile == Tile::CORNERFLOORLVL2 || tile == Tile::PLATFORMBASIC || tile == Tile::PLATFORMLVL2
		|| tile == Tile::CORNER || tile == Tile::CORNER || tile == Tile::PLATFORMCORNERRIGHT || tile == Tile::PLATFORMCORNERLEFTLVL2 || tile == Tile::CORNERPLATFORMLVL2
		|| tile == Tile::FLOOR30 || tile == Tile::CORNERFLOOR30) || IsTileFloor(tile);
}//remember: Add all shader tiles here
bool TileMap::IsTileLadderTop(Tile tile) const
{
	return tile == Tile::LADDER_TOP_L || tile == Tile::LADDER_TOP_R;
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionHalfWallLeft(const AABB& box) const
{
	return CollisionXHalfLeft(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionHalfWallRight(const AABB& box) const
{
	return CollisionXHalfRight(box.pos + Point(box.width - 8, 0), box.height);
}
bool TileMap::TestCollisionAir(const AABB& box) const
{
	return CollisionAir(box.pos + Point(box.width - 8, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int *py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;
	Point pFloor(box.pos.x, box.pos.y + 1);	//control point
	Point p2(box.pos.x - 8, *py);	//control point
	Point p3(box.pos.x + 8, *py);	//control point
	Point p22(box.pos.x - 7, box.pos.y + 1);	//control point
	Point p33(box.pos.x + 7, box.pos.y + 1);	//control point

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE;
		return true;
	}
	else if (CollisionYFLOOR(pFloor, box.width))
	{
		tile_y = p.y / TILE_SIZE;
		*py = tile_y * TILE_SIZE + TILE_SIZE / 2 ;
		return true;
	}
	else if (CollisionYHalfRight(p2, box.width)) 
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE;
		return true;
	}
	else if (CollisionYHalfLeft(p3, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE;
		return true;
	}
	else if (CollisionYHalfRightDEBUG(p33, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE + TILE_SIZE / 2;
		return true;
	}
	else if (CollisionYHalfLeftDEBUG(p22, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE + TILE_SIZE / 2;
		return true;
	}
	return false;
}
bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;
	
	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileMario(GetTileIndex(x, y)) || IsTileStatic(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionXHalfLeft(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileHalfWallLeft(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionXHalfRight(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileHalfWallRight(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionAir(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileAir(GetTileIndex(x, y)) || IsTileFloorNCeiling(GetTileIndex(x,y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTileLadderTop(tile) ||IsTileMario(tile))
			return true;
	}
	return false;
}
bool TileMap::CollisionYHalfRight(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileHalfCubeRight(tile))
			return true;
	}
	return false;
}
bool TileMap::CollisionYHalfLeft(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileHalfCubeLeft(tile))
			return true;
	}
	return false;
}
bool TileMap::CollisionYHalfRightDEBUG(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileHalfCubeRightDEBUG(tile))
			return true;
	}
	return false;
}
bool TileMap::CollisionYHalfLeftDEBUG(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileHalfCubeLeftDEBUG(tile))
			return true;
	}
	return false;
}
bool TileMap::CollisionYFLOOR(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileFloor(tile))
		return true;
	}
	return false;
}
bool TileMap::TestCollisionHead(const AABB& box, int *posY) const
{
	int x, y, x0, x1;
	Tile tile;

	y = (box.pos.y - 1) / TILE_SIZE; 
	x0 = box.pos.x / TILE_SIZE;
	x1 = (box.pos.x + box.width - 1) / TILE_SIZE;

	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		if (tile == Tile::LOCK_RED)
			return true;
	}
	return false;
}
bool TileMap::TestCollisionLaser(const AABB& box, int* posY) const
{
	int x, y, x0, x1;
	Tile tile;

	y = (box.pos.y + 16) / TILE_SIZE; 
	x0 = box.pos.x / TILE_SIZE;

	x1 = (box.pos.x + box.width - 1) / TILE_SIZE;

	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		if (IsTileLaser(tile))
			return true;
	}
	return false;
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				if (tile != Tile::LASER)
				{
					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				}
				else
				{
					laser->Draw((int)pos.x, (int)pos.y);
				}
			}
		}
	}
}
AABB TileMap::GetSweptAreaX(const AABB& hitbox) const
{
	AABB box;
	int column, x, y, y0, y1;
	bool collision;

	box.pos.y = hitbox.pos.y;
	box.height = hitbox.height;

	column = hitbox.pos.x / TILE_SIZE;
	y0 = hitbox.pos.y / TILE_SIZE;
	y1 = (hitbox.pos.y + hitbox.height - 1) / TILE_SIZE;

	//Compute left tile index
	collision = false;
	x = column - 1;
	while (!collision && x >= 0)
	{
		//Iterate over the tiles within the vertical range
		for (y = y0; y <= y1; ++y)
		{
			//One solid tile is sufficient
			if (IsTileSolid(GetTileIndex(x, y)))
			{
				collision = true;
				break;
			}
		}
		if (!collision) x--;
	}
	box.pos.x = (x + 1) * TILE_SIZE;

	//Compute right tile index
	collision = false;
	x = column + 1;
	while (!collision && x < LEVEL_WIDTH)
	{
		//Iterate over the tiles within the vertical range
		for (y = y0; y <= y1; ++y)
		{
			//One solid tile is sufficient
			if (IsTileSolid(GetTileIndex(x, y)))
			{
				collision = true;
				break;
			}
		}
		if (!collision) x++;
	}
	box.width = x * TILE_SIZE - box.pos.x;

	return box;
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance(); 
	data.ReleaseTexture(Resource::IMG_TILES);

	laser->Release();

	dict_rect.clear();
}