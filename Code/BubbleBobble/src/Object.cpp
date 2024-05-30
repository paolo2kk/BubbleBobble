#include "Object.h"
#include "StaticImage.h"
#include <cstdlib>
#include "iostream"

Object::Object(const Point& p) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	P1 = true;
	framecounter = 0;
	Rectangle rc;
	const int n = TILE_SIZE;

	switch (DrawRandObject())
	{
	case ObjectType::BLUE_CANDY: rc = { 0, 0, n, n }; break;
	case ObjectType::CAKE: rc = { n, 0, n, n }; break;
	case ObjectType::DONUT: rc = { 2 * n, 0, n, n }; break;
	case ObjectType::HAMBURGUER: rc = { 3 * n, 0, n, n }; break;
	case ObjectType::HOT_DOG: rc = { 4 * n, 0, n, n }; break;
	case ObjectType::ICE_CREAM: rc = { 5 * n, 0, n, n }; break;
	case ObjectType::PINK_CANDY: rc = { 6 * n, 0, n, n }; break;
	case ObjectType::PIZZA: rc = { 7 * n, 0, n, n }; break;
	case ObjectType::POPSICLE: rc = { 8 * n, 0, n, n }; break;
	case ObjectType::SUSHI: rc = { 9 * n, 0, n, n }; break;
	case ObjectType::YELLOW_CANDY: rc = { 10 * n, 0, n, n }; break;
	case ObjectType::MIQUEL: rc = { 11 * n, 0, n, n }; break;

	case ObjectType::APPLE: rc = { 0, n, n, n }; break;
	case ObjectType::BANANA: rc = { n, n, n, n }; break;
	case ObjectType::CHERRY: rc = { 2 * n, n, n, n }; break;
	case ObjectType::GRAPE: rc = { 3 * n, n, n, n }; break;
	case ObjectType::LEMON: rc = { 4 * n, n, n, n }; break;
	case ObjectType::ORANGE_OBJ: rc = { 5 * n, n, n, n }; break;
	case ObjectType::PEAR: rc = { 6 * n, n, n, n }; break;
	case ObjectType::WATERMELON: rc = { 7 * n, n, n, n }; break;

	default: LOG("Internal error: object creation of invalid type");
	}

	point = false;

	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS), rc);
}
Object::Object(const Point& p, ObjectType obj) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	P1 = true;
	framecounter = 0;
	Rectangle rc;
	const int n = TILE_SIZE;

	switch (obj)
	{

	case ObjectType::DOT:
		rc = { 12 * n, 0, n, n }; break;

	default: LOG("Internal error: object creation of invalid type");
	}

	point = false;

	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS), rc);
}
Object::~Object()
{

}
ObjectType Object::DrawRandObject()
{
	int random = GetRandomValue(0, 19);

	switch (random)
	{
	case 0:
		type = ObjectType::APPLE;
		return ObjectType::APPLE;
		break;
	case 1:
		type = ObjectType::BANANA;
		return ObjectType::BANANA;
		break;
	case 2:
		type = ObjectType::CHERRY;
		return ObjectType::CHERRY;
		break;
	case 3:
		type = ObjectType::GRAPE;
		return ObjectType::GRAPE;
		break;
	case 4:
		type = ObjectType::LEMON;
		return ObjectType::LEMON;
		break;
	case 5:
		type = ObjectType::ORANGE_OBJ;
		return ObjectType::ORANGE_OBJ;
		break;
	case 6:
		type = ObjectType::PEAR;
		return ObjectType::PEAR;
		break;
	case 7:
		type = ObjectType::WATERMELON;
		return ObjectType::WATERMELON;
		break;
	case 8:
		type = ObjectType::BLUE_CANDY;
		return ObjectType::BLUE_CANDY;
		break;
	case 9:
		type = ObjectType::CAKE;
		return ObjectType::CAKE;
		break;
	case 10:
		type = ObjectType::DONUT;
		return ObjectType::DONUT;
		break;
	case 11:
		type = ObjectType::HAMBURGUER;
		return ObjectType::HAMBURGUER;
		break;
	case 12:
		type = ObjectType::HOT_DOG;
		return ObjectType::HOT_DOG;
		break;
	case 13:
		type = ObjectType::ICE_CREAM;
		return ObjectType::ICE_CREAM;
		break;
	case 14:
		type = ObjectType::PINK_CANDY;
		return ObjectType::PINK_CANDY;
		break;
	case 15:
		type = ObjectType::PIZZA;
		return ObjectType::PIZZA;
		break;
	case 16:
		type = ObjectType::POPSICLE;
		return ObjectType::POPSICLE;
		break;
	case 17:
		type = ObjectType::SUSHI;
		return ObjectType::SUSHI;
		break;
	case 18:
		type = ObjectType::YELLOW_CANDY;
		return ObjectType::YELLOW_CANDY;
		break;
	case 19:
		type = ObjectType::MIQUEL;
		return ObjectType::MIQUEL;
		break;

	}
}
void Object::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
int Object::Points() const
{
	if (type == ObjectType::APPLE)		return POINTS_APPLE;
	else if (type == ObjectType::BANANA)	return POINTS_BANANA;
	else if (type == ObjectType::CHERRY)	return POINTS_CHERRY;
	else if (type == ObjectType::GRAPE)	return POINTS_GRAPE;
	else if (type == ObjectType::LEMON)	return POINTS_LEMON;
	else if (type == ObjectType::ORANGE_OBJ)	return POINTS_ORANGE;
	else if (type == ObjectType::PEAR)	return POINTS_PEAR;
	else if (type == ObjectType::WATERMELON)	return POINTS_WATERMELON;
	else if (type == ObjectType::BLUE_CANDY)	return POINTS_BLUE_CANDY;
	else if (type == ObjectType::CAKE)	return POINTS_CAKE;
	else if (type == ObjectType::DONUT)	return POINTS_DONUT;
	else if (type == ObjectType::HAMBURGUER)	return POINTS_HAMBURGUER;
	else if (type == ObjectType::HOT_DOG)	return POINTS_HOT_DOG;
	else if (type == ObjectType::ICE_CREAM)	return POINTS_ICE_CREAM;
	else if (type == ObjectType::PINK_CANDY)	return POINTS_PINK_CANDY;
	else if (type == ObjectType::PIZZA)	return POINTS_PIZZA;
	else if (type == ObjectType::POPSICLE)	return POINTS_POPSICLE;
	else if (type == ObjectType::SUSHI)	return POINTS_SUSHI;
	else if (type == ObjectType::YELLOW_CANDY)	return POINTS_YELLOW_CANDY;
	else if (type == ObjectType::MIQUEL)	return POINTS_MIQUEL;

	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}
void Object::DrawPoints()
{
	Rectangle rc;
	const int n = TILE_SIZE;

	if (P1 == false)
	{
		switch (Points()) {
		case POINTS_APPLE:
			rc = { 21 * n,n * 3, n, n }; break;
			break;
		case POINTS_BANANA:
			rc = { 17 * n,n * 3, n, n }; break;
			break;
		case POINTS_GRAPE:
			rc = { 31 * n,n * 3, n, n }; break;
			break;
		case POINTS_LEMON:
			rc = { 14 * n,n * 3, n, n }; break;
			break;
		case POINTS_ORANGE:
			rc = { 13 * n,n * 3, n, n }; break;
			break;
		case POINTS_PEAR:
			rc = { 18 * n,n * 3, n, n }; break;
			break;
		case POINTS_WATERMELON:
			rc = { 19 * n,n * 3, n, n }; break;
			break;
		case POINTS_BLUE_CANDY:
			rc = { 9 * n,n * 3, n, n }; break;
			break;
		case POINTS_CAKE:
			rc = { 29 * n,n * 3, n, n }; break;
			break;
		case POINTS_DONUT:
			rc = { 27 * n,n * 3, n, n }; break;
			break;
		case POINTS_POPSICLE:
			rc = { 20 * n,n * 3, n, n }; break;
			break;
		case POINTS_SUSHI:
			rc = { 30 * n,n * 3, n, n }; break;
			break;

		}
	}


	//IF BUB
	if (P1 == true)
	{
		switch (Points()) {
		case POINTS_APPLE:
			rc = { 21 * n,n * 2, n, n }; break;
			break;
		case POINTS_BANANA:
			rc = { 17 * n,n * 2, n, n }; break;
			break;
		case POINTS_GRAPE:
			rc = { 31 * n,n * 2, n, n }; break;
			break;
		case POINTS_LEMON:
			rc = { 14 * n,n * 2, n, n }; break;
			break;
		case POINTS_ORANGE:
			rc = { 13 * n,n * 2, n, n }; break;
			break;
		case POINTS_PEAR:
			rc = { 18 * n,n * 2, n, n }; break;
			break;
		case POINTS_WATERMELON:
			rc = { 19 * n,n * 2, n, n }; break;
			break;
		case POINTS_BLUE_CANDY:
			rc = { 9 * n,n * 2, n, n }; break;
			break;
		case POINTS_CAKE:
			rc = { 29 * n,n * 2, n, n }; break;
			break;
		case POINTS_DONUT:
			rc = { 27 * n,n * 2, n, n }; break;
			break;
		case POINTS_POPSICLE:
			rc = { 20 * n,n * 2, n, n }; break;
			break;
		case POINTS_SUSHI:
			rc = { 30 * n,n * 2, n, n }; break;
			break;
		}
	}
	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS), rc);


}
bool Object::pastTime(float time)
{
	framecounter++;
	if (framecounter / 60 == time)
	{
		framecounter = 0;
		return true;
	}
	return false;
}
void Object::PointsAnimation()
{
	Point p = GetPos();
	p.y -= 0.001;
	SetPos(p);
}