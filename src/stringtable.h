#pragma once
#include "stringviewer.h"

class StringTable
{
private:
	std::string StringBlob;
	std::vector<StringViewer> Viewers;
public:
	void Add(const std::string& NewString)
	{
		StringViewer tempViewer = StringViewer(StringBlob.size(),NewString.size()); 
		StringBlob.append(NewString);
		Viewers.push_back(tempViewer);
	}

	std::string GetLine(const size_t Entry) const
	{
		if(Entry < Viewers.size())
		{
			StringViewer tempViewer = Viewers[Entry];
			return tempViewer.GetString(StringBlob);
		}
		return "\0";
	}

	std::string operator[] (const size_t Entry) const
	{
		return GetLine(Entry);
	}

	void Clear(void)
	{
		StringBlob.clear();
		Viewers.clear();
	}
};