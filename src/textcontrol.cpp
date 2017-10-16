#include "textcontrol.h"

TextControl::TextControl()
{
}
TextControl::~TextControl()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);	//seriously, I know i'm doing this wrong.
}

void TextControl::TextAdd(std::string Text)
{
	TextList.push_back(Text);
	CharsDisplay = 0;
	Ready = false;
}

void TextControl::TextClear()
{
	TextList.clear();
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

void TextControl::Tick(bool Continue)
{
	if(TextList.size() == 0)
	    return;

	auto CurrentLine = TextList[std::max(0,(int)TextList.size()-1)];
	int LineLength = CurrentLine.size();
	if(CharsDisplay < LineLength)
	{
	    CharsDisplay = std::min(++CharsDisplay,LineLength);
	    Ready = false;
	}
	else
	{
	    Ready = Continue;
	}
}

void TextControl::Draw()
{
	if(Show)
	{
		auto Spacing = 35;
		vita2d_draw_rectangle(X + Border,Y + Border,(Width*Scale)-(Border*2),(Height*Scale)-(Border*2), RGBA8(0,0,0,Alpha));

		vita2d_set_clip_rectangle(X + Border, Y + Border, X + Border + ((Width*Scale) - (Border*2)), Y + Border + (Height*Scale) - (Border*2));
		vita2d_enable_clipping();

		int offset = 0;
		int Size = TextList.size();
		if(Size > 1)	//If there is a backlog
		{
		    for(int i=0; i<(Size-1); ++i)
		    {
				vita2d_pgf_draw_text(pgf, X + Border + 8, Y + Border + 8 + offset + (Spacing/2), RGBA8(128,128,255,255), 1.5f, TextList[i].c_str());
				offset += Spacing;
		    }
		}
		if(Size > 0)	//Current line
		{
			std::string Line = TextList[Size - 1];
			Line.erase(CharsDisplay, std::string::npos);
			vita2d_pgf_draw_text(pgf, X + Border + 8, Y + Border + 8 + offset + (Spacing/2), RGBA8(255,255,255,255), 1.5f, Line.c_str());
		}

		vita2d_disable_clipping();
	}
}
