#include "menupanel.h"

MenuPanel::MenuPanel()
{
	logoPointer = vita2d_load_PNG_file(ASSET_LogoSmall);
	this->LogoSmall = std::shared_ptr<vita2d_texture>(logoPointer, vita2d_free_texture);
}

void MenuPanel::Tick()
{
	if(Open)	X = std::max(X - SlideSpeed, -256.0f);
	else	X = std::min(X + SlideSpeed, 0.5f);
}

void MenuPanel::Draw()
{
	if(X >= 0)
		return;

	//Fade out background
	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, RGBA8(0,0,0, (int)-(X/2)));

	//Draw panel & border line
	vita2d_draw_rectangle(SCREEN_WIDTH + X, 0, 256, SCREEN_HEIGHT, RGBA8(114, 137, 217, 255));
	vita2d_draw_rectangle(SCREEN_WIDTH + X, 0, 3, SCREEN_HEIGHT, RGBA8(0,0,0, 255));

	//Draw logo at top
	if(logoPointer != NULL)
		vita2d_draw_texture(logoPointer,SCREEN_WIDTH + X, 0);
}