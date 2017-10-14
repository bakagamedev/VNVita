#pragma once
#include "common.h"

class ImageControl
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
	float Width,Height;
	vita2d_texture * imagePointer;
	std::shared_ptr<vita2d_texture> Image;

	void SetScreenSize(float Width, float Height)
	{
		this->Width = Width;
		this->Height = Height;
	}

	void SetImage(std::string Path)
	{
		Show = true;
		if(Path == "~")
		{
			Show = false;
		}
		if(Path != this->Path)
		{
			if(imagePointer != NULL)	//Clear current texture
			{
				vita2d_wait_rendering_done();
				vita2d_free_texture(imagePointer);
			}

			if(FileExists(Path))
			{
				if((Path.find(".jpg") != std::string::npos) || (Path.find(".JPG") != std::string::npos))
					imagePointer =  vita2d_load_JPEG_file(Path.c_str());
				if((Path.find(".png") != std::string::npos) || (Path.find(".PNG") != std::string::npos))
					imagePointer =  vita2d_load_PNG_file(Path.c_str());

				if(imagePointer != NULL)
				{
					vita2d_texture_set_filters(imagePointer, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
					Image = std::shared_ptr<vita2d_texture>(imagePointer, vita2d_free_texture);
				}
			}
		}
	}
};

class BackgroundControl : public ImageControl
{
public:
	void DrawBackground()
	{
		vita2d_texture * Back = Image.get();

		float BackgroundX = (960 - Width) / 2;	
		float BackgroundY = 0.0f;
		if((Show == false) || (Back == NULL))
		{
			//Draw black background and quit
			vita2d_draw_rectangle(BackgroundX, BackgroundY, Width, Height, RGBA8(100,0,0, 255));	//actually redish
			return;
		}

		float Scale = 544.0f / vita2d_texture_get_height(Back);
		vita2d_draw_texture_scale(Back,BackgroundX,BackgroundY,Scale,Scale);
	}
};

class ForegroundControl : public ImageControl
{
private:
	float X,Y;

public:
	void SetXY(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}

	void DrawForeground()
	{
		vita2d_texture * Fore = Image.get();

		if((Show == false) || (Fore == NULL))
		{
			return;
		}

		float Scale = 544.0f * (vita2d_texture_get_height(Fore) / Height);	// Screen size * (Sprite / DS Screen size) 
		vita2d_draw_texture_scale(Fore,X * Scale,Y * Scale,Scale,Scale);
	}
};