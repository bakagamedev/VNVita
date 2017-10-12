#pragma once
#include "common.h"

class NovelHeader
{
public:
	NovelHeader(std::string Path)
	{
		this->Name = Path;
		this->Path = Path;
		//Icon = vita2d_load_JPEG_file(Path + "icon.png");
	}
	~NovelHeader()
	{
		//vita2d_free_texture(Icon);
	}

	std::string Name;
	std::string Path;
	vita2d_texture *Icon;
};

class NovelBrowser
{
private:
	std::vector<NovelHeader> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	int ItemSelected = 0;
public:
	ErrorType StatusCode;
	NovelBrowser();
	~NovelBrowser();
	
	void Run();
};