#pragma once
#include <iostream>

namespace exercise
{
	class string
	{
	private:
		char* _buffer;
		uint32_t _length;
	public:
		string();
		string(char*&& _string);
		string(char*& _string);

		inline uint32_t length() const { return this->_length; };
		inline const char* buffer() const { return this->_buffer; };

		~string();
	};
}


