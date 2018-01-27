#include "animatedsprite.h"

UIAnimatedSprite::UIAnimatedSprite(const std::string& firstImage,int FrameMilliseconds)
{
	this->FrameMilliseconds = FrameMilliseconds;
	LoadFrameFromFile(firstImage);
}
UIAnimatedSprite::UIAnimatedSprite(std::initializer_list<std::string> initialiser)
{
	for(auto & value : initialiser)
	{
		LoadFrameFromFile(value);
	}
}
UIAnimatedSprite::UIAnimatedSprite(SpriteType Texture)
{
	this->FrameList.push_back(Texture);
}

UIAnimatedSprite::UIAnimatedSprite(std::initializer_list<SpriteType> initialiser)
{
	for(auto & value : initialiser)
	{
		this->FrameList.push_back(value);
	}
}

void UIAnimatedSprite::SetFrameTime(uint64_t FrameMilliseconds)
{
	this->FrameMilliseconds = FrameMilliseconds;
	//frameTimer.Timer(1000*FrameMilliseconds);
}

void UIAnimatedSprite::LoadFrameFromFile(const std::string& Path)
{
	vita2d_texture * SpritePointer = vita2d_load_PNG_file(Path.c_str());
	if(SpritePointer != NULL)
	{
		SpriteType Sprite = SpriteType(SpritePointer,vita2d_free_texture);
		FrameList.push_back(Sprite);
	}
}

int UIAnimatedSprite::GetFrameCount(void) const
{
	return FrameList.size();
}

void UIAnimatedSprite::Draw(int X,int Y)
{
	frameTimer.update();
	if(frameTimer.HasDurationElapsed())
	{
		FrameCurrent++;
		if(FrameCurrent>=GetFrameCount())
		{
			FrameCurrent = 0;
		}

		frameTimer.reset();
	}
	DrawFrame(X,Y,FrameCurrent);
}

void UIAnimatedSprite::DrawFrame(int X,int Y,uint16_t Frame)
{
	auto Sprite = FrameList[FrameCurrent].get();
	if(Sprite != NULL)
		vita2d_draw_texture(Sprite,X,Y);
}