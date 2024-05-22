#include "Turret.h"
#include "Sprite.h"

Turret::Turret(const Point& p, int width, int height, int frame_width, int frame_height) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = TURRET_SHOOT_DELAY;
	state = TurretState::IDLE;
}
Turret::~Turret()
{
}
AppStatus Turret::Initialise(Look look, const AABB& area)
{
	const int n = TURRET_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	render = new Sprite(data.GetTexture(Resource::IMG_ENEMIES));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for turret sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)TurretAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)TurretAnim::IDLE_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)TurretAnim::IDLE_RIGHT, { 0, 0, n, n });
	sprite->SetAnimationDelay((int)TurretAnim::IDLE_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)TurretAnim::IDLE_LEFT, { 0, 0, -n, n });

	sprite->SetAnimationDelay((int)TurretAnim::ATTACK_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)TurretAnim::ATTACK_RIGHT, { 0, n, n, n });
	sprite->SetAnimationDelay((int)TurretAnim::ATTACK_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)TurretAnim::ATTACK_LEFT, { 0, n, -n, n });

	this->look = look;
	if (look == Look::LEFT)       sprite->SetAnimation((int)TurretAnim::IDLE_LEFT);
	else if (look == Look::RIGHT) sprite->SetAnimation((int)TurretAnim::IDLE_RIGHT);

	visibility_area = area;

	return AppStatus::OK;
}
bool Turret::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;

	if (state == TurretState::IDLE)
	{
		attack_delay--;
		if (attack_delay == 0)
		{
			if (IsVisible(box))
			{
				state = TurretState::ATTACK;

				if (look == Look::LEFT)	sprite->SetAnimation((int)TurretAnim::ATTACK_LEFT);
				else					sprite->SetAnimation((int)TurretAnim::ATTACK_RIGHT);
			}
			attack_delay = TURRET_SHOOT_DELAY;
		}
	}
	else if (state == TurretState::ATTACK)
	{
		attack_delay--;
		if (attack_delay == 0)
		{
			shoot = true;

			state = TurretState::IDLE;

			if (look == Look::LEFT)	sprite->SetAnimation((int)TurretAnim::IDLE_LEFT);
			else					sprite->SetAnimation((int)TurretAnim::IDLE_RIGHT);

			attack_delay = TURRET_SHOOT_DELAY;
		}
	}
	sprite->Update();

	return shoot;
}
void Turret::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + TURRET_SHOT_OFFSET_X_LEFT;
		*d = { -TURRET_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + TURRET_SHOT_OFFSET_X_RIGHT;
		*d = { TURRET_SHOT_SPEED, 0 };
	}
	p->y = pos.y + TURRET_SHOT_OFFSET_Y;
}