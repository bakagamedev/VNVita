#pragma once
#include <string>

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
    std::size_t  currIndex = width - 1;
    std::size_t  sizeToElim;
    while ( currIndex < source.length() )
    {
        currIndex = source.find_last_of(whitespace,currIndex + 1); 
        if (currIndex == std::string::npos)
            break;
        currIndex = source.find_last_not_of(whitespace,currIndex);
        if (currIndex == std::string::npos)
            break;
        sizeToElim = source.find_first_not_of(whitespace,currIndex + 1) - currIndex - 1;
        source.replace( currIndex + 1, sizeToElim , "\n");
        currIndex += (width + 1); //due to the recently inserted "\n"
    }
    return source;
}