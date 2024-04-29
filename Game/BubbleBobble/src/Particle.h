#pragma once
#include "Entity.h"

#define PARTICLE_FRAME_SIZE		16
#define PARTICLE_ANIM_DELAY		(2*ANIM_DELAY)

class Particle : public Entity
{
public:
	Particle();
	~Particle();

	void Init(const Point& p);

	//"Overriden" function, particles don't move and returns true if the animation is complete
	bool Update();

	//Overridden function because the control point is located at the top left instead of the
	//bottom left (which is the default control point position for entities)
	void Draw() const;
};

