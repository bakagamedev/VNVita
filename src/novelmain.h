#pragma once
#include "defines.h"
#include "userinterface/userinterface.h"
#include "processor.h"
#include "header.h"

class NovelMain
{
private:
	NovelHeader  header; 
	CodeLoader	 codeLoader;
	CodeReader 	 codeReader;
	StringLoader stringLoader;
	Processor 	 processor;
	UI ui;

	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	SceCtrlData GamePad, GamePadLast;
public:
	StatusType StatusCode;

	NovelMain(NovelHeader header);
	~NovelMain();
	void Run();
};