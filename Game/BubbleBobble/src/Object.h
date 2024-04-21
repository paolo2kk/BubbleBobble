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

enum class PointsType { _10, _20, _30, _40, _50, _60, _70, _80, _90, _100, _150, _200, _250, _300, _350, _400, _450, _500, _550, _600, _650, _700, _750, _800, _850, _900, _950, _1000, _1200, _2000, _3000, _4000, _5000, _6000, _7000, _8000, _9000, _10000, _x2, _x3, _x4, _x5, _x6, _x7, _x8, _x9 };

enum class ObjectType { 

	APPLE, BANANA, CHERRY, GRAPE, LEMON, ORANGE_OBJ, PEAR, WATERMELON,
	BLUE_CANDY, CAKE, DONUT, HAMBURGUER, HOT_DOG, ICE_CREAM, PINK_CANDY, PIZZA, POPSICLE, SUSHI, YELLOW_CANDY, MIQUEL,
						
};

class Object : public Entity
{
public:
	Object(const Point& p);
	~Object();

	ObjectType DrawRandObject();

	void DrawDebug(const Color& col) const;
	int Points() const;

private:
	ObjectType type;
};
