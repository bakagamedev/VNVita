#pragma once
#include "common.h"
#include "novelheader.h"
#include "imagecontrol.h"
#include "menupanel.h"

class NovelMain
{
private:
	std::string Path;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	ForegroundControl Foreground;
	BackgroundControl Background;
	MenuPanel Menu;

	NovelHeader Novel;
	void Tick(SceCtrlData GamePad,SceCtrlData GamePadLast);
	void Draw();
public:
	NovelMain(std::string LoadPath);
	~NovelMain();
	void Run();
};