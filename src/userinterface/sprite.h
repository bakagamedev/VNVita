#pragma once
#include <vita2d.h>
#include <string>
#include <memory>

class UISprite
{
private:
	std::shared_ptr<vita2d_texture> Sprite;
public:
	UISprite(std::string Path);
	UISprite(std::string Path, uint32_t Flags);

	int GetWidth(void);
	int GetHeight(void);

	void Draw(int X,int Y);
	void DrawScaled(int X,int Y,float Scale);
	
};