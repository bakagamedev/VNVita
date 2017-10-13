#pragma once
#include "common.h"

class NovelHeader
{
	private:
		vita2d_texture * LoadImageName(std::string Path)
		{
			//Takes name without type por exampler;  ux0:data/vnvita/saya no uta/icon
			//Priority : High PNG -> High JPG -> Base PNG -> Base PNG

			//JPEG Doesn't work at the moment. Find out why it crashes. 
			
			vita2d_texture* Texture;
			std::string PathTemp = Path;

			// High PNG
			Texture = vita2d_load_PNG_file((PathTemp.append("-high.png")).c_str());
			
			// High JPG
			if(Texture == NULL)
			{
				PathTemp = Path;
				PathTemp.append("-high.jpg");
				//Texture = vita2d_load_JPEG_file(PathTemp.c_str());
			}			

			// Low PNG
			if(Texture == NULL)
			{
				PathTemp = Path;
				PathTemp.append(".png");
				Texture = vita2d_load_PNG_file(PathTemp.c_str());
			}

			// Low JPG
			if(Texture == NULL)
			{
				PathTemp = Path;
				PathTemp.append(".jpg");
				//Texture = vita2d_load_JPEG_file(PathTemp.c_str());
			}

			return Texture;
		}

	public:
	NovelHeader(std::string Path)
	{
		this->Name = Path;
		this->Path = Path;

		//Icon
		vita2d_texture * iconPointer = LoadImageName(Path + "\\icon"); 
		if(iconPointer != NULL)
		{
			this->Icon = std::shared_ptr<vita2d_texture>(iconPointer, vita2d_free_texture);
		}

		//Thumbnail / Preview
		vita2d_texture * thumbPointer = LoadImageName(Path + "\\thumbnail"); 
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