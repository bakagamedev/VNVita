#pragma once
#include "common.h"

class MenuPanel
{
private:
	float X = 0;
	float SlideSpeed = 4.0f;
public:
	bool Show = false;

	void Draw();
	void Tick();
};