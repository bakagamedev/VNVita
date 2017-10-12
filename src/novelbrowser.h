#pragma once
#include "common.h"

class NovelHeader
{
	public:
	NovelHeader(std::string Path)
	{
		this->Name = Path;
		this->Path = Path;

		//Check if file exists before read?
		std::string IconPath = Path.c_str();
		IconPath.append("\\icon.png");
		auto iconPointer = vita2d_load_PNG_file(IconPath.c_str());
		if(iconPointer != NULL)
		{
			this->Icon = std::shared_ptr<vita2d_texture>(iconPointer, vita2d_free_texture);
		}
		//Thumbnail
		std::string ThumbPath = Path.c_str();
		ThumbPath.append("\\thumbnail.png");
		auto thumbPointer = vita2d_load_PNG_file(ThumbPath.c_str());
		if(thumbPointer != NULL)
		{
			this->Thumbnail = std::shared_ptr<vita2d_texture>(thumbPointer, vita2d_free_texture);
		}
	}	

	std::string Name;
	std::string Path;
	std::shared_ptr<vita2d_texture> Icon;
	std::shared_ptr<vita2d_texture> Thumbnail;
};

class NovelBrowser
{
private:
	void Search(std::string SearchPath);
	std::vector<NovelHeader> NovelList;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	int ItemSelected = 0;
public:
	StatusType StatusCode;
	std::string LoadPath;
	
	NovelBrowser();
	~NovelBrowser();
	
	void Run();
};