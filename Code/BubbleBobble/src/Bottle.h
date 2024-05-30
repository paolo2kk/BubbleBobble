#pragma once
#include "Entity.h"


enum class ProjectileType { 
	
};

class Projectile : public Entity
{
public:
	Projectile(const Point& p, Look view);
	Projectile(const Point& p, Look view, bool a);
	void SetAnimation(int id);
	~Projectile();

	void Release();

	void Update();

	void MoveX();

	bool pastTime(float time);

	void DrawDebug(const Color& col) const;
	float framecounter;
	bool isThund = false;
private:
	Look direction;
	ProjectileType type;

};
