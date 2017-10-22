#pragma once
#include "common.h"
#include "novelheader.h"
#include <algorithm>
#include "stringhelpers.h"

enum class ViewModeType
{
	List,
	Grid,
};

class NovelBrowser
{
private:
	SceCtrlData GamePad, GamePadLast;
	void Search(std::string SearchPath);
	std::vector<NovelHeader> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	int ItemSelected = 0;
	float ScrollY = 0;
	int Scroll = 0;
	int GridPerLine = 5;
public:
	StatusType StatusCode;
	
	NovelBrowser();
	~NovelBrowser();
	
	std::string Run();

	bool Tick(ViewModeType &ViewMode);
	void DrawList();
	void DrawGrid();
};