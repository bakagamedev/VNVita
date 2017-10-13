#pragma once
#include "common.h"

class NovelMain
{
private:
	NovelHeader * NovelSelected;

public:
	NovelMain(NovelHeader * NovelSelected);
	bool Run();
};
