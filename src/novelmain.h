#pragma once
#include "common.h"

class NovelMain
{
private:
	std::string Path;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

public:
	NovelMain(std::string LoadPath);
	~NovelMain();
	void Run();
};