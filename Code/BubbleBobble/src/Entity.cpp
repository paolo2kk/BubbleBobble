#include "Entity.h"
#include <cmath>
#include "Globals.h"

//Entity::Entity() :
//	pos({ 0,0 }), dir({ 0,0 }), width(0), height(0), frame_width(0), frame_height(0), render(nullptr)
//{
//	isAlive = false;
//}
Entity::Entity(const Point& p, int w, int h) : pos(p), dir({ 0,0 }), width(w), height(h), frame_width(w), frame_height(h), render(nullptr)
{
	isAlive = true;
    NoHitbox = false;
    InitializeAnimations();
}
Entity::Entity(const Point& p, int w, int h, int frame_w, int frame_h) : pos(p), dir({ 0,0 }), width(w), height(h), frame_width(frame_w), frame_height(frame_h), render(nullptr)
{
	isAlive = true;
    NoHitbox = false;
    InitializeAnimations();
}
Entity::~Entity()
{
	if (render != nullptr)
	{
		delete render;
		render = nullptr;
	}
}
AppStatus Entity::InitializeAnimations()
{
    float i;
    const float n = ANIM_SIZE;

    ResourceManager& data = ResourceManager::Instance();

    if (data.LoadTexture(Resource::IMG_ANIMATIONS, "images/ANIMATIONS.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_animations = data.GetTexture(Resource::IMG_ANIMATIONS);

    render = new Sprite(data.GetTexture(Resource::IMG_ANIMATIONS));
    if (render == nullptr)
    {
        LOG("Failed to allocate memory for player sprite");
        return AppStatus::ERROR;
    }

    // Zen Chan Animations

    Sprite* Anima = dynamic_cast<Sprite*>(render);
    Anima->SetNumberAnimations((int)Animations::NUM_ANIMATIONS);

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_WALK_R, { i * n, 0, -n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_WALK_L, { i * n, 0, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_ANGRY_WALK_R, { i * n, n, -n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_ANGRY_WALK_L, { i * n, n, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_DEATH, { i * n, n * 2, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_GREEN, { i * n, n * 3, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_YELLOW, { i * n, n * 3, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_RED, { i * n, n * 3, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_BLUE, { i * n, n * 4, n, n });

    //PulPul animations

    Anima->SetAnimationDelay((int)Animations::PULPUL_FLY, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_FLY, { i * n, n * 5, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_ANGRY_FLY, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_ANGRY_FLY, { i * n, n * 6, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_DEATH, { i * n, n * 7, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_GREEN, { i * n, n * 8, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_YELLOW, { i * n, n * 8, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_RED, { i * n, n * 8, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_BLUE, { i * n, n * 9, n, n });

    //Benebow animations

    Anima->SetAnimationDelay((int)Animations::BENEBOU_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_WALK_R, { i * n, n * 10, -n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_WALK_L, { i * n, n * 10, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_ANGRY_WALK_R, { i * n, n * 11, -n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_ANGRY_WALK_L, { i * n, n * 11, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_DEATH, { i * n, n * 12, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_GREEN, { i * n, n * 13, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_YELLOW, { i * n, n * 13, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_RED, { i * n, n * 13, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_BLUE, { i * n, n * 14, n, n });

    // Hidegons animations

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_WALK_R, { i * n, n * 15, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_WALK_L, { i * n, n * 15, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_SPECIAL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_SPECIAL_R, { i * n, n * 16, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_SPECIAL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_SPECIAL_L, { i * n, n * 16, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_WALK_R, { i * n, n * 17, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_WALK_L, { i * n, n * 17, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_SPECIAL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_SPECIAL_R, { i * n, n * 18, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_SPECIAL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_SPECIAL_L, { i * n, n * 18, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_R, { i * n, n * 19, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_L, { i * n, n * 19, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_ANGRY_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_ANGRY_R, { i * n, n * 20, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_ANGRY_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_ANGRY_L, { i * n, n * 20, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_DEATH, { i * n, n * 21, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_GREEN, { i * n, n * 22, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_YELLOW, { i * n, n * 22, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_RED, { i * n, n * 22, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_BLUE, { i * n, n * 23, n, n });

    // Drunk animnations

    Anima->SetAnimationDelay((int)Animations::DRUNK_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_WALK_R, { i * n, n * 24, -n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_WALK_L, { i * n, n * 24, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_R, { i * n * 2, n * 25, -n * 2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_L, { i * n * 2, n * 25, n * 2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_ANGRY_WALK_R, { i * n, n * 26, -n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_ANGRY_WALK_L, { i * n, n * 26, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_ANGRY_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_ANGRY_R, { i * n * 2, n * 27, -n * 2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_ANGRY_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_ANGRY_L, { i * n * 2, n * 27, n * 2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DEATH, { i * n, n * 28, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_PROJECTILE, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_PROJECTILE, { i * n, n * 29, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_GREEN, { i * n, n * 30, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_YELLOW, { i * n, n * 30, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_RED, { i * n, n * 30, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_BLUE, { i * n, n * 31, n, n });

    // Skel monsta

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_SPAWN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_SPAWN, { i * n, n * 32, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_WALK_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_WALK_R, { i * n, n * 33, -n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_WALK_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_WALK_L, { i * n, n * 33, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_GREEN, { i * n, n * 34, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_YELLOW, { i * n, n * 34, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_RED, { i * n, n * 34, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_BLUE, { i * n, n * 35, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_DEATH, { i * n, n * 36, n, n });

    //BOB animations

    Anima->SetAnimationDelay((int)Animations::BOB_IDLE_R, 30);
        Anima->AddKeyFrame((int)Animations::BOB_IDLE_R, { 0 * n, n * 37, -n, n });
        Anima->AddKeyFrame((int)Animations::BOB_IDLE_R, { 2 * n, n * 37, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_IDLE_L, 30);
        Anima->AddKeyFrame((int)Animations::BOB_IDLE_L, { 0 * n, n * 37, n, n });
        Anima->AddKeyFrame((int)Animations::BOB_IDLE_L, { 2 * n, n * 37, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_WALK_R, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_WALK_R, { i * n, n * 37, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_WALK_L, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_WALK_L, { i * n, n * 37, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_ATACK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_ATACK_R, { i * n, n * 38, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_ATACK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_ATACK_L, { i * n, n * 38, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_FALL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FALL_R, { i * n, n * 39, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_FALL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FALL_L, { i * n, n * 39, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_JUMP_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_JUMP_R, { i * n, n * 40, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_JUMP_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_JUMP_L, { i * n, n * 40, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUISH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUISH_R, { i * n, n * 41, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUISH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUISH_L, { i * n, n * 41, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUASH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUASH_R, { i * n, n * 42, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUASH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUASH_L, { i * n, n * 42, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_DEATH, ANIM_DELAY + 5 );
    for (i = 0; i < 12; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_DEATH, { i * n, n * 43, n, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_PUSH_BUTTON, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_PUSH_BUTTON, { i * n * 2, n * 45, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_FIRE_DEATH, ANIM_DELAY);
    for (i = 0; i < 16; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FIRE_DEATH, { i * n * 2, n * 47, n * 2, n });

    Anima->SetAnimationDelay((int)Animations::BOB_LEVEL_TRANSITION_FASE_1, 10);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_LEVEL_TRANSITION_FASE_1, { i * n * 2, n * 48, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_LEVEL_TRANSITION_FASE_2, 20);
    for (i = 5; i <= 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_LEVEL_TRANSITION_FASE_2, { i * n * 2, n * 48, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_LEVEL_TRANSITION_FASE_3, 10);
    for (i = 8; i <= 9; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_LEVEL_TRANSITION_FASE_3, { i * n * 2, n * 48, n * 2, n * 2 });

    // Bub Animations

    Anima->SetAnimationDelay((int)Animations::BUB_IDLE_R, 30);
    Anima->AddKeyFrame((int)Animations::BUB_IDLE_R, { 0 * n, n * 50, -n, n });
    Anima->AddKeyFrame((int)Animations::BUB_IDLE_R, { 2 * n, n * 50, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_IDLE_L, 30);
    Anima->AddKeyFrame((int)Animations::BUB_IDLE_L, { 0 * n, n * 50, n, n });
    Anima->AddKeyFrame((int)Animations::BUB_IDLE_L, { 2 * n, n * 50, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_WALK_R, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_WALK_R, { i * n, n * 50, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_WALK_L, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_WALK_L, { i * n, n * 50, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_ATACK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_ATACK_R, { i * n, n * 51, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_ATACK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_ATACK_L, { i * n, n * 51, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_FALL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FALL_R, { i * n, n * 52, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_FALL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FALL_L, { i * n, n * 52, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_JUMP_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_JUMP_R, { i * n, n * 53, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_JUMP_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_JUMP_L, { i * n, n * 53, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUISH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUISH_R, { i * n, n * 54, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUISH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUISH_L, { i * n, n * 54, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUASH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUASH_R, { i * n, n * 55, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUASH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUASH_L, { i * n, n * 55, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_DEATH, ANIM_DELAY + 5);
    for (i = 0; i < 12; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_DEATH, { i * n, n * 56, n, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BUB_PUSH_BUTTON, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_PUSH_BUTTON, { i * n * 2, n * 59, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BUB_FIRE_DEATH, ANIM_DELAY);
    for (i = 0; i < 16; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FIRE_DEATH, { i * n * 2, n * 58, n * 2, n });

    Anima->SetAnimationDelay((int)Animations::BUB_LEVEL_TRANSITION_FASE_1, 10);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_LEVEL_TRANSITION_FASE_1, { i * n * 2, n * 61, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BUB_LEVEL_TRANSITION_FASE_2, 20);
    for (i = 5; i <= 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_LEVEL_TRANSITION_FASE_2, { i * n * 2, n * 61, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BUB_LEVEL_TRANSITION_FASE_3, 10);
    for (i = 8; i <= 9; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_LEVEL_TRANSITION_FASE_3, { i * n * 2, n * 61, n * 2, n * 2 });

    //BUBBLES

    Anima->SetAnimationDelay((int)Animations::BUBBLE, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::BUBBLE, { i * n , n * 63, n, n });

    Anima->SetAnimationDelay((int)Animations::THUNDER_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::THUNDER_BUBBLE_GREEN, { i * n, n * 64, n, n });

    Anima->SetAnimationDelay((int)Animations::THUNDER_BUBBLE_YELLOW, ANIM_DELAY);
    for (i = 3; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::THUNDER_BUBBLE_YELLOW, { i * n, n * 64, n, n});

    Anima->SetAnimationDelay((int)Animations::THUNDER_BUBBLE_RED, ANIM_DELAY);
    for (i = 6; i < 9; ++i)
        Anima->AddKeyFrame((int)Animations::THUNDER_BUBBLE_RED, { i * n, n * 64, n, n });

    Anima->SetAnimationDelay((int)Animations::THUNDER_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::THUNDER_BUBBLE_BLUE, { i * n, n * 65, n, n });

    Anima->SetAnimationDelay((int)Animations::BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUBBLE_GREEN, { i * n, n * 66, n, n });

    Anima->SetAnimationDelay((int)Animations::BUBBLE_APLASTAO, ANIM_DELAY);
    Anima->AddKeyFrame((int)Animations::BUBBLE_APLASTAO, { 0, n * 66, n, n });

    Anima->SetAnimationDelay((int)Animations::BUBBLE_POP, ANIM_DELAY);
    for (i = 3; i <= 4; ++i)
        Anima->AddKeyFrame((int)Animations::BUBBLE_POP, { i * n, n * 66, n, n });

    Anima->SetAnimationDelay((int)Animations::HURRY_UP, ANIM_DELAY);
        Anima->AddKeyFrame((int)Animations::HURRY_UP, { 5 * n, n * 66, n*4, n });
        Anima->AddKeyFrame((int)Animations::HURRY_UP, { 9 * n, n * 66, n * 4, n });

    Anima->SetAnimationDelay((int)Animations::BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUBBLE_BLUE, { i * n, n * 67, n, n });

    Anima->SetAnimationDelay((int)Animations::SPAWN_BUBBLE_GREEN_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::SPAWN_BUBBLE_GREEN_R, { i * n, n * 68, -n, n });

    Anima->SetAnimationDelay((int)Animations::SPAWN_BUBBLE_GREEN_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::SPAWN_BUBBLE_GREEN_L, { i * n, n * 68, n, n });

    Anima->SetAnimationDelay((int)Animations::SPAWN_BUBBLE_BLUE_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::SPAWN_BUBBLE_BLUE_R, { i * n, n * 69, -n, n });

    Anima->SetAnimationDelay((int)Animations::SPAWN_BUBBLE_BLUE_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::SPAWN_BUBBLE_BLUE_L, { i * n, n * 69, n, n });

    //SUPER DRUNK

    Anima->SetAnimationDelay((int)Animations::SUPER_DRUNK_WALK, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::SUPER_DRUNK_WALK, { i * n*4, n * 70, n*4, n*4 });

    Anima->SetAnimationDelay((int)Animations::SUPER_DRUNK_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::SUPER_DRUNK_DEATH, { i * n * 4, n * 74, n * 4, n * 4 });

    Anima->SetAnimationDelay((int)Animations::SUPER_DRUNK_ANGRY, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::SUPER_DRUNK_ANGRY, { i * n * 4, n * 78, n * 4, n * 4 });

    Anima->SetAnimationDelay((int)Animations::SUPER_DRUNK_BUBBLE, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::SUPER_DRUNK_BUBBLE, { i * n * 4, n * 82, n * 4, n * 4 });

    return AppStatus::OK;
}
Point Entity::GetPos()
{
	return pos;
}
void Entity::SetPos(const Point& p)
{
	pos = p;
}
bool Entity::IsAlive() const
{
	return isAlive;
}
void Entity::Update()
{
	pos += dir;
    
}
AABB Entity::GetHitbox() const
{
    if (NoHitbox == false)
    {
        Point p(pos.x, pos.y - (height - 1));
        AABB hitbox(p, width, height);
        return hitbox;
    }
    else
    {
        Point p(pos.x, pos.y - (height - 1));
        Point d(-100, -100);
        AABB hitbox(d, width, height);
        return hitbox;
    }

}
AABB Entity::GetHitArea() const
{

    Point position(0, pos.y - (height - 1));
    
    AABB hitarea(position, WINDOW_WIDTH / 2, height);
    return hitarea;
}
void Entity::DeleteHitbox() 
{
    NoHitbox = true;
}
Point Entity::GetRenderingPosition() const
{
	Point p;
	p.x = pos.x + width / 2 - frame_width / 2;
	p.y = pos.y - (frame_height-1);
	return p;
}
void Entity::SetAlive(bool b)
{
	isAlive = b;
}
void Entity::Set(const Point& p, const Point& d, int w, int h, int framew, int frameh)
{
	pos = p;
	dir = d;
	width = w;
	height = h;
	frame_width = framew;
	frame_height = frameh;
	isAlive = true;
}
void Entity::SetAnimationE(int id)
{
    Sprite* sprite = dynamic_cast<Sprite*>(render);
    sprite->SetAnimation(id);
}
void Entity::Spriteset()
{
    Sprite* sprite = dynamic_cast<Sprite*>(render);
    sprite->Update();
    Draw();
}
void Entity::Draw() const
{
	Point p = GetRenderingPosition();
	render->Draw(p.x, p.y);
}
void Entity::Warp()
{
	if (pos.y > WINDOW_HEIGHT) {
		pos.y = -TILE_SIZE;
	}
}
void Entity::DrawTint(const Color& col) const
{
	Point p = GetRenderingPosition();
	render->DrawTint(p.x, p.y, col);
}
void Entity::DrawHitbox(const Color& col) const
{
	Color c = col;
	c.a = 128;		//50% transparent

	render->DrawBox(pos.x, pos.y-(height-1), width, height, c);
	render->DrawCorners(pos.x, pos.y-(height-1), width, height);
    
        render->DrawBox(0, pos.y - (height - 1), WINDOW_WIDTH, height, c);

   

}
void Entity::DrawHitbox(int x, int y, int w, int h, const Color& col) const
{
	Color c = col;
	c.a = 128;		//50% transparent

	render->DrawBox(x, y-(h-1), w, h, c);
	render->DrawCorners(x, y-(h-1), w, h);
}
