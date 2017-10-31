#include "textcontrol.h"

TextControl::TextControl()
{
	ptrArrowUp = vita2d_load_PNG_file(ASSET_ArrowUp);
	ImgArrowUp = std::shared_ptr<vita2d_texture>(ptrArrowUp, vita2d_free_texture);
	ptrArrowDown = vita2d_load_PNG_file(ASSET_ArrowDown);
	ImgArrowDown = std::shared_ptr<vita2d_texture>(ptrArrowDown, vita2d_free_texture);

	X = 0;
	Y = 0;
	Width = SCREEN_WIDTH;
	Height = SCREEN_HEIGHT;
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
	Y = 0;
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


void TextControl::ScrollClamp()
{
	Scroll = std::min(std::max(Scroll,-((int)TextList.size())-1),0);
}
void TextControl::ScrollUp()
{
	--Scroll;
	ScrollClamp();
}

void TextControl::ScrollDown()
{
	++Scroll;
	ScrollClamp();
}

void TextControl::Tick(bool Continue)
{
	int Size = TextList.size();
	if(Size == 0)
	{
		Ready = true;
		return;
	}

	Ready = false;
	auto String = TextList[Size-1];
	if(CharsDisplay < String.size())  
	{ 
	    ++CharsDisplay;
	}
	else
	{
		if(Continue)
			Ready = true;
	}

	if(Scroll != 0)
	    Ready = false;
}
	
void TextControl::SetQuestion(const std::string Text)
{
	QuestionText = Text;
	QuestionActive = true;
}
void TextControl::EndQuestion()
{
	QuestionActive = false;
}

void TextControl::Draw()
{
	if(Show)
	{
		int MaxCharsPerLine = 68;//44;	//Guess.
		int CharHeight = 26;	//Guess. Not sure how to get this value.
		int DrawOffset = 20;	//Because vita2d's text drawing is wonky
		MaxLines = (Height / CharHeight)+1;	//Lines on screen at once

		int TextY = Height + DrawOffset;
		int Size = TextList.size();
		if(Size > 0)
		{
			if(QuestionActive)
			{
				auto Colour = RGBA8(255,255,0,255);	//Yellow
				TextY -= CharHeight*((std::count(QuestionText.begin(), QuestionText.end(), '\n'))+1);	//Number of answers
				vita2d_pgf_draw_text(pgf,X + Border, TextY, Colour, 1.5f, QuestionText.c_str());
			}
			if((Scroll == 0) && (SmallMode = true))
			{
				auto Colour = RGBA8(255,255,255,255);	//White
				auto String = TextList[Size-1];
				String = stringwrap(String,MaxCharsPerLine);
				TextY -= CharHeight*((std::count(String.begin(), String.end(), '\n'))+1);
				String.resize(CharsDisplay);

				vita2d_draw_rectangle(X + Border, TextY - CharHeight,(Width*Scale)-(Border*2), SCREEN_HEIGHT, RGBA8(0,0,0,Alpha));
				vita2d_pgf_draw_text(pgf, X,TextY,Colour, 1.5f, String.c_str());
			}
			else	//Large box
			{
				vita2d_draw_rectangle(X + Border,Y + Border,(Width*Scale)-(Border*2),(Height*Scale)-(Border*2), RGBA8(0,0,0,Alpha));
				int ListMax = std::max((Size+Scroll)-1,0);
				int ListMin = std::max(ListMax - MaxLines,0);

				for(int i=ListMax; i>=ListMin; --i)
				{
					auto String = TextList[i];
					String = stringwrap(String,MaxCharsPerLine);
					TextY -= CharHeight*((std::count(String.begin(), String.end(), '\n'))+1);

					auto Colour = RGBA8(255,255,255,255);	//White
					if(i == (Size-1))
					{
						String.resize(CharsDisplay);	//Do this after counting \n's so the box doesn't jump around while writing
						Colour = RGBA8(64,255,64,255);	//Blue
					}

					vita2d_pgf_draw_text(pgf, X,TextY,Colour, 1.5f, String.c_str());
				}
			}
		}
	}
}
