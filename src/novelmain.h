#pragma once
#include "defines.h"
#include "novelheader.h"

class NovelMain
{
private:
	NovelHeader Header; 

	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	SceCtrlData GamePad, GamePadLast;
public:
	StatusType StatusCode;

	NovelMain(NovelHeader Header);
	~NovelMain();
	void Run();
};