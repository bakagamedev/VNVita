#include "menupanel.h"

void MenuPanel::Tick()
{
	if(Open)	X = std::max(X - SlideSpeed, -256.0f);
	else	X = std::min(X + SlideSpeed, 0.5f);
}

void MenuPanel::Draw()
{
	if(X >= 0)
		return;

	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, RGBA8(0,0,0, (int)-(X/2)));

	vita2d_draw_rectangle(SCREEN_WIDTH + X, 0, 256, SCREEN_HEIGHT, RGBA8(114, 137, 217, 255));
	vita2d_draw_rectangle(SCREEN_WIDTH + X, 0, 3, SCREEN_HEIGHT, RGBA8(0,0,0, 255));
}