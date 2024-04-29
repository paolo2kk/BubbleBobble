#pragma once
#include <array>
#include "Shot.h"
#include "TileMap.h"
#include "ParticleManager.h"

#define MAX_SHOTS		16

class ShotManager
{
public:
	ShotManager();
	~ShotManager();

	AppStatus Initialise();

	//Set the TileMap reference for managing shot collisions
	void SetTileMap(TileMap* tilemap);

	//Set the TileMap reference for managing shot collisions
	void SetParticleManager(ParticleManager* particles);

	//Add a new shot with the given position and direction
	void Add(const Point& pos, const Point& dir);

	//Remove all the shots
	void Clear();

	//Update shot positions and check for collisions with the level and player
	void Update(const AABB& player_hitbox);

	//Draw all active shots
	void Draw() const;
	
	//Draw hitboxes of shots for debugging
	void DrawDebug(const Color& col) const;

private:
	std::array<Shot, MAX_SHOTS> shots;

	//Reference to the TileMap object
	//This class does not own the object, it only holds a reference to it
	TileMap *map;

	//Reference to the TileMap object
	//This class does not own the object, it only holds a reference to it
	ParticleManager *particles;
};

