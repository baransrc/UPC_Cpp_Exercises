#include "string.h"

namespace exercise
{
	string::string()
	{

	}

	string::string(char*&& _string)
	{
	}

	string::string(char*& _string)
	{
	}

	string::~string()
	{
		delete[] _buffer;
	}
}