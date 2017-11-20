#pragma once
#include "novelheader.h"

class NovelMain
{
private:
	NovelHeader Header; 
public:
	NovelMain(NovelHeader Header);
	void Run();
};