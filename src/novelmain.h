#pragma once
#include "novelheader.h"

class NovelMain
{
private:
	NovelHeader Header; 
public:
	StatusType StatusCode;

	NovelMain(NovelHeader Header);
	void Run();
};