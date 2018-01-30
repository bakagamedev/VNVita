#pragma once
#include "vita2d.h"

class UIProgressbar
{
private:
	float Percent;
public:
	void Draw(int x,int y, int Width,int Height);
	void SetPercent(const float Percent);
};

void UIProgressbar::SetPercent(const float Percent)
{
	this->Percent = Percent;
}

void UIProgressbar::Draw(int X, int Y, int Width, int Height)
{
	vita2d_draw_rectangle(X,Y,Width,Height,RGBA8(0,0,0,255));
	vita2d_draw_rectangle(X,Y,static_cast<int>(Width * Percent),Height,RGBA8(0,0,0,255));
}