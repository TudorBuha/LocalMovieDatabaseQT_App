#include "Exception.h"

FileException::FileException(const std::string& throwMessage) : message(throwMessage)
{
}
//returns the message of the exception
const char* FileException::what()
{
	return message.c_str();
}
