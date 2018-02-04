#include "progressbar.h"

void UIProgressbar::SetPercent(const float Percent)
{
	this->Percent = Percent;
}

void UIProgressbar::Draw(int X, int Y, int Width, int Height)
{
	vita2d_draw_rectangle(X,Y,Width,Height,RGBA8(20,20,20,255));
	vita2d_draw_rectangle(X,Y,static_cast<int>(Width * Percent),Height,RGBA8(255,255,255,255));
}