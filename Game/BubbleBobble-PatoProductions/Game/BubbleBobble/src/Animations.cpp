#include "Animations.h"

Anim::Anim()
{
    Initialize();
}
Anim::~Anim()
{

}

AppStatus Anim::Initialize()
{
    float i;
    const float n = ANIM_SIZE;

    ResourceManager& data = ResourceManager::Instance();

    if (data.LoadTexture(Resource::IMG_ANIMATIONS, "images/ANIMATIONS.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_animations = data.GetTexture(Resource::IMG_ANIMATIONS);

    render_ = new Sprite(data.GetTexture(Resource::IMG_ANIMATIONS));
    if (render_ == nullptr)
    {
        LOG("Failed to allocate memory for player sprite");
        return AppStatus::ERROR;
    }

    // Zen Chan Animations
    
    Anima = dynamic_cast<Sprite*>(render_);
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
        Anima->AddKeyFrame((int)Animations::ZENCHAN_DEATH, { i * n, n*2, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_GREEN, { i * n, n*3, n, n });

    Anima->SetAnimationDelay((int)Animations::ZENCHAN_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::ZENCHAN_BUBBLE_BLUE, { i * n, n*4, n, n });

    //PulPul animations

    Anima->SetAnimationDelay((int)Animations::PULPUL_FLY, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_FLY, { i * n, n*5, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_ANGRY_FLY, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_ANGRY_FLY, { i * n, n*6, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_DEATH, { i * n, n*7, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_GREEN, { i * n, n*8, n, n });

    Anima->SetAnimationDelay((int)Animations::PULPUL_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::PULPUL_BUBBLE_BLUE, { i * n, n*9, n, n });

    //Benebow animations

    Anima->SetAnimationDelay((int)Animations::BENEBOU_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_WALK_R, { i * n, n*10, -n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_WALK_L, { i * n, n*10, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_ANGRY_WALK_R, { i * n, n*11, -n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_ANGRY_WALK_L, { i * n, n*11, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_DEATH, { i * n, n*12, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_GREEN, { i * n, n*13, n, n });

    Anima->SetAnimationDelay((int)Animations::BENEBOU_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BENEBOU_BUBBLE_BLUE, { i * n, n*14, n, n });

    // Hidegons animations

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_WALK_R, { i * n, n*15, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_WALK_L, { i * n, n*15, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_SPECIAL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_SPECIAL_R, { i * n, n*16, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_SPECIAL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_SPECIAL_L, { i * n, n*16, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_WALK_R, { i * n, n*17, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_WALK_L, { i * n, n*17, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_SPECIAL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_SPECIAL_R, { i * n, n * 18, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_ANGRY_SPECIAL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_ANGRY_SPECIAL_L, { i * n, n * 18, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_R, { i * n, n*19, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_L, { i * n, n*19, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_ANGRY_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_ANGRY_R, { i * n, n*20, -n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_FIRE_ANGRY_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_FIRE_ANGRY_L, { i * n, n*20, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_DEATH, { i * n, n*21, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_GREEN, { i * n, n*22, n, n });

    Anima->SetAnimationDelay((int)Animations::HIDEGONS_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::HIDEGONS_BUBBLE_BLUE, { i * n, n*23, n, n });

    // Drunk animnations

    Anima->SetAnimationDelay((int)Animations::DRUNK_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_WALK_R, { i * n, n*24, -n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_WALK_L, { i * n, n*24, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_R, { i * n*2, n*25, -n*2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_L, { i * n*2, n*25, n*2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_ANGRY_WALK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_ANGRY_WALK_R, { i * n, n*26, -n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_ANGRY_WALK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_ANGRY_WALK_L, { i * n, n*26, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_ANGRY_R, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_ANGRY_R, { i * n*2, n*27, -n*2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DRINK_ANGRY_L, ANIM_DELAY);
    for (i = 0; i < 6; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DRINK_ANGRY_L, { i * n*2, n*27, n*2, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_DEATH, { i * n, n*28, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_PROJECTILE, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_PROJECTILE, { i * n, n * 29, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_GREEN, { i * n, n*30, n, n });

    Anima->SetAnimationDelay((int)Animations::DRUNK_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::DRUNK_BUBBLE_BLUE, { i * n, n*31, n, n });

   // Skel monsta

        Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_SPAWN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_SPAWN, { i * n, n*32, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_WALK_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_WALK_R, { i * n, n*33, -n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_WALK_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_WALK_L, { i * n, n*33, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_GREEN, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_GREEN, { i * n, n*34, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_BUBBLE_BLUE, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_BUBBLE_BLUE, { i * n, n*35, n, n });

    Anima->SetAnimationDelay((int)Animations::SKEL_MONSTA_DEATH, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::SKEL_MONSTA_DEATH, { i * n, n * 36, n, n });

    //BUB animations

    Anima->SetAnimationDelay((int)Animations::BUB_WALK_R, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_WALK_R, { i * n, n*37, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_WALK_L, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_WALK_L, { i * n, n*37, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_ATACK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_ATACK_R, { i * n, n*38, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_ATACK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_ATACK_L, { i * n, n*38, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_JUMP_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_JUMP_R, { i * n, n*39, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_JUMP_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_JUMP_L, { i * n, n*39, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_FALL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FALL_R, { i * n, n * 40, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_FALL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FALL_L, { i * n, n * 40, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUISH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUISH_R, { i * n, n*41, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUISH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUISH_L, { i * n, n*41, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUASH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUASH_R, { i * n, n*42, -n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_SQUASH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_SQUASH_L, { i * n, n*42, n, n });

    Anima->SetAnimationDelay((int)Animations::BUB_DEATH, ANIM_DELAY);
    for (i = 0; i < 13; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_DEATH, { i * n, n*43, n, n*2 });

    Anima->SetAnimationDelay((int)Animations::BUB_PUSH_BUTTON, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_PUSH_BUTTON, { i * n*2, n*45, n*2, n*2 });

    Anima->SetAnimationDelay((int)Animations::BUB_FIRE_DEATH, ANIM_DELAY);
    for (i = 0; i < 16; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_FIRE_DEATH, { i * n*2, n*47, n*2, n });

    Anima->SetAnimationDelay((int)Animations::BUB_LEVEL_TRANSITION, ANIM_DELAY);
    for (i = 0; i < 10; ++i)
        Anima->AddKeyFrame((int)Animations::BUB_LEVEL_TRANSITION, { i * n*2, n*48, n*2, n*2 });
    
    // Bob Animations

    Anima->SetAnimationDelay((int)Animations::BOB_WALK_R, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_WALK_R, { i * n, n * 50, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_WALK_L, ANIM_DELAY);
    for (i = 0; i < 7; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_WALK_L, { i * n, n * 50, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_ATACK_R, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_ATACK_R, { i * n, n * 51, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_ATACK_L, ANIM_DELAY);
    for (i = 0; i < 4; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_ATACK_L, { i * n, n * 51, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_JUMP_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_JUMP_R, { i * n, n * 52, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_JUMP_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_JUMP_L, { i * n, n * 52, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_FALL_R, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FALL_R, { i * n, n * 53, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_FALL_L, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FALL_L, { i * n, n * 53, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUISH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUISH_R, { i * n, n * 54, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUISH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUISH_L, { i * n, n * 54, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUASH_R, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUASH_R, { i * n, n * 55, -n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_SQUASH_L, ANIM_DELAY);
    for (i = 0; i < 3; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_SQUASH_L, { i * n, n * 55, n, n });

    Anima->SetAnimationDelay((int)Animations::BOB_DEATH, ANIM_DELAY);
    for (i = 0; i < 13; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_DEATH, { i * n, n * 56, n, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_PUSH_BUTTON, ANIM_DELAY);
    for (i = 0; i < 2; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_PUSH_BUTTON, { i * n * 2, n * 58, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BOB_FIRE_DEATH, ANIM_DELAY);
    for (i = 0; i < 16; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_FIRE_DEATH, { i * n * 2, n * 60, n * 2, n });

    Anima->SetAnimationDelay((int)Animations::BOB_LEVEL_TRANSITION, ANIM_DELAY);
    for (i = 0; i < 10; ++i)
        Anima->AddKeyFrame((int)Animations::BOB_LEVEL_TRANSITION, { i * n * 2, n * 61, n * 2, n * 2 });

    Anima->SetAnimationDelay((int)Animations::BUBBLE,ANIM_DELAY);
    for (i = 0; i < 10; ++i)
        Anima->AddKeyFrame((int)Animations::BUBBLE, { i * n * 2, n * 63, n * 2, n * 2 });

    return AppStatus::OK;
}
void Anim::SetAnimation(int id)
{
    Sprite* sprite = dynamic_cast<Sprite*>(render_);
    sprite->SetAnimation(id);
}