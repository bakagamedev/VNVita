#pragma once
#include <vita2d.h>
#include <string>
#include <memory>

class UISprite
{
private:
	std::shared_ptr<vita2d_texture> texture;
public:
	UISprite(void) = default;
	UISprite(std::shared_ptr<vita2d_texture> Texture);	
	UISprite(const std::string& Path);
	UISprite(const std::string& Path, uint32_t Flags);

	bool IsNull(void) const;

	void SetFlags(SceGxmTextureFilter MinFilter, SceGxmTextureFilter MagFilter);
	int GetWidth(void) const;
	int GetHeight(void) const;

	void Draw(int X,int Y);
	void DrawScaled(int X,int Y,float Scale);
};