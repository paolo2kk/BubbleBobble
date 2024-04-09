#include "Sprite.h"

Sprite::Sprite(const Texture2D * texture)
{
    img = texture;
    current_anim = -1;
    current_frame = 0;
    current_delay = 0;
}
Sprite::~Sprite()
{
    Release();
}
void Sprite::SetNumberAnimations(int num)
{
    animations.clear();
    animations.resize(num);
}
void Sprite::SetAnimationDelay(int id, int delay)
{
    if (id >= 0 && id < animations.size())
    {
        animations[id].delay = delay;
    }
}
void Sprite::AddKeyFrame(int id, const Rectangle& rect)
{
    if (id >= 0 && id < animations.size())
    {
        animations[id].frames.push_back(rect);
    }
}
void Sprite::SetAnimation(int id)
{
    if (id >= 0 && id < animations.size())
    {
        current_anim = id;
        current_frame = 0;
        current_delay = animations[current_anim].delay;
    }
}
int Sprite::GetAnimation()
{
    return current_anim;
}
void Sprite::SetManualMode()
{
    mode = AnimMode::MANUAL;
}
void Sprite::SetAutomaticMode()
{
    mode = AnimMode::AUTOMATIC;
}
void Sprite::Update()
{
    ////Both animation modes (automatic and manual) are carry out with animation delay
    //if (current_delay > 0)
    //{
    //    current_delay--;
    //    if (current_delay == 0)
    //    {
    //        //Only automatic animation mode advances next frame
    //        if (mode == AnimMode::AUTOMATIC)
    //        {
    //            current_frame++;
    //            current_frame %= animations[current_anim].frames.size();
    //            current_delay = animations[current_anim].delay;
    //        }
    //    }
    //}
}
void Sprite::NextFrame()
{
    //Next frame is only available in manual animation mode
    if (mode == AnimMode::MANUAL)
    {
        current_delay--;
        if (current_delay <= 0)
        {
            current_frame++;
            current_frame %= animations[current_anim].frames.size();
            current_delay = animations[current_anim].delay;
        }
    }   
}
void Sprite::PrevFrame()
{
    //Previous frame is only available in manual animation mode
    if (mode == AnimMode::MANUAL)
    {
        current_delay--;
        if (current_delay <= 0)
        {
            current_frame--;
            current_frame %= animations[current_anim].frames.size();
            current_delay = animations[current_anim].delay;
        }
    }
}
void Sprite::Draw(int x, int y) const
{
    DrawTint(x, y, WHITE);
}
void Sprite::DrawTint(int x, int y, const Color& col) const
{
    if (current_anim >= 0 && current_anim < animations.size())
    {
        Rectangle rect = animations[current_anim].frames[current_frame];
        DrawTextureRec(*img, rect, { (float)x, (float)y }, col);
    }
}
void Sprite::Release()
{
    //Release each animation's frames
    for (auto& animation : animations)
    {
        animation.frames.clear();
    }
    //Clear the animations vector
    animations.clear();
}
