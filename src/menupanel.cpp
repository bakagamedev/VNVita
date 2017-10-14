#include "menupanel.h"

void MenuPanel::Tick()
{
	if(Show)	X = std::max(X - SlideSpeed, -256.0f);
	else	X = std::min(X + SlideSpeed, 0.5f);
}

void MenuPanel::Draw()
{
	if(X < 0)
	{
		vita2d_draw_rectangle(960 - X, 0, 256, 544, RGBA8(114, 137, 217, 255));
	}
}