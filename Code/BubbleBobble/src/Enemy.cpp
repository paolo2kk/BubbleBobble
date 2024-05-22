#include "Enemy.h"
#include "Sprite.h"

Enemy::Enemy(const Point& p, int width, int height, int frame_width, int frame_height) :
	Entity(p, width, height, frame_width, frame_height)
{
	visibility_area = {};
	look = Look::LEFT;
}
Enemy::~Enemy()
{
}
bool Enemy::IsVisible(const AABB& hitbox)
{
	//Does the enemy's visibility area intersect with the hitbox?
	if (visibility_area.TestAABB(hitbox))
	{
		//Is the enemy facing the hitbox?
		//We consider it not visible when the boxes are colliding
		if (look == Look::LEFT)
		{
			if (pos.x > hitbox.pos.x + hitbox.width)	return true;
		}
		else if (look == Look::RIGHT)
		{
			if (pos.x + width < hitbox.pos.x)	return true;
		}
	}
	return false;
}
void Enemy::DrawVisibilityArea(const Color& col) const
{
	DrawRectangleLines(visibility_area.pos.x, visibility_area.pos.y, visibility_area.width, visibility_area.height, col);
}