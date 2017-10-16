#pragma once
#include "common.h"

class MenuItem
{
public:
	std::string Title;
	std::function<void()> FunctionPointer;

	MenuItem(std::string Title, std::function<void()> FunctionPointer)
	{
		this->Title = Title;
		this->FunctionPointer = FunctionPointer;
	}
};

class MenuPanel
{
private:
	constexpr static const float PanelWidth = 256.0f; 
	vita2d_texture * logoPointer;
	std::shared_ptr<vita2d_texture> LogoSmall;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	std::vector<MenuItem> MenuItemList;

	float X = 0;
	float SlideSpeed = 8.0f;

	int ItemSelected = 0;

	//Callbacks
	static void MenuDoesNothing()	{};
	static void MenuExitNovel();

public:
	MenuPanel();
	~MenuPanel();

	bool Open = false;
	bool Active = false;
	void Draw();
	void Tick(SceCtrlData GamePad, SceCtrlData GamePadLast);
};