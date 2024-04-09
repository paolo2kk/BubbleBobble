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
	const int n = TILE_SIZE_WIDTH;
	const int p = TILE_SIZE_HEIGHT;


	dict_rect[(int)Tile::LVL1WALL] = { 0,  0, n, p };
	dict_rect[(int)Tile::LVL1WALLSHADOW] = { n,  0, n, p };
	dict_rect[(int)Tile::LVL1CEILING] = { n*2,  0, n, p };
	dict_rect[(int)Tile::LVL1WALL2] = { 0,  p, n, p };
	dict_rect[(int)Tile::LVL1WALL3] = { 0,  2*p, n, p };
	dict_rect[(int)Tile::LVL1WALL4] = { 0,  3*p, n, p };
	dict_rect[(int)Tile::LVL1WALL5] = { 0,  4*p, n, p };
	dict_rect[(int)Tile::LVL1WALL6] = { 0,  5*p, n, p };
	dict_rect[(int)Tile::LVL1WALL7] = { 0,  6 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL8] = { 0,  7 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL9] = { 0,  8 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL10] = { 0,  9 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL11] = { 0,  10 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL12] = { 0,  11 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL13] = { 0,  12 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL14] = { 0,  13 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL15] = { 0,  14 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL16] = { 0,  15 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL17] = { 0,  16 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL18] = { 0,  17 * p, n, p };
	dict_rect[(int)Tile::LVL1WALL19] = { 0,  18 * p, n, p };
	dict_rect[(int)Tile::LVL1FLOOR] = { 2*n,  18 * p  , n, p  };
	dict_rect[(int)Tile::LVL1SHADOW] = { n,  n , n, p };
	dict_rect[(int)Tile::LVL1FLOORDEBUGEAO] = { n,  18 * p  , n, p };

	dict_rect[(int)Tile::PLATFORM1] = { n,  7 * p + 3 , n, p + 1 };
	dict_rect[(int)Tile::PLATFORM2] = { 2* n,  7 * p + 3  , n + 2, p + 7};
	dict_rect[(int)Tile::PLATFORM2V2] = { 2 * n,  7 * p + 3  , n + 1, p  };
	dict_rect[(int)Tile::PLATFORM1PATTERNDOS] = {  n,  20 * p + 4 , n, p };
	dict_rect[(int)Tile::PLATFORM3] = {4 * n  ,  7 * p + 2, n, p + 4 };
	dict_rect[(int)Tile::SHADOWOFTHECOLOSSUS] = { 3 * n + 8 ,  7 * p + 2, n , p + 4};

}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "images/MAP1full.png") != AppStatus::OK)
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
	//laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME0]);
	//laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME1]);
	//laser->AddKeyFrame(0, dict_rect[(int)Tile::LASER_FRAME2]);
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
	int idx = x + y*width;
	if(idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
		return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
bool TileMap::IsTilePlatform(Tile tile) const 
{
	return (Tile::PLATFORM_FIRST <= tile && tile <= Tile::PLATFORM_LAST);
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int *py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE_HEIGHT;

		*py = tile_y * TILE_SIZE_HEIGHT + 1;
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
	x = p.x / TILE_SIZE_WIDTH;
	y0 = p.y / TILE_SIZE_WIDTH;
	y1 = (p.y + distance - 1) / TILE_SIZE_WIDTH;
	
	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE_HEIGHT;
	x0 = p.x / TILE_SIZE_WIDTH;
	x1 = (p.x + distance - 1) / TILE_SIZE_WIDTH;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTilePlatform(tile))
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
				pos.x = (float)j * TILE_SIZE_WIDTH;
				pos.y = (float)i * TILE_SIZE_HEIGHT;

				if (tile == tile)
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