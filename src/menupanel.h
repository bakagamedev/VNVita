#pragma once
#include "common.h"

class MenuPanel
{
private:
	vita2d_texture * logoPointer;
	std::shared_ptr<vita2d_texture> LogoSmall;

	float X = 0;
	float SlideSpeed = 4.0f;
public:
	MenuPanel();

	bool Open = false;
	void Draw();
	void Tick();
};