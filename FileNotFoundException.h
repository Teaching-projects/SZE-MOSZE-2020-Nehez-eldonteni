#ifndef FILENOTFOUNDEXCEPTIION_H
#define FILENOTFOUNDEXCEPTIION_H

#include <iostream>

class FileNotFoundException : public std::string
{
public:
	FileNotFoundException(std::string message) :std::string(message) {}
	
};

#endif
