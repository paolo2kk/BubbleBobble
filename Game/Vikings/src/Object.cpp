#include "Object.h"
#include "StaticImage.h"

Object::Object(const Point& p, ObjectType t) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t; 
	
	Rectangle rc;
	const int n = TILE_SIZE;
	
	switch (type)
	{
		case ObjectType::BLUE_CANDY: rc = {0, 0, n, n}; break;
		case ObjectType::CAKE: rc = {n, 0, n, n}; break;
		case ObjectType::DONUT: rc = { 2* n, 0, n, n }; break;
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
	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS), rc);

}
Object::~Object()
{
}
void Object::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
int Object::Points() const
{
	if (type == ObjectType::APPLE)		return POINTS_APPLE;
	else if (type == ObjectType::CHILI)	return POINTS_CHILI;
	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}