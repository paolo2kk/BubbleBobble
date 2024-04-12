#pragma once
#include <raylib.h>
#include "Point.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "AABB.h"

class Entity
{
public:
	Entity();
	Entity(const Point& p, int width, int height);
	Entity(const Point& p, int width, int height, int frame_width, int frame_height);
	virtual ~Entity();

	void SetPos(const Point& p);
	void Update();
	AABB GetHitbox() const;
	void Init(const Point& p, int w, int h);
	//Draw representation model
	void Draw() const;
	void DrawTint(const Color& col) const;
	
	//Draw logical/physical model (hitbox)
	void DrawHitbox(const Color& col) const;
	void DrawHitbox(int x, int y, int w, int h, const Color& col) const;
	bool isAlive = false;

protected:
	Point GetRenderingPosition() const;

	//Logical/physical model
	Point pos, dir;
	int width, height, speed;				

	//Representation model
	int frame_width, frame_height;

	RenderComponent *render;
};