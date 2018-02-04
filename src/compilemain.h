#pragma once
#include "novelinfo.h"
#include "stringtable.h"
#include "stringhelpers.h"
#include "compilerloader.h"
#include "compiler.h"
#include "userinterface/progressbar.h"

class CompileMain
{
private:
	NovelInfo header;
	UIProgressbar progress;
	StringTable sourcefiles;

	CompilerLoader loader;
	Compiler compiler;


	void DetectVNDSScripts();
	void Draw();
public:
	CompileMain(NovelInfo header);
	void Run();
};
