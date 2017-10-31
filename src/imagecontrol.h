#pragma once
#include "common.h"

class ImageBase
{		
private:
	bool FileExists(std::string Path)
	{
		SceIoStat StatTemp;
		return (sceIoGetstat(Path.c_str(), &StatTemp) >= 0);
	}
public:
	std::string Path;
	bool Show;
	float ScreenWidth = SCREEN_WIDTH;
	float ScreenHeight = SCREEN_HEIGHT;
	float NovelWidth = 256;
	float NovelHeight = 196;
	float Scale = 1.0f;
	std::shared_ptr<vita2d_texture> Image;

	virtual ~ImageBase() = default;

	void SetScreenSize(float Width, float Height)
	{
		this->ScreenWidth = Width;
		this->ScreenHeight = Height;
		Scale = ScreenHeight / NovelHeight;
	}

	void SetNovelSize(float Width, float Height)
	{
		this->NovelWidth = Width;
		this->NovelHeight = Height;
		Scale = ScreenHeight / NovelHeight;
	}

	void LoadImage(const std::string Path)
	{
		Show = true;
		if(Path == "~")
		{
			Show = false;
		}
		if(Path != this->Path)
		{
			vita2d_wait_rendering_done();
			if(FileExists(Path))
			{
				vita2d_texture * imagePointer = NULL;

				if((Path.find(".jpg") != std::string::npos) || (Path.find(".JPG") != std::string::npos))
					imagePointer =  vita2d_load_JPEG_file(Path.c_str());
				if((Path.find(".png") != std::string::npos) || (Path.find(".PNG") != std::string::npos))
					imagePointer =  vita2d_load_PNG_file(Path.c_str());

				if(imagePointer != NULL)
				{
					vita2d_texture_set_filters(imagePointer, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
					Image = std::shared_ptr<vita2d_texture>(imagePointer, vita2d_free_texture);
				}
				else
				{
					imagePointer =  vita2d_load_PNG_file(ASSET_NoAsset);
					Image = std::shared_ptr<vita2d_texture>(imagePointer, vita2d_free_texture);
				}
			}
		}
	}
};

class BackgroundControl : public ImageBase
{
private:
public:
	void SetImage(const std::string Path)
	{
		LoadImage(Path);
	}

	void Draw()
	{
		float BackgroundY = 0.0f;
		float BackgroundX = (ScreenWidth - (NovelWidth*Scale)) / 2;	
		if((Show == false) || (Image.get() == NULL))
		{
			//Draw black background and quit
			vita2d_draw_rectangle(BackgroundX, BackgroundY, NovelWidth * Scale, NovelHeight * Scale, RGBA8(16,16,16, 255));	//actually redish 
			return;
		}

		if(Image.get() != NULL)
		{
			vita2d_draw_texture_scale(Image.get(), BackgroundX, BackgroundY, Scale, Scale);
		}
	}
	void DrawBorders()
	{
		float BackgroundX = (ScreenWidth - (NovelWidth*Scale)) / 2;	
		vita2d_draw_rectangle(0,0, BackgroundX, ScreenHeight, RGBA8(0,0,0, 255));	//Cover up sides
		vita2d_draw_rectangle(BackgroundX + (NovelWidth*Scale),0, BackgroundX, ScreenHeight, RGBA8(0,0,0, 255));	
	}
};

class ForegroundControl : public ImageBase
{
private:
	float X,Y;

public:
	ForegroundControl(const std::string Path)
	{
		SetImage(Path);
	}
	ForegroundControl(const std::string Path, float x, float y)
	{
		SetImage(Path);
		SetPosition(x,y);
	}
	ForegroundControl(void) = default;

	void SetImage(const std::string Path)
	{
		LoadImage(Path);
	}
	void SetPosition(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}

	void Draw()
	{
		if((Show == false) || (Image.get() == NULL))
		{
			return;
		}

		float Left = (ScreenWidth - (NovelWidth*Scale)) / 2;	
		float PointScale = Scale*(NovelHeight/192);	//Transform from NDS size -> novel size -> Screen size

		if(Image.get() != NULL)
		{
			vita2d_draw_texture_scale(Image.get(), Left + (X * PointScale), Y * PointScale, Scale, Scale);
		}

	}
};

class ImageControl
{
private:
	int NovelWidth = 256;
	int	NovelHeight = 192;

public:
	int BackgroundWait = -1;
	BackgroundControl Background;
	std::list<ForegroundControl> ForegroundList;

	void Draw()
	{
		Background.Draw();
		if(ForegroundList.size() > 0)
		{
			for(ForegroundControl Image : ForegroundList)
			{
				Image.Draw();
			}
		}
		Background.DrawBorders();
	}

	void BgLoad(std::string Path, int Delay)
	{
		ImageClear();	//Bg's hide sprites
		Background.SetImage(Path);
		BackgroundWait = Delay;
	}
	void BgLoad(std::string Path)
	{
		ImageClear();
		Background.SetImage(Path);
	}

	void ImageClear()
	{
		ForegroundList.clear();
	}
	void SetImage(const std::string Path,const float x,const float y)
	{
		if(Path == "~")
		{
			ImageClear();
		}
		else
		{
			ForegroundList.push_back(ForegroundControl(Path,x,y));
			ForegroundList.back().SetNovelSize(NovelWidth,NovelHeight);
		}
	}

	void SetNovelSize(const int Width, const int Height)
	{
		NovelWidth = Width;
		NovelHeight = Height;
		Background.SetNovelSize(Width,Height);
	}
};