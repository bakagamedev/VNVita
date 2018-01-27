#pragma once
#include <vita2d.h>
#include <string>
#include <memory>

class UISprite
{
private:
	std::shared_ptr<vita2d_texture> texture;
public:
	UISprite(std::shared_ptr<vita2d_texture> Texture);	
	UISprite(const std::string& Path);
	UISprite(const std::string& Path, uint32_t Flags);

	void SetFlags(SceGxmTextureFilter MinFilter, SceGxmTextureFilter MagFilter);
	int GetWidth(void);
	int GetHeight(void);

	void Draw(int X,int Y);
	void DrawScaled(int X,int Y,float Scale);
};