#include "string.h"
#include "string_util.h"
#include <assert.h>

#define VERBOSE true

namespace exercise
{
	constexpr char NULL_CHAR = '\0';
	constexpr int NULL_CHAR_PADDING = 1;

	string::string() : _buffer(nullptr), _length(0)
	{	
	}

	string::string(const char* _string)
	{
#if VERBOSE == true
		printf("Copied const char* to the buffer of String With Constructor.\n");
#endif

		_length = string_length(_string);
		_buffer = new char[_length + NULL_CHAR_PADDING];

		memcpy(_buffer, _string, _length);
		_buffer[_length] = NULL_CHAR;
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

	string::string(const string& _string)
	{
#if VERBOSE == true
		printf("Copied String With Constructor.\n");
#endif

		_length = _string._length;
		_buffer = new char[_length + NULL_CHAR_PADDING];

		memcpy(_buffer, _string._buffer, _length);
		_buffer[_length] = NULL_CHAR;
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
		printf("%s\n", _buffer);
	}

	void string::clear()
	{
		delete[] _buffer;
		
		_buffer = new char[NULL_CHAR_PADDING];
		_buffer[0] = NULL_CHAR;
		_length = 0;
	}

	bool string::operator==(const char* _string) const
	{
		uint32_t length = string_length(_string);

		if (_length != length)
		{
			return false;
		}

		return compare_with_same_length_string(_string);
	}

	bool string::operator==(const string& _string) const
	{
		uint32_t length = string_length(_string._buffer);

		if (_length != length)
		{
			return false;
		}

		return compare_with_same_length_string(_string._buffer);
	}

	string& string::operator=(string&& _string) noexcept
	{
#if VERBOSE == true
		printf("Moved String With Assignment.\n");
#endif
		// If _string points to the same memory address with this,
		// i.e they are the same string, assert since this should 
		// never be made with move keyword:
		assert(&_string != this);

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
		_buffer = new char[_length + NULL_CHAR_PADDING];

		memcpy(_buffer, _string._buffer, _length);
		_buffer[_length] = NULL_CHAR;

		return *this;
	}

	string string::operator+(const string& _string) const
	{
#if VERBOSE == true
		printf("Operator + on two strings:\n");
#endif
		// New string will have the buffer size of the two 
		// concatenated, plus one for "null-terminator":
		uint32_t buffer_length = _string._length + _length + NULL_CHAR_PADDING;

		char* concat_buffer = new char[buffer_length];

		memcpy(concat_buffer, _buffer, _length);
		memcpy(&(concat_buffer[_length]), _string._buffer, _string._length);
		
		// I have struggled for like 4-5 hours getting f**k ton of nonsense characters
		// at the end of the copied strings, and this one line of code was the solution.
		// Basically, char* are going way longer than they are allocated, and if you don't add
		// the following so-called "null-character" along with a padding of +1 to the buffer, 
		// your buffer will have the above mentioned non-sense:
		concat_buffer[buffer_length - NULL_CHAR_PADDING] = NULL_CHAR;

		return string(std::move(concat_buffer));
	}

	string::~string()
	{
#if VERBOSE == true
		printf("Deleted String.\n");
#endif
		delete[] _buffer;
	}

	bool string::compare_with_same_length_string(const char* _string) const
	{
		for (uint32_t i = 0; i < _length; ++i)
		{
			if (_string[i] != _buffer[i])
			{
				return false;
			}
		}

		return true;
	}
}