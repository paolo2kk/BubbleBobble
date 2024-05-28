#include "Particle.h"
#include "Sprite.h"

Particle::Particle()
{
	const int n = TILE_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	render = new Sprite(data.GetTexture(Resource::IMG_ANIMATIONS));
	
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations(1);
	sprite->SetAnimationDelay((int)Animations::BUBBLE_POP, PARTICLE_ANIM_DELAY);
		sprite->AddKeyFrame((int)Animations::BUBBLE_POP, { n * 3, n * 66, n, n });
		sprite->AddKeyFrame((int)Animations::BUBBLE_POP, { n * 4, n * 66, n, n });

	
	sprite->SetAnimation(0);

	SetAlive(false);
}
Particle::~Particle()
{
}
void Particle::Init(const Point& p)
{
	//Set position
	Set(p, {0,0}, PARTICLE_FRAME_SIZE, PARTICLE_FRAME_SIZE, PARTICLE_FRAME_SIZE, PARTICLE_FRAME_SIZE);
	
	//Initialise animation
	Sprite* sprite = dynamic_cast<Sprite*>(render); 
	sprite->SetAnimation(0);
}
bool Particle::Update()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();

	return sprite->IsAnimationComplete();
}
void Particle::Draw() const
{
	render->Draw(pos.x, pos.y);
}