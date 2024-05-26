#pragma once
#include "Entity.h"


enum class ProjectileType { 
	
};

class Projectile : public Entity
{
public:
	Projectile(const Point& p);
	void SetAnimation(int id);
	~Projectile();

	void Release();

	bool pastTime(float time);

	void DrawDebug(const Color& col) const;
	float framecounter;

private:
	ProjectileType type;

};
