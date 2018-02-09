#include "userinterface.h"

UI::UI()
{

}

bool UI::PressContinue(void)
{
	return (!backlogOpen && !menuOpen && (GamePad.buttons & SCE_CTRL_CROSS) & !(GamePadLast.buttons & SCE_CTRL_CROSS));
}

void UI::PrintTextbox(std::string String)
{
	StringViewer viewer = StringViewer(StringBlob.size(),String.size());
	StringBlob.append(String);
	UItextbox.Print(String);
}

void UI::Tick()
{
	sceCtrlPeekBufferPositive(0, &GamePad, 1);

	if((GamePad.buttons & SCE_CTRL_TRIANGLE) && ((GamePadLast.buttons & SCE_CTRL_TRIANGLE) == 0))
		menuOpen = !menuOpen;

	if(!menuOpen)
	{
		if((GamePad.buttons & SCE_CTRL_SQUARE) && ((GamePadLast.buttons & SCE_CTRL_SQUARE) == 0))
		{
			backlogOpen = !backlogOpen; 
		}
	}

}

void UI::TickEnd()
{
	GamePadLast = GamePad;
}

void UI::Draw() 
{
	if(backlogOpen)
		UIbacklog.DrawBox();
	else
		UItextbox.Draw();

	if(menuOpen)
		UIpanel.DrawBox();
}