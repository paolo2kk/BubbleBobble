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
	return (Tile::STATIC_FIRST <= tile && tile <= Tile::STATIC_LAST || tile == Tile::BLOCKWITH3 || tile == Tile::BLOCKWITHOUT3);
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST || tile == Tile::CORNER || tile == Tile::PLATFORMCORNERRIGHT || tile == Tile::PLATFORMLVL2 ||
		   tile == Tile::CORNERPLATFORMLVL2 || tile == Tile::PLATFORMDEDOS);
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
	return (tile == Tile::PLATFORMMIDDLEFINISH || tile == Tile::FLOORLVL2LEFT);
}
bool TileMap::IsTileHalfCubeLeft(Tile tile) const
{
	return (tile == Tile::PLATFORMEND || tile == Tile::ULTIMAPLATFORMLVL2);
}
bool TileMap::IsTileHalfCubeLeftDEBUG(Tile tile) const
{
	return (tile == Tile::PLATFORMMIDDLESTART || tile == Tile::FLOORLVL2RIGHT) ;
}
bool TileMap::IsTileHalfWallLeft(Tile tile) const
{
	return (tile == Tile::HALWALLLEFTLVL2);
}
bool TileMap::IsTileHalfWallRight(Tile tile) const
{
	return (tile == Tile::HALFWALLRIGHTLVL2);

}
bool TileMap::IsTileFloor(Tile tile) const
{
	return (Tile::FLOOR_FIRST <= tile && tile <= Tile::FLOOR_LAST || tile == Tile::FLOORLVL2 || tile == Tile::CORNERFLOORLVL2);
}
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
		*py = tile_y * TILE_SIZE + TILE_SIZE / 2;
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
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance(); 
	data.ReleaseTexture(Resource::IMG_TILES);

	laser->Release();

	dict_rect.clear();
}