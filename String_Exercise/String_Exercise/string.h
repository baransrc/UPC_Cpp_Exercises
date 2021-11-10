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
		string(const char* _string);
		string(char*&& _string);
		string(const string& _string);
		string(string&& _string) noexcept;

		void print() const;
		void clear();
		
		inline uint32_t length() const { return this->_length; };
		inline const char* buffer() const { return this->_buffer; };

		bool operator==(const char* _string) const;
		bool operator==(const string& _string) const;
		string& operator=(string&& _string) noexcept;
		string& operator=(const string& _string);
		string operator+(const string& _string) const;

		~string();
	private:
		bool compare_with_same_length_string(const char* _string) const;
	};
}