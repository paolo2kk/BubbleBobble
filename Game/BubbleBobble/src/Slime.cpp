#include "Slime.h"
#include "Sprite.h"

Slime::Slime(const Point& p, int width, int height, int frame_width, int frame_height, TileMap* mapp) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = SlimeState::ROAMING;
	map = mapp;
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
	sprite->AddKeyFrame((int)SlimeAnim::IDLE_RIGHT, { 0, 4 * n, -n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::IDLE_LEFT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::IDLE_LEFT, { 0, 4 * n, n, n });

	sprite->SetAnimationDelay((int)SlimeAnim::WALKING_RIGHT, SLIME_ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)SlimeAnim::WALKING_RIGHT, { (float)i * n, 4 * n, -n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::WALKING_LEFT, SLIME_ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)SlimeAnim::WALKING_LEFT, { (float)i * n, 4 * n, n, n });

	sprite->SetAnimationDelay((int)SlimeAnim::ATTACK_RIGHT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_RIGHT, { 0, 6 * n, n, n });
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_RIGHT, { n, 6 * n, n, n });
	sprite->SetAnimationDelay((int)SlimeAnim::ATTACK_LEFT, SLIME_ANIM_DELAY);
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_LEFT, { 0, 6 * n, -n, n });
	sprite->AddKeyFrame((int)SlimeAnim::ATTACK_LEFT, { n, 6 * n, -n, n });

	this->look = look;
	if (look == Look::LEFT)        sprite->SetAnimation((int)SlimeAnim::WALKING_LEFT);
	else if (look == Look::RIGHT) sprite->SetAnimation((int)SlimeAnim::WALKING_RIGHT);

	visibility_area = area;


	return AppStatus::OK;
}

bool Slime::Update(const AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;

	MoveX();
	MoveY();
	sprite->Update();

	return shoot;
}
void Slime::MoveX()
{
	AABB box = GetHitbox();
	int prev_x = pos.x;

	if (look == Look::RIGHT) {
		pos += {1,0};
	}else if (look == Look::LEFT) {
		pos += {-1, 0};
	}
	
	if (map->TestCollisionWallLeft(box))
	{
		pos.x = prev_x;
		look = Look::RIGHT;
	}
	else if (map->TestCollisionHalfWallRight(box)) {
		pos.x = prev_x;
		look = Look::RIGHT;

	}

	if (map->TestCollisionWallRight(box))
	{
		pos.x = prev_x;
		look = Look::RIGHT;

	}
	else if (map->TestCollisionHalfWallLeft(box)) {
		pos.x = prev_x;
		look = Look::RIGHT;

	}
}
void Slime::MoveY()
{

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