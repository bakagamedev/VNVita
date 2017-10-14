#pragma once
#include "common.h"

class NovelMain
{
private:
	std::string Path;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	///ForegroundControl ForeGround;
	//BackgroundControl BackGround;

	NovelHeader Novel;
	bool Tick(SceCtrlData GamePad,SceCtrlData GamePadLast);
	void Draw();
public:
	NovelMain(std::string LoadPath);
	~NovelMain();
	void Run();
};