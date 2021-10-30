#pragma once
#include <iostream>

namespace exercise
{
	inline uint32_t string_length(const char* string)
	{
		uint32_t length = 0;
		const char* string_ptr = string;

		while (*string_ptr != '\0')
		{
			++length;
			string_ptr += sizeof(char);
		}

		return length;
	}
}

