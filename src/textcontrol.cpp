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

void TextControl::ScrollUp()
{
	Scroll = std::max(Scroll-1,MaxLines - (int)(TextList.size()));
}

void TextControl::ScrollDown()
{
	Scroll = std::min(Scroll+1,0);
	if((int)TextList.size() < MaxLines)
		Scroll = 0;
}

void TextControl::Tick(bool Continue)
{
	if(TextList.size() == 0)
	    return;
	if(Scroll != 0)
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
			int listStart = Size-MaxLines;
			int listEnd = Size-1;
			if(Scroll != 0)
			{
				listStart += Scroll;
				listEnd += Scroll+1;	// +1 so it goes into current line position
			}
			listStart = std::max(0,listStart);
    		listEnd = std::min(listEnd,Size);

			offset = std::max(0,(MaxLines - Size) * Spacing);	//Pad it so current line is at the bottom of the screen
		    for(int i=listStart; i<listEnd; ++i)
		    {
				vita2d_pgf_draw_text(pgf, X + Border + 8, Y + Border + 20 + offset + (Spacing/2), RGBA8(128,128,255,255), 1.5f, TextList[i].c_str());
				offset += Spacing;
		    }
		}
		else
		{
			offset = (MaxLines-1)*Spacing;	//If there's nothing before current line, move it to bottom.
		}

		if((Size > 0) && (Scroll == 0))	//Current line
		{
			std::string Line = TextList[Size - 1];
			Line.erase(CharsDisplay, std::string::npos);
			vita2d_pgf_draw_text(pgf, X + Border + 8, Y + Border + 20 + offset + (Spacing/2), RGBA8(255,255,255,255), 1.5f, Line.c_str());
		}

		vita2d_disable_clipping();
	}
}
