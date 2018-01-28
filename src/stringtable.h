#pragma once
#include "stringviewer.h"

class StringTable
{
private:
	std::string stringBlob;
	std::vector<StringViewer> viewers;
public:
	void Add(const std::string& NewString)
	{
		StringViewer tempViewer = StringViewer(stringBlob.size(),NewString.size()); 
		stringBlob.append(NewString);
		viewers.push_back(tempViewer);
	}

	std::string GetLine(const size_t Entry) const
	{
		if(Entry < viewers.size())
		{
			StringViewer tempViewer = viewers[Entry];
			return tempViewer.GetString(stringBlob);
		}
		return "";
	}

	std::string operator[] (const size_t Entry) const
	{
		return GetLine(Entry);
	}

	void Clear(void)
	{
		stringBlob.clear();
		viewers.clear();
	}
};