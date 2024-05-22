#pragma once
#include "RenderComponent.h"

class StaticImage : public RenderComponent
{
public:
    StaticImage(const Texture2D* texture, const Rectangle& rect);
    ~StaticImage();

    void Draw(int x, int y) const override;
    void DrawTint(int x, int y, const Color& col) const override;
    void Release() override;

private:
    Rectangle rc;
    const Texture2D* img;
};

