#include "StaticImage.h"

StaticImage::StaticImage(const Texture2D* texture, const Rectangle& rect)
{
	img = texture;
	rc = rect;
}
StaticImage::~StaticImage()
{
}
void StaticImage::Draw(int x, int y) const
{
	DrawTint(x, y, WHITE);
}
void StaticImage::DrawTint(int x, int y, const Color& col) const
{
	DrawTextureRec(*img, rc, { (float)x, (float)y }, col);
}
void StaticImage::Release()
{
}