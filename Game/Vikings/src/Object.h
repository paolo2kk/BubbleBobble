#pragma once
#include "Entity.h"

#define OBJECT_PHYSICAL_SIZE	14
#define OBJECT_FRAME_SIZE		16

#define POINTS_APPLE	10
#define POINTS_BANANA	20
#define POINTS_CHERRY	10
#define POINTS_GRAPE	20
#define POINTS_LEMON	10
#define POINTS_CHILI	20
#define POINTS_APPLE	10
#define POINTS_CHILI	20
#define POINTS_APPLE	10
#define POINTS_CHILI	20



enum class ObjectType { APPLE, BANANA, CHERRY, GRAPE, LEMON, ORANGE_OBJ, PEAR, WATERMELON,
						BLUE_CANDY, CAKE, DONUT, HAMBURGUER, HOT_DOG, ICE_CREAM, PINK_CANDY, PIZZA, POPSICLE, SUSHI, YELLOW_CANDY, MIQUEL,
						
};

class Object : public Entity
{
public:
	Object(const Point& p, ObjectType t);
	~Object();

	void DrawDebug(const Color& col) const;
	int Points() const;

private:
	ObjectType type;
};

