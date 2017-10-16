#include "textcontrol.h"

TextControl::TextControl()
{

}
TextControl::~TextControl()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);	//seriously, I know i'm doing this wrong.
}

void TextControl::SetNovelSize(float Width, float Height)
{
	this->Width = Width;
	this->Height = Height;
	Scale = SCREEN_HEIGHT / Height;
	X = (SCREEN_WIDTH - (Width*Scale)) / 2;	
}

void TextControl::SetAlpha(uint8_t Alpha)
{
	this->Alpha = Alpha;
}

void TextControl::SetBorderSize(float Border)
{
	this->Border = Border;
}

void TextControl::Draw()
{
	vita2d_draw_rectangle(X + Border,Y + Border,(Width*Scale)-(Border*2),(Height*Scale)-(Border*2), RGBA8(0,0,0,Alpha));

	const char * TextTemp = "Test words\nWords words words\nline 3\nNo Items, Fox Only, Final Destination";
	vita2d_pgf_draw_text(pgf, X + Border + 4, Y + Border + 32, RGBA8(0,0,0,255), 1.5f, TextTemp) ;
}