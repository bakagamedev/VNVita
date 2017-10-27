#include "menupanel.h"

MenuPanel::MenuPanel()
{
	logoPointer = vita2d_load_PNG_file(ASSET_LogoSmall);
	this->LogoSmall = std::shared_ptr<vita2d_texture>(logoPointer, vita2d_free_texture);
	MenuItemList.emplace_back("Quicksave",DoesNothing);
	MenuItemList.emplace_back("Quickload",DoesNothing);
	MenuItemList.emplace_back("Save",DoesNothing);
	MenuItemList.emplace_back("Load",DoesNothing);
	MenuItemList.emplace_back("Options",DoesNothing);
	MenuItemList.emplace_back("Exit", [this]() { this->QuitNovel(); });
}

void MenuPanel::QuitNovel()
{
	State = MenuStateType::QuitNovel;
}

MenuPanel::~MenuPanel()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

MenuStateType MenuPanel::Tick(SceCtrlData GamePad, SceCtrlData GamePadLast)
{
	X = (Open) ? std::max(X - SlideSpeed, -PanelWidth) : std::min(X + SlideSpeed, 0.5f);
	Active = (X < -(PanelWidth/2));	//Enable controls if panel is at least half open

	if((Open) && (Active))
	{
		if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
		{
			ItemSelected = std::max(ItemSelected-1,0);
		}
		if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
		{
			ItemSelected = std::min(ItemSelected+1,((int)MenuItemList.size())-1);
		}

		if((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
		{
			std::function<void()> & FunctionPointer = MenuItemList[ItemSelected].FunctionPointer;
			FunctionPointer();
		}
	}

	return State;
}

void MenuPanel::Draw()
{
	if(X >= 0)
		return;

	float Left = SCREEN_WIDTH + X;

	//Fade out background
	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, RGBA8(0,0,0, (int)-(X/2)));

	//Draw panel & border line
	vita2d_draw_rectangle(Left, 0, PanelWidth, SCREEN_HEIGHT, COLOUR_UIBackground);
	vita2d_draw_rectangle(Left-2.0f, 0, 3, SCREEN_HEIGHT, COLOUR_UIBorder);

	//Draw logo at top
	if(logoPointer != NULL)
		vita2d_draw_texture(logoPointer,Left, 0);
	vita2d_draw_line(Left,96,Left + PanelWidth, 96, COLOUR_UIBorder);

	int Spacing = 42;
	for(int i=0; i<MenuItemList.size(); ++i)
	{
		auto Colour = (i == ItemSelected) ? COLOUR_UIBackgroundFocus : COLOUR_UIBackground;
		vita2d_draw_rectangle(Left, 96 + (i*Spacing), PanelWidth, Spacing, Colour);
		vita2d_draw_line(Left, 96 + ((i+1)*Spacing), Left+PanelWidth, 96 + ((i+1)*Spacing), COLOUR_UIBorder);
		vita2d_pgf_draw_text(pgf, Left+8, 128 + (i*Spacing), COLOUR_Font, 2.0f, MenuItemList[i].Title.c_str());
	}
}