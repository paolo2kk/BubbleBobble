#pragma once
#include "Entity.h"

#define OBJECT_PHYSICAL_SIZE	14
#define OBJECT_FRAME_SIZE		16

#define POINTS_APPLE	700
#define POINTS_BANANA	500
#define POINTS_CHERRY	700
#define POINTS_GRAPE	4000
#define POINTS_LEMON	350
#define POINTS_ORANGE	300
#define POINTS_PEAR		550
#define POINTS_WATERMELON	600
#define POINTS_BLUE_CANDY	100
#define POINTS_CAKE			2000
#define POINTS_DONUT		1000
#define POINTS_HAMBURGUER	2000
#define POINTS_HOT_DOG		500
#define POINTS_ICE_CREAM	1000
#define POINTS_PINK_CANDY	100
#define POINTS_PIZZA		1000
#define POINTS_POPSICLE		650
#define POINTS_SUSHI		3000
#define POINTS_YELLOW_CANDY	100
#define POINTS_MIQUEL		4000



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

