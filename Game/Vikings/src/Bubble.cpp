#include "Bubble.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include "Player.h"
#include <raymath.h>

Bubble::Bubble(const Point& p, State s, Look view) :
	Player(p, s, view)
{
	startPos = p;
	state = s;
	look = view;
	shoot_delay = SHOOT_DELAY;
	map = nullptr;
	isAlive = false;
}

Bubble::~Bubble()
{
	delete this;
}

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

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}

void Bubble::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_BUBBLES);

	render->Release();
}
