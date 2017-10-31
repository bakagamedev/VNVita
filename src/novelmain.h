#pragma once
#include "common.h"
#include "novelheader.h"
#include "vndsparse.h"
#include "imagecontrol.h"
#include "textcontrol.h"
#include "menupanel.h"

class NovelMain
{
private:
	std::string Path;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	TextControl Text;
	ImageControl Images;

	VNDSParser Parser = VNDSParser(&Images, &Text);
	MenuPanel Menu = MenuPanel(&Parser);

	NovelHeader Novel;
	void Tick(SceCtrlData GamePad,SceCtrlData GamePadLast);
	void Draw();

	bool AutoMode = false;
public:
	NovelMain(std::string LoadPath);
	~NovelMain();
	void Run();
};