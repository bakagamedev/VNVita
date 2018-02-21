#pragma once
#include <string>
#include "stringviewer.h"

//https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start (in place)
static inline void stringltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void stringrtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void stringtrim(std::string &s) {
    stringltrim(s);
    stringrtrim(s);
}

//https://stackoverflow.com/questions/6891652/formatting-a-string-into-multiple-lines-of-a-specific-length-in-c-c
//Not the best solution, leaves words dangling off the end of the line before the \n.
static inline std::string stringwrap(std::string source, std::size_t width, std::string whitespace = " \t\r")
{
    std::size_t currIndex = width - 1;
    std::size_t sizeToElim;
    while ( currIndex < source.length() )
    {
        currIndex = source.find_last_of(whitespace,currIndex + 1); 
        std::size_t startindex = currIndex;
        if (currIndex == std::string::npos)
            break;
        currIndex = source.find_last_not_of(whitespace,currIndex);
        if (currIndex == std::string::npos)
            break;
        sizeToElim = source.find_first_not_of(whitespace,currIndex + 1) - currIndex - 1;
        source.replace( startindex, sizeToElim , "\n");
        currIndex += (width + 1); //due to the recently inserted "\n"
    }
    return source;
}

static inline std::vector<StringViewer> stringsplit(const std::string &input, char split)
{
    std::vector<StringViewer> tokens;

    int size = input.size();

    int seglength = 0;
    for(int offset = 0; offset<size; ++offset)
    {
        if(input.at(offset) == split)
        {
            tokens.push_back(StringViewer(offset-seglength,seglength));
            seglength = 0;
        }
        else
        {
            ++seglength;
        }
    }
    if(seglength>0)
        tokens.push_back(StringViewer(size-seglength,seglength));

    return tokens;
}

static inline std::vector<StringViewer> stringsplit(const std::string &input)
{
    return stringsplit(input,' ');
}