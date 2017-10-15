#include "menupanel.h"

MenuPanel::MenuPanel()
{
	logoPointer = vita2d_load_PNG_file(ASSET_LogoSmall);
	this->LogoSmall = std::shared_ptr<vita2d_texture>(logoPointer, vita2d_free_texture);
}

MenuPanel::~MenuPanel()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

void MenuPanel::Tick()
{
	if(Open)	X = std::max(X - SlideSpeed, -256.0f);
	else	X = std::min(X + SlideSpeed, 0.5f);

	if(Open)
	{

	}
}

void MenuPanel::Draw()
{
	if(X >= 0)
		return;

	float Left = SCREEN_WIDTH + X;

	//Fade out background
	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, RGBA8(0,0,0, (int)-(X/2)));

	//Draw panel & border line
	vita2d_draw_rectangle(Left, 0, 256, SCREEN_HEIGHT, RGBA8(114, 137, 217, 255));
	vita2d_draw_rectangle(Left-2.0f, 0, 3, SCREEN_HEIGHT, RGBA8(0,0,0, 255));

	//Draw logo at top
	if(logoPointer != NULL)
		vita2d_draw_texture(logoPointer,Left, 0);

	std::vector<std::string> EverythingString = {"Quicksave","QuickLoad","Save","Load","Options","Hide","Exit"};

	for(int i=0; i<EverythingString.size(); ++i)
	{
		auto Colour = RGBA8(28,28,28,255);
		if(Selected == i)
		{
			Colour = RGBA8(255,255,255,255);
		}
		vita2d_pgf_draw_text(pgf, Left+8, 128 + (i*38), Colour, 2.0f, EverythingString[i].c_str());
	}


}