#pragma once
#include "common.h"

class NovelBrowser
{
private:
	void Search(std::string SearchPath);
	std::vector<NovelHeader> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	int ItemSelected = 0;
public:
	StatusType StatusCode;
	
	NovelBrowser();
	~NovelBrowser();
	
	std::string Run();
};