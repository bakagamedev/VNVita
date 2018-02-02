#pragma once
#include "novelinfo.h"
#include "stringtable.h"
#include "stringhelpers.h"
#include "userinterface/progressbar.h"

class CompileMain
{
private:
	NovelInfo header;
	UIProgressbar progress;

	StringTable sourcefiles;

	void DetectVNDS();
	void Draw();
public:
	CompileMain(NovelInfo header);
	void Run();
};
