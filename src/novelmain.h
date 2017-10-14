#pragma once
#include "common.h"
#include "imagecontrol.h"

class NovelMain
{
private:
	std::string Path;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	ForegroundControl Foreground;
	BackgroundControl Background;

	NovelHeader Novel;
	bool Tick(SceCtrlData GamePad,SceCtrlData GamePadLast);
	void Draw();
public:
	NovelMain(std::string LoadPath);
	~NovelMain();
	void Run();
};