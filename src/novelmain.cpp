#include "novelmain.h"

NovelMain::~NovelMain()
{
}

NovelMain::NovelMain(std::string LoadPath)
{
	this->Path = LoadPath;
	Novel.Reset(Path,false);

	Parser.SetPath(Path);
	Parser.SetFile("main.scr");

	Images.SetNovelSize(Novel.Width,Novel.Height);
	//Text.SetNovelSize(Novel.Width,Novel.Height);
	Text.SetNovelSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	Text.SetBorderSize(0);
}

void NovelMain::Tick(SceCtrlData GamePad,SceCtrlData GamePadLast)
{
	bool Up = false;
	bool Down = false;
	if((GamePad.buttons & SCE_CTRL_CIRCLE) && ((GamePadLast.buttons & SCE_CTRL_CIRCLE) == 0))
	{
	} 	
	if((GamePad.buttons & SCE_CTRL_START) && ((GamePadLast.buttons & SCE_CTRL_START) == 0))
	{
	} 
	if((GamePad.buttons & SCE_CTRL_SQUARE) && ((GamePadLast.buttons & SCE_CTRL_SQUARE) == 0))
	{
		Text.Show = !Text.Show;
	} 

	if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
	{
		Up = true;
	} 
	if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
	{
		Down = true;
	} 

	if((GamePad.buttons & SCE_CTRL_LTRIGGER ) && ((GamePadLast.buttons & SCE_CTRL_LTRIGGER ) == 0))
	{
		AutoMode = !AutoMode;
	}

	bool Pressed = ((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0));
	bool TextGo = Pressed;
	if(!Text.QuestionActive)	{	TextGo = (Pressed || AutoMode);	}
	Text.Tick(TextGo, Up, Down);

	bool ParserReady = (Pressed || AutoMode);
	if(!Text.Ready)	{	ParserReady = false;	}
	Parser.Tick(ParserReady);
}

void NovelMain::Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	Images.Draw();
	Text.Draw();
	//UI Draw
	Menu.Draw();

	vita2d_end_drawing();
	vita2d_swap_buffers();
} 

void NovelMain::Run()
{
	SceCtrlData GamePad, GamePadLast;
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!
	
	bool Finished = false;
	while(!Finished)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);
		
		if((GamePad.buttons & SCE_CTRL_TRIANGLE) && ((GamePadLast.buttons & SCE_CTRL_TRIANGLE) == 0))
		{
			Menu.Open = !Menu.Open;
		}

		MenuStateType MenuState = Menu.Tick(GamePad,GamePadLast);
		if(MenuState == MenuStateType::QuitNovel)
		{
			break;
		}

		if(!Menu.Active)
			Tick(GamePad,GamePadLast);

		Finished = ((Parser.IsFinished()) && (Text.Ready));	//End when novel ends and nothing is being printed

		Draw();

		GamePadLast = GamePad;
	}

	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}