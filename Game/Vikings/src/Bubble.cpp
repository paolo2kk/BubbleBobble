#include "Bubble.h"
#include "StaticImage.h"

<<<<<<< Updated upstream
Bubble::Bubble(const Point& p, State s, Look view) :
	Player(p, s, view)
{
	startPos = p;
	state = s;
	look = view;
	shoot_delay = SHOOT_DELAY;
	map = nullptr;
=======
Bubble::Bubble(const Point& p, Direction d) : Entity(p, BUBBLE_PHYSICAL_SIZE, BUBBLE_PHYSICAL_SIZE, BUBBLE_FRAME_SIZE, BUBBLE_FRAME_SIZE)
{
	dire = d;
	speed = .3;
	stages = 1;
	Rectangle rc;
	const int n = TILE_SIZE;
	eTime = 0;
	spawnTime = 0;
	lifeTime = GetRandomValue(3, 5);
	switch (dire)
	{
	case Direction::LEFT: rc = { n, n, n, n }; break;
	case Direction::RIGHT: rc = {n, n, n, n }; break;

	default: LOG("Internal error: object creation of invalid type");
	}
	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_TILES), rc);

>>>>>>> Stashed changes
}

Bubble::~Bubble()
{
	delete this;
}
<<<<<<< Updated upstream

AppStatus Bubble::Initialise()
{
	int i;
	const int n = BUBBLE_FRAME_SIZE;
	const int p = PADDING_X;
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_BUBBLES, "images/Bubbles.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for bubble sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);
	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { n + 1, n, -n, n });
	sprite->SetAnimationDelay((int)BubbleAnim::CRUSHED_SIDE, ANIM_DELAY);
	sprite->AddKeyFrame((int)BubbleAnim::CRUSHED_SIDE, { 0, 0, -n, n });

	sprite->SetAnimationDelay((int)BubbleAnim::INSHOOT, ANIM_DELAY);
	for (i = 0; i < 5; ++i)
		sprite->AddKeyFrame((int)BubbleAnim::INSHOOT, { (float)i * (n + PADDING_X), (float)0, -n, n });

	sprite->SetAnimation((int)BubbleAnim::INSHOOT);
	

	return AppStatus::OK;
}

void Bubble::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}

void Bubble::Update()
{
	eFrame++;
	MovementX();
	MovementY();
}


void Bubble::MovementX()
{
	SetAnimation((int)BubbleAnim::INSHOOT);
	for (int i = 0; i < SHOOT_RANGE; i += SHOOT_SPEED) {
		pos.x += i;
	}
	MovementXfinished = true;
}

void Bubble::MovementY()
{
	if (MovementXfinished) {

	}
}

void Bubble::StartFloating()
{
}

void Bubble::SetAnimation(int id)
{
}

void Bubble::SetCrushedSideAnimation()
{
=======
void Bubble::Update()
{
	
	pos += dir;

	LeftMovement(dire);
	
}
bool Bubble::isAlive()
{
	eTime += GetFrameTime();
	if (eTime >= lifeTime)
	{
		return false;
	}
	else {
		return true;
	}
}
void Bubble::LeftMovement(Direction d)
{
	
	if (d == Direction::LEFT)
	{
		switch (stages) {
		case 1:
			dir = { 0, -1 };
			if (pos.y <= 200) {
				stages++;
			}
			break;
		case 2:
			dir = { 1, 0 };
			if (pos.x >= 105) {
				stages++;
			}
			break;
		case 3:
			dir = { 0, -1 };
			if (pos.y <= 144) {
				stages++;
			}
			break;
		case 4:
			dir = { -1, 0 };
			if (pos.x <= 24) {
				stages++;
			}
			break;
		case 5:
			dir = { 0, -1 };
			
			break;
		}


	}
	else if (d == Direction::RIGHT)
	{
		
			switch (stages) {
			case 1:
				dir = { 0, -1 };
				if (pos.y <= 200) {
					stages++;
				}
				break;
			case 2:
				dir = { -1, 0 };
				if (pos.x <= 136) {
					stages++;
				}
				break;
			case 3:
				dir = { 0, -1 };
				if (pos.y <= 144) {
					stages++;
				}
				break;
			case 4:
				dir = { 1, 0 };
				if (pos.x >= 216) {
					stages++;
				}
				break;
			case 5:
				dir = { 0, -1 };

				break;
			}


	}

>>>>>>> Stashed changes
}

void Bubble::SetCrushedTopAnimation()
{
}

void Bubble::Stop()
{
}

void Bubble::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
int Bubble::Points() const
{
	if (dire == Direction::LEFT)		return POINTS_APPLE;
	else if (dire == Direction::RIGHT)	return POINTS_CHILI;
	else
	{
		LOG("Internal error: object direction invalid when giving points");
		return 0;
	}
}

void Bubble::Release()
{

	render->Release();
}
<<<<<<< Updated upstream
=======

//#include "Bubble.h"
//#include "Sprite.h"
//#include "TileMap.h"
//#include "Globals.h"
//#include <raymath.h>
//
//
//Bubble::Bubble(const Point& p, States s, Looks view) :
//	Entity(p, BUBBLE_PHYSICAL_WIDTH, BUBBLE_PHYSICAL_HEIGHT, BUBBLE_FRAME_SIZE, BUBBLE_FRAME_SIZE)
//{
//	state = s;
//	look = view;
//	
//}
//Bubble::~Bubble()
//{
//}
//AppStatus Bubble::Initialise()
//{
//	int i;
//	const int n = BUBBLE_FRAME_SIZE;
//	ResourceManager& data = ResourceManager::Instance();
//	if (data.LoadTexture(Resource::IMG_BUBBLES, "images/Bubbles.png") != AppStatus::OK)
//	{
//		return AppStatus::ERROR;
//	}
//
//	render = new Sprite(data.GetTexture(Resource::IMG_BUBBLES));
//	if (render == nullptr)
//	{
//		LOG("Failed to allocate memory for player sprite");
//		return AppStatus::ERROR;
//	}
//
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetNumberAnimations((int)BubbleAnim::NUM_ANIMATIONS);
//	sprite->SetAnimationDelay((int)BubbleAnim::IDLE, ANIM_DELAY);
//	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { n, n, n, n });
//	sprite->AddKeyFrame((int)BubbleAnim::IDLE, { n, n, n, n });
//
//	sprite->SetAnimation((int)BubbleAnim::IDLE);
//	return AppStatus::OK;
//}
//
//void Bubble::SetAnimation(int id)
//{
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->SetAnimation(id);
//}
//void Bubble::Update()
//{
//	Sprite* sprite = dynamic_cast<Sprite*>(render);
//	sprite->Update();
//	SetAnimation((int)BubbleAnim::IDLE);
//
//}
//void Bubble::Render()
//{
//	Point p = GetRenderingPosition();
//	render->Draw(p.x, p.y);
//}
//void Bubble::DrawDebug(const Color& col) const
//{
//	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
//
//	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
//	DrawPixel(pos.x, pos.y, WHITE);
//}
//void Bubble::Release()
//{
//	ResourceManager& data = ResourceManager::Instance();
//	data.ReleaseTexture(Resource::IMG_BUBBLES);
//
//	render->Release();
//}
>>>>>>> Stashed changes
