#include "sprite.h"

UISprite::UISprite(const std::string& Path)
{
	vita2d_texture * SpritePointer = vita2d_load_PNG_file(Path.c_str());
	if(SpritePointer != NULL)
	{
		Sprite = std::shared_ptr<vita2d_texture>(SpritePointer, vita2d_free_texture);
	}
}

UISprite::UISprite(const std::string& Path, uint32_t Flags)
{	
	vita2d_texture * SpritePointer = vita2d_load_PNG_file(Path.c_str());

	if(SpritePointer != NULL)
	{
		Sprite = std::shared_ptr<vita2d_texture>(SpritePointer, vita2d_free_texture);
		SceGxmTextureFilter FlagCast = static_cast<SceGxmTextureFilter>(Flags);
		vita2d_texture_set_filters(SpritePointer, FlagCast, FlagCast);		
	}
}

int UISprite::GetWidth(void)
{
	return(vita2d_texture_get_width(Sprite.get()));
}
int UISprite::GetHeight(void)
{
	return(vita2d_texture_get_height(Sprite.get()));
}

void UISprite::Draw(int X, int Y)
{
	if(Sprite.get() != NULL)
		vita2d_draw_texture(Sprite.get(),X,Y);
}
void UISprite::DrawScaled(int X,int Y,float Scale)
{
	if(Sprite.get() != NULL)
		vita2d_draw_texture_scale(Sprite.get(),X,Y,Scale,Scale);
}