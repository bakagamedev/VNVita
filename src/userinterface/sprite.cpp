#include "sprite.h"

UISprite::UISprite(std::shared_ptr<vita2d_texture> Texture)
{
	this->texture = Texture;
}

UISprite::UISprite(const std::string& Path)
{
	vita2d_texture * texturePtr = vita2d_load_PNG_file(Path.c_str());
	if(texturePtr != nullptr)
	{
		texture = std::shared_ptr<vita2d_texture>(texturePtr, vita2d_free_texture);
	}
}

void UISprite::SetFlags(SceGxmTextureFilter MinFilter,SceGxmTextureFilter MagFilter)
{
	if(texture != nullptr)
		vita2d_texture_set_filters(texture.get(), MinFilter, MagFilter);		
}

bool UISprite::IsNull(void) const
{
	return (texture.get() == nullptr);
}

int UISprite::GetWidth(void) const
{
	return(vita2d_texture_get_width(texture.get()));
}
int UISprite::GetHeight(void) const
{
	return(vita2d_texture_get_height(texture.get()));
}

void UISprite::Draw(int X, int Y)
{
	if(texture.get() != nullptr)
		vita2d_draw_texture(texture.get(),X,Y);
}
void UISprite::DrawScaled(int X,int Y,float Scale)
{
	if(texture.get() != nullptr)
		vita2d_draw_texture_scale(texture.get(),X,Y,Scale,Scale);
}