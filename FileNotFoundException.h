/**
 * \class FileNotFoundException
 * 
 * \brief FileNotFoundException class
 * 
 * \author haliscsharp
 * 
 * \version 1.0
 * 
 * \date 2020/10/05 23:15
 * 
 * Created on 2020/10/05 23:15
*/

#ifndef FILENOTFOUNDEXCEPTIION_H
#define FILENOTFOUNDEXCEPTIION_H

#include <iostream>

class FileNotFoundException : public std::string
{
public:
	///This is the constructor of the class
	FileNotFoundException(std::string message) :std::string(message) {}
	
};

#endif
