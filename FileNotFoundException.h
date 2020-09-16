#ifndef FILENOTFOUNDEXCEPTIION_H
#define FILENOTFOUNDEXCEPTIION_H

#include <iostream>

class FileNotFoundException : public std::exception
{
public:
	FileNotFoundException(std::string message) :msg(message) {}
	~FileNotFoundException() {}

	std::string message() { return msg; }

private:
	std::string msg;
};

#endif