#pragma once
#include "common.h"

class MenuPanel
{
private:
	vita2d_texture * logoPointer;
	std::shared_ptr<vita2d_texture> LogoSmall;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	float X = 0;
	float SlideSpeed = 8.0f;

	int Selected = 0;

public:
	MenuPanel();
	~MenuPanel();

	bool Open = false;
	void Draw();
	void Tick();
};