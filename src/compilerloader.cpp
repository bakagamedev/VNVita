#include "compilerloader.h"

void CompilerLoader::DetectVNDS(const std::string& ScriptPath)
{
	sourceFiles.Clear();
	SceUID uid = sceIoDopen(ScriptPath.c_str());
	if(uid >= 0)
	{
		SceIoDirent fileInfo;
		for(int next = sceIoDread(uid, &fileInfo); next != 0; next = sceIoDread(uid, &fileInfo))
		{
			if(next > 0)
			{
				SceIoStat stat = fileInfo.d_stat;
				if(stat.st_mode = 0000)	//???? file type here
				{
					std::string name(fileInfo.d_name);
					stringtrim(name);
					if(StringHasExtension(name,"txt"))
						sourceFiles.Add(name);
				}
			}
		}
	}
}

void CompilerLoader::DetectVNVita(const std::string& ScriptPath)
{

}

Compiler CompilerLoader::Load(const std::string& ScriptPath,const std::string& OutputPath,NovelFormatType Type)
{
	switch(Type)
	{
		case NovelFormatType::VNDS:
		{
			DetectVNDS(ScriptPath);
		} break;
		case NovelFormatType::VNVita:
		{
			DetectVNVita(ScriptPath);
		} break;
	}
	Compiler Compiler();//Compiler(sourceFiles,OutputPath,Type);
}