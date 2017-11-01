#include "vndsparse.h"

VNDSParser::VNDSParser(ImageControl *Images, TextControl *Text)
{
	this->Images = Images;
	this->Text = Text;
}

void VNDSParser::SaveState(const std::string SaveFile)
{
	//Assumes GUI handles all file conflicts
	sceIoMkdir(SavePath.c_str(), 0777);

	std::ofstream filesave(SavePath + SaveFile);
	if(filesave.is_open())
	{
		filesave << File;
		filesave << "\n";
		filesave << std::to_string(CurrentLine-1);
		filesave << "\n";
		filesave << Images->Background.Path;
		filesave << "\n";
		filesave << std::to_string(Images->ForegroundList.size());
		for(int i=0; i<Images->ForegroundList.size(); ++i)
		{
			filesave << "\n";
			filesave << Images->ForegroundList[i].Path;
			filesave << "\n";
			filesave << std::to_string(Images->ForegroundList[i].X);
			filesave << "\n";
			filesave << std::to_string(Images->ForegroundList[i].Y);
		}
	}
	filesave.close();
}
void VNDSParser::LoadState(const std::string SaveFile)
{
	std::ifstream fileread(SavePath + SaveFile);

	if(fileread.is_open())
	{
		fileread >> this->File;
		SetFile(File);
		
		std::string CurrentLineTemp;
		fileread >> CurrentLineTemp;
		try	{	CurrentLine = std::stoi(CurrentLineTemp);	}
		catch(std::invalid_argument)	{CurrentLine = 0;	}

		std::string BackPath;
		fileread >> BackPath;
		Images->BgLoad(BackPath,0);

		int SpriteCount = 0;
		fileread >> CurrentLineTemp;
		try	{ SpriteCount = std::stoi(CurrentLineTemp);	}
		catch(std::invalid_argument){SpriteCount = 0;}

		for(int i=0; i<SpriteCount; ++i)
		{
			std::string SpritePath;
			float X,Y;
			//Path
			fileread >> SpritePath;
			//X
			fileread >> CurrentLineTemp;
			try { X = std::stoi(CurrentLineTemp); }
			catch(std::invalid_argument) { X = 0; }
			//Y
			fileread >> CurrentLineTemp;
			try { Y = std::stoi(CurrentLineTemp); }
			catch(std::invalid_argument) { Y = 0; }

			Images->SetImage(SpritePath,X,Y);
		}
	}

	fileread.close();
}

void VNDSParser::SetPath(const std::string Path)
{
	this->BasePath = Path;
	this->ScriptPath = Path + "/script/";
	this->SoundPath = Path + "/sound/";
	this->BackgroundPath = Path + "/background/";
	this->ForegroundPath = Path + "/foreground/";
	this->SavePath = Path + "/save/";
}

void VNDSParser::SetFile(const std::string File)
{
	this->File = File;

	//Clear State
	LabelLocations.clear();
	Instructions.clear();
	StringBlob.clear();
	CurrentLine = 0;
	DelayFrames = 0;
	FunctionClearText();
	Text->QuestionActive = false;

	//Log label locations
	//Read file
	uint LineNo = 0;

	std::ifstream fileread(ScriptPath + File);
	std::string Line;
	while(std::getline(fileread, Line))
	{
		//skip empty lines
		if(Line.empty())
			continue;

		stringtrim(Line);

		OpcodeType Opcode = GetOpcode(Line);

		//Skip unrecognisable lines
		if(Opcode == OpcodeType::None)
			continue;

		GetOperand(Line);

		if(Opcode == OpcodeType::Label)
		{
			LabelLocations[Line] = LineNo;
			continue;
		}

		uint StringLength = Line.size();
		Instructions.push_back(VNDSInstruction(Opcode, StringViewer(StringBlob.size(),StringLength)));
		StringBlob.append(Line);
		++LineNo;
	}

	if(Instructions.size() == 0)
	{
		Text->TextAdd("Bad script file");
		Text->TextAdd(ScriptPath+File);
	}

	DumpStrings(ScriptPath + File + ".txt");
}

void VNDSParser::Tick(bool Pressed)
{
	--DelayFrames;
	if(DelayFrames > 0)
	{
		return;
	}
	--Images->BackgroundWait;
	if(Images->BackgroundWait > 0)
	{
		return;
	}

	if(QuestionWait)
	{
		if ((!Text->QuestionActive) && (Text->QuestionAnswer>=1))	//Wait for Text to respond
		{
			SetVar("selected",Text->QuestionAnswer);
			Text->QuestionAnswer = -1;
			QuestionWait = false;
			return;	//End for frame, continue next
		}
		else
		{
			return;	//No answer given yet, abort.
		}
	}

	if((Pressed) || (Continue) || (DelayFrames==0))
	{
		RunNextLine();
	}
}

bool VNDSParser::IsFinished()
{
	return (CurrentLine>=Instructions.size());
}

void VNDSParser::RunNextLine()
{
	TempString.clear();
	Blocking = false;
	Continue = false;
	//"Blocking" being set to true hands control back to the UI.
	while(!Blocking)
	{
		if(IsFinished())
		{
			return;
		}

		VNDSInstruction * CurrentInstruction = &Instructions[CurrentLine];

		//replace with map or something
		switch(CurrentInstruction->Opcode)
		{
			case OpcodeType::Text:
				FunctionText(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Cleartext:
				FunctionClearText();
				break;
			case OpcodeType::Jump:
				FunctionJump(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Bgload:
				FunctionBgload(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Setimg:
				FunctionSetimg(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Goto:
				FunctionGoto(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::If:
				FunctionIf(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Fi:
				/*	TextAdd("Fi");	*/
				break;
			case OpcodeType::Setvar:
				/*	TextAdd("Setvar");	*/
				break;
			case OpcodeType::Gsetvar:
				/*	TextAdd("GSetvar");*/
				break;
			case OpcodeType::Random:
				/*	TextAdd("Random"); */
				break;
			case OpcodeType::Delay:
				FunctionDelay(CurrentInstruction->Operand.String);
				break;
			case OpcodeType::Music:
				/*	TextAdd("Music"); */
				break;
			case OpcodeType::Sound:
				/*	TextAdd("Sound"); */
				break;
			case OpcodeType::Choice:
				FunctionChoice(CurrentInstruction->Operand.String);
				break;
		}
		++CurrentLine;
	}

	if(!TempString.empty())
		Text->TextAdd(TempString);
}

void VNDSParser::DumpStrings(const std::string &outfile)
{
    std::ofstream out(outfile);
    out << StringBlob;
    out.close();
}

OpcodeType VNDSParser::GetOpcode(const std::string &line)
{
	std::string opstring = line.substr(0, line.find(" "));
	if(OpcodeStrings.find(opstring) != OpcodeStrings.end())
	{
		return OpcodeStrings[opstring];
	}
	return OpcodeType::None;
}

void VNDSParser::GetOperand(std::string &line)
{
	if(line == "text")	//Blank lines manifest here as just "text"
	{
		line = "";
	}
	else
	{
		line = line.substr(line.find_first_of(" \t")+1);
	}
}

void VNDSParser::TextAdd(const std::string &String)
{
	if(!TempString.empty())	TempString += "\n";
	TempString += String;
}

bool VNDSParser::IsQuestion()
{
	return QuestionWait;
}

void VNDSParser::SetAnswer(int Answer)
{
	QuestionAnswer = Answer;
}

std::string VNDSParser::GetQuestionAnswers()
{
	return QuestionAnswerViewer.GetString(StringBlob);
}

/*
	Variable Controls
*/
void VNDSParser::SetVar(std::string Var, std::string Value)
{
	LocalVariables[Var] = Value;
}
void VNDSParser::SetVar(std::string Var, int Value)
{
	LocalVariables[Var] = std::to_string(Value);
}
void VNDSParser::SetGVar(std::string Var, std::string Value)
{
	GlobalVariables[Var] = Value;
}

/*
	Function zone! Actung!
*/
void VNDSParser::FunctionText(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	if (String.size() == 0)
		return;

	Blocking = true;
	char firstchar = String.at(0);
	if(firstchar == '@')	
		{	String.erase(0,1);	Continue = true;	Blocking = false;}
	if(firstchar == '~')	
		{	String = "";	Blocking = true;	Continue = true;	}
	if(firstchar == '!')	
		{	String = ""; 	Blocking = true;	}

	TextAdd(String);
}

void VNDSParser::FunctionIf(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	std::vector<StringViewer> Tokens = stringsplit(String);

	bool IfTrue = false;
	if(Tokens.size() == 3)
	{
		std::string LeftSide = Tokens[0].GetString(String);
		std::string Operator = Tokens[1].GetString(String);;
		std::string RightSide = Tokens[2].GetString(String);;

		if(LocalVariables.count(LeftSide) != 0)	
		{
			LeftSide = LocalVariables[LeftSide];	//Replace with value

			if(Operator == "==")
			{
				if(LeftSide == RightSide)
					IfTrue = true;
			}
			if(Operator == "!=")
			{
				if(LeftSide != RightSide)
					IfTrue = true;
			}
		}
		else
		{
			//If variable isn't found, match with 0.
			if((Operator == "==") && (RightSide == "0"))
			{
				IfTrue = true;
			}
		}
	}

	if(!IfTrue)	//Skip to matching fi
	{
		bool Found = false;
		int IfMatch = 1;
		int Position = CurrentLine+1;
		while(!Found)
		{
			if(Instructions[Position].Opcode == OpcodeType::If)
				++IfMatch;
			if(Instructions[Position].Opcode == OpcodeType::Fi)
				--IfMatch;

			if(IfMatch == 0)
				Found = true;
			else
				++Position;	
		}
		CurrentLine = Position;
	}
}

void VNDSParser::FunctionClearText()
{
	Text->TextClear();
}

void VNDSParser::FunctionJump(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	std::vector<StringViewer> Tokens = stringsplit(String);
	SetFile(Tokens[0].GetString(String));
}

void VNDSParser::FunctionBgload(StringViewer Viewer)
{
	Blocking = true;	//Finishes execution for current frame
	Continue = true;	//But do run on next, so delays get processed.
	std::string String = Viewer.GetString(StringBlob);
	auto Tokens = stringsplit(String);
	int Delay = 16;
	if(Tokens.size() > 1)
	{
		try
		{
			Delay = std::stoi(Tokens[1].GetString(String));
		}
		catch(std::invalid_argument)
		{
			Delay = 16;
		}
	}
	Images->BgLoad(BackgroundPath+Tokens[0].GetString(String),Delay);
}

void VNDSParser::FunctionSetimg(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	auto Tokens = stringsplit(String);

	if(Tokens[0].GetString(String).at(0) == '~')
	{
		Images->ImageClear();
	}
	else
	{
		int x=0,y=0;
		if(Tokens.size()>1)
		{
			try
			{
				x = std::stoi(Tokens[1].GetString(String));
				y = std::stoi(Tokens[2].GetString(String));
			}
			catch(std::invalid_argument)
			{
				x = 0;
				y = 0;
			}
		}
		Images->SetImage(ForegroundPath+Tokens[0].GetString(String),x,y);
	}

}

void VNDSParser::FunctionGoto(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	TextAdd("Goto : "+String);
	if(LabelLocations.count(String) != 0)
	{
		CurrentLine = LabelLocations[String];
		TextAdd("Cool!");
	}
	else
	{
		TextAdd("Failed.");
	}
}

void VNDSParser::FunctionDelay(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	int Delay;
	try
	{
		Delay = std::stoi(String);
	}
	catch(std::invalid_argument)
	{
		Delay = 0;
	}
	DelayFrames = Delay;
	Blocking = true;	//Abort parsing for current frame
}

void VNDSParser::FunctionChoice(StringViewer Viewer)
{
	std::string String = Viewer.GetString(StringBlob);
	QuestionAnswerViewer = Viewer;
	Blocking = true;
	QuestionWait = true;
	TextAdd(String);
	Text->SetQuestion(String);
}