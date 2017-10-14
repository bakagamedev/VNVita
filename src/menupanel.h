#pragma once
#include "common.h"

class MenuPanel
{
private:
	float X = 0;
	float SlideSpeed = 4.0f;
public:
	bool Open = false;
	void Draw();
	void Tick();
};