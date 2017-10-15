#pragma once
#include "common.h"

class MenuOptionType
{
public:
	std::string Title;
	std::function<void()> FunctionPointer;

	MenuOptionType(std::string Title, std::function<void()> FunctionPointer)
	{
		this->Title = Title;
		this->FunctionPointer = FunctionPointer;
	}
};

class MenuPanel
{
private:
	vita2d_texture * logoPointer;
	std::shared_ptr<vita2d_texture> LogoSmall;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	std::vector<MenuOptionType> MenuOptions;

	float X = 0;
	float SlideSpeed = 8.0f;

	int Selected = 0;

	//Callbacks
	static void MenuDoesNothing()	{};
	void MenuExitNovel();

public:
	MenuPanel();
	~MenuPanel();

	bool Open = false;
	void Draw();
	void Tick(SceCtrlData GamePad, SceCtrlData GamePadLast);
};