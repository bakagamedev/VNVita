#pragma once
#include "common.h"

class NovelHeader
{
public:
	NovelHeader(std::string Path)
	{
		this->Name = Name;
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
	std::list<NovelHeader> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

public:
	ErrorType StatusCode;
	NovelBrowser();
	void Run();
};