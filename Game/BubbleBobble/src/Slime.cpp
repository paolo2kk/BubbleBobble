#include "Slime.h"
#include "Sprite.h"

Slime::Slime(const Point& p, int width, int height, int frame_width, int frame_height) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = SlimeState::ROAMING;

	current_step = 0;
	current_frames = 0;
}
Slime::~Slime()
{
}
AppStatus Slime::Initialise(Look look, const AABB& area)
{
	int i;
	const int n = SLIME_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	render = new Sprite(data.GetTexture(Resource::IMG_ENEMIES));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for slime sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)SlimeAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)SlimeAnim::IDLE_RIGHT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::IDLE_RIGHT, { 0, 2 * n, n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::IDLE_LEFT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::IDLE_LEFT, { 0, 2 * n, -n, n });

	sprite->SetAnimationDelay((int)SlimeAnim::WALKING_RIGHT, SLIME_ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)SlimeAnim::WALKING_RIGHT, { (float)i * n, 2 * n, n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::WALKING_LEFT, SLIME_ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)SlimeAnim::WALKING_LEFT, { (float)i * n, 2 * n, -n, n });

	sprite->SetAnimationDelay((int)SlimeAnim::ATTACK_RIGHT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_RIGHT, { 0, 3 * n, n, n });
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_RIGHT, { n, 3 * n, n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::ATTACK_LEFT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_LEFT, { 0, 3 * n, -n, n });
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_LEFT, { n, 3 * n, -n, n });

	this->look = look;
	if (look == Look::LEFT)        sprite->SetAnimation((int)SlimeAnim::IDLE_LEFT);
	else if (look == Look::RIGHT) sprite->SetAnimation((int)SlimeAnim::IDLE_RIGHT);

	visibility_area = area;

	InitPattern();

	return AppStatus::OK;
}
void Slime::InitPattern()
{
	//Multiplying by 3 ensures sufficient time for displaying all 3 frames of the
	//walking animation, resulting in smoother transitions and preventing the animation
	//from appearing rushed or incomplete
	const int n = SLIME_ANIM_DELAY * 3;

	pattern.push_back({ {0, 0}, 2 * n, (int)SlimeAnim::IDLE_RIGHT });
	pattern.push_back({ {SLIME_SPEED, 0}, n, (int)SlimeAnim::WALKING_RIGHT });
	pattern.push_back({ {0, 0}, n, (int)SlimeAnim::IDLE_RIGHT });
	pattern.push_back({ {SLIME_SPEED, 0}, n, (int)SlimeAnim::WALKING_RIGHT });
	pattern.push_back({ {0, 0}, n, (int)SlimeAnim::IDLE_RIGHT });

	pattern.push_back({ {0, 0}, 2 * n, (int)SlimeAnim::IDLE_LEFT });
	pattern.push_back({ {-SLIME_SPEED, 0}, n, (int)SlimeAnim::WALKING_LEFT });
	pattern.push_back({ {0, 0}, n, (int)SlimeAnim::IDLE_LEFT });
	pattern.push_back({ {-SLIME_SPEED, 0}, n, (int)SlimeAnim::WALKING_LEFT });
	pattern.push_back({ {0, 0}, n, (int)SlimeAnim::IDLE_LEFT });

	current_step = 0;
	current_frames = 0;
}
bool Slime::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;

	if (state == SlimeState::ROAMING)
	{
		if (IsVisible(box))
		{
			state = SlimeState::ATTACK;
			//The attack animation consists of 2 frames, with the second one being when
			//we throw the shot. Wait for a frame before initiating the attack.
			attack_delay = SLIME_ANIM_DELAY;

			if (look == Look::LEFT)	sprite->SetAnimation((int)SlimeAnim::ATTACK_LEFT);
			else					sprite->SetAnimation((int)SlimeAnim::ATTACK_RIGHT);
		}
		else
		{
			pos += pattern[current_step].speed;
			current_frames++;

			if (current_frames == pattern[current_step].frames)
			{
				current_step++;
				current_step %= pattern.size();
				current_frames = 0;

				anim_id = pattern[current_step].anim;
				sprite->SetAnimation(anim_id);
				UpdateLook(anim_id);
			}
		}
	}
	else if (state == SlimeState::ATTACK)
	{
		if (!IsVisible(box))
		{
			state = SlimeState::ROAMING;

			//Continue with the previous animation pattern before initiating the attack
			anim_id = pattern[current_step].anim;
			sprite->SetAnimation(anim_id);
		}
		else
		{
			attack_delay--;
			if (attack_delay == 0)
			{
				shoot = true;

				//The attack animation consists of 2 frames. Wait for a complete loop
				//before shooting again
				attack_delay = 2 * SLIME_ANIM_DELAY;
			}
		}
	}
	sprite->Update();

	return shoot;
}
void Slime::UpdateLook(int anim_id)
{
	SlimeAnim anim = (SlimeAnim)anim_id;
	look = (anim == SlimeAnim::IDLE_LEFT ||
		anim == SlimeAnim::WALKING_LEFT ||
		anim == SlimeAnim::ATTACK_LEFT) ? Look::LEFT : Look::RIGHT;
}
void Slime::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + SLIME_SHOT_OFFSET_X_LEFT;
		*d = { -SLIME_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + SLIME_SHOT_OFFSET_X_RIGHT;
		*d = { SLIME_SHOT_SPEED, 0 };
	}
	p->y = pos.y + SLIME_SHOT_OFFSET_Y;
}