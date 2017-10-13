#pragma once
#include "common.h"

class NovelMain
{
private:
	NovelHeader * NovelSelected;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

public:
	NovelMain(NovelHeader * NovelSelected);
	~NovelMain();
	void Run();
};
