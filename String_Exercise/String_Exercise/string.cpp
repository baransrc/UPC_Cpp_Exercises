#include "string.h"
#include "string_util.h"

#define VERBOSE true

namespace exercise
{
	string::string() : _buffer(new char[0]), _length(0)
	{	
	}

	string::string(const char* _string)
	{
#if VERBOSE == true
		printf("Copied const char* to the buffer of String With Constructor.\n");
#endif

		_length = string_length(_string);
		_buffer = new char[_length];

		memcpy(_buffer, _string, _length);
	}

	string::string(char*&& _string)
	{
#if VERBOSE == true
		printf("Moved char* to buffer of String With Constructor.\n");
#endif

		_length = string_length(_string);
		_buffer = _string;

		_string = nullptr;
	}

	string::string(string& _string)
	{
#if VERBOSE == true
		printf("Copied String With Constructor.\n");
#endif

		_length = _string._length;
		_buffer = new char[_length];

		memcpy(_buffer, _string._buffer, _length);
	}

	string::string(string&& _string) noexcept
	{
#if VERBOSE == true
		printf("Moved String With Constructor.\n");
#endif

		_length = _string._length;
		_buffer = _string._buffer;

		_string._buffer = nullptr;
		_string._length = 0;
	}

	void string::print() const
	{
		if (_length > 0)
		{
			for (uint32_t i = 0; i < _length; ++i)
			{
				printf("%c", _buffer[i]);
			}
		}
	
		printf("\n");
	}

	void string::clear()
	{
		delete[] _buffer;
		
		_buffer = new char[1];
		_buffer[0] = '\0';

		_length = string_length(_buffer);
	}

	bool string::operator==(const char* _string) const
	{
		uint32_t length = strlen(_string);

		if (_length != length)
		{
			return false;
		}

		for (uint32_t i = 0; i < length; ++i)
		{
			if (_string[i] != _buffer[i])
			{
				return false;
			}
		}

		return true;
	}

	bool string::operator==(const string& _string) const
	{
		return operator==(_string._buffer);
	}

	string& string::operator=(string&& _string) noexcept
	{
#if VERBOSE == true
		printf("Moved String With Assignment.\n");
#endif
		// If _string points to the same memory address with this,
		// i.e they are the same string, dereference this and return it's address:
		// This can be done with one return statements and inverting the == to !=
		// but I don't like that much of indentation in my code.
		if (&_string == this) 
		{
			return *this;
		}

		delete[] _buffer;

		_buffer = _string._buffer;
		_length = _string._length;

		_string._buffer = nullptr;
		_string._length = 0;

		return *this;
	}

	string& string::operator=(const string& _string)
	{
#if VERBOSE == true
		printf("Copied String With Assignment.\n");
#endif

		delete[] _buffer;

		_length = _string._length;
		_buffer = new char[_length];

		memcpy(_buffer, _string._buffer, _length);

		return *this;
	}

	string string::operator+(const string& _string) const
	{
#if VERBOSE == true
		printf("Operator + on two strings:\n");
#endif
		// New string will have the buffer size of the two 
		// concatenated, plus one for "null-terminator":
		uint32_t buffer_length = _string._length + _length + 1;

		char* concat_buffer = new char[buffer_length];

		memcpy(concat_buffer, _buffer, _length);
		memcpy(&(concat_buffer[_length]), _string._buffer, _string._length);
		
		// I have struggled for like 4-5 hours getting f**k ton of nonsense characters
		// at the end of the copied strings, and this one line of code was the solution.
		// Basically, char* are going way longer than they are allocated, and if you don't add
		// the following so-called "null-character" along with a padding of +1 to the buffer, 
		// your buffer will have the above mentioned non-sense:
		concat_buffer[buffer_length - 1] = '\0';

		return string(std::move(concat_buffer));
	}

	string::~string()
	{
		delete[] _buffer;

#if VERBOSE == true
		printf("Deleted String.\n");
#endif
	}
}