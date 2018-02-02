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
