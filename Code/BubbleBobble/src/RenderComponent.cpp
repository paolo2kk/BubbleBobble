
#include "RenderComponent.h"
#include "raylib.h"

RenderComponent::~RenderComponent()
{
}
void RenderComponent::DrawBox(int x, int y, int w, int h, const Color& col) const
{
	Rectangle rc;

	rc.x = (float)x;
	rc.y = (float)y;
	rc.width = (float)w;
	rc.height = (float)h;

	DrawRectangleRec(rc, col);
}
void RenderComponent::DrawCorners(int x, int y, int w, int h) const
{
	int left, right, bottom, top;

	left = x;
	right = x + w - 1;
	top = y;
	bottom = y + h - 1;
	
	DrawPlus(left, bottom, 1, PINK);
	DrawPlus(right, bottom, 1, PINK);
	DrawPlus(left, top, 1, PINK);
	DrawPlus(right, top, 1, PINK);
}
void RenderComponent::DrawPlus(int x, int y, int radius, const Color& col) const
{
	int x1, y1, x2, y2;
	x1 = x - radius;
	x2 = x + radius;
	y1 = y - radius;
	y2 = y + radius;

	/* Well-known bug
	DrawLine(x1, y, x2, y, col);
	DrawLine(x, y1, x, y2, col);*/

	int i;
	for (i = x1; i <= x2; ++i)	DrawPixel(i, y, col);
	for (i = y1; i <= y2; ++i)	DrawPixel(x, i, col);
}