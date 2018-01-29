#include "novelmain.h"

NovelMain::NovelMain(NovelInfo header)
{
	this->header = header;
	StatusCode = StatusType::OK;

	std::string StartFile = header.Path + "\\compiled\\main.txt";

	ui = UI();
	codeLoader = CodeLoader(header);
	//stringLoader = StringLoader(header.)
	codeReader = codeLoader.Load(StartFile);
	processor = Processor(codeReader,codeLoader,stringLoader);
}

NovelMain::~NovelMain()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

void NovelMain::Run()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	sceCtrlPeekBufferPositive(0, &GamePad, 1);

	//Move button press logic to UI
	if(ui.PressContinue() && (GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
	{
		processor.Process();
		vita2d_pgf_draw_text(pgf, 45,45,RGBA8(255,0,0,255), 3.0f, "Hit!");
	}
	GamePadLast = GamePad;

	vita2d_pgf_draw_text(pgf, 0,25,RGBA8(255,255,0,255), 1.0f, header.Title.c_str());

	std::string StackDrawy = "";
	for(auto i=0; i<5; ++i)
	{
		char TempString[10];
		sprintf(TempString,"%u",codeReader.data[i]);
		StackDrawy.append(TempString);
	}
	vita2d_pgf_draw_text(pgf, 0,125,RGBA8(255,255,0,255), 1.0f, StackDrawy.c_str());
	{
		char TempString[10];
		sprintf(TempString,"Index : %u",codeReader.index);
		TempString[9] = 0x00;
		vita2d_pgf_draw_text(pgf, 0,145,RGBA8(255,255,0,255), 1.0f, TempString);
	}

	{
		char TempString[10];
		sprintf(TempString,"SS : %u",processor.stack.size());
		TempString[9] = 0x00;
		vita2d_pgf_draw_text(pgf, 0,225,RGBA8(255,255,0,255), 1.0f, TempString);
	}

	ui.Tick();
	ui.Draw();

	vita2d_end_drawing();
	vita2d_swap_buffers();
}