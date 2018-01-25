#pragma once
#include "boxbase.h"
#include "textbox.h"

class UI
{
private:
	std::string StringBlob;
	std::vector<StringViewer> Backlog;

	bool menuOpen = false;
	bool backlogOpen = false;

	UIBoxBase UIbacklog = UIBoxBase(Rectangle(8,8,944,524));
	UITextBox UItextbox = UITextBox(Rectangle(0,344,960,200));
	UIBoxBase UIpanel   = UIBoxBase(Rectangle(0,0,128,544));

	SceCtrlData GamePad, GamePadLast;				
	vita2d_pgf * font = vita2d_load_default_pgf();	//Font!
public:
	UI();

	void PrintTextbox(std::string String);
	void Tick();
	void Draw();
};