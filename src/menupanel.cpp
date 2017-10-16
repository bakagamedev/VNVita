#include "menupanel.h"

MenuPanel::MenuPanel()
{
	logoPointer = vita2d_load_PNG_file(ASSET_LogoSmall);
	this->LogoSmall = std::shared_ptr<vita2d_texture>(logoPointer, vita2d_free_texture);

	MenuItemList.emplace_back("Quicksave",MenuDoesNothing);
	MenuItemList.emplace_back("Quickload",MenuDoesNothing);
	MenuItemList.emplace_back("Save",MenuDoesNothing);
	MenuItemList.emplace_back("Load",MenuDoesNothing);
	MenuItemList.emplace_back("Options",MenuDoesNothing);
	MenuItemList.emplace_back("Exit",MenuDoesNothing);
}

void MenuPanel::MenuExitNovel()
{
	//
}

MenuPanel::~MenuPanel()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

void MenuPanel::Tick(SceCtrlData GamePad, SceCtrlData GamePadLast)
{
	constexpr static const float PanelWidth = 256.0f; 
	X = (Open) ? std::max(X - SlideSpeed, -PanelWidth) : std::min(X + SlideSpeed, 0.5f);
	Active = (X < -(PanelWidth/2));	//Enable controls if panel is at least half open

	if((Open) && (Active))
	{
		if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
		{
			Selected = std::max(Selected-1,0);
		}
		if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
		{
			Selected = std::min(Selected+1,((int)MenuItemList.size())-1);
		}

		if((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
		{
			std::function<void()> FunctionPointer = MenuItemList[Selected].FunctionPointer;
			FunctionPointer();
		}
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
	vita2d_draw_rectangle(Left, 0, 256, SCREEN_HEIGHT, COLOUR_UIBackground);
	vita2d_draw_rectangle(Left-2.0f, 0, 3, SCREEN_HEIGHT, COLOUR_UIBorder);

	//Draw logo at top
	if(logoPointer != NULL)
		vita2d_draw_texture(logoPointer,Left, 0);

	for(int i=0; i<MenuItemList.size(); ++i)
	{
		auto Colour = (i == Selected) ? COLOUR_Selected : COLOUR_Deselected;
		vita2d_pgf_draw_text(pgf, Left+8, 128 + (i*38), Colour, 2.0f, MenuItemList[i].Title.c_str());
	}


}