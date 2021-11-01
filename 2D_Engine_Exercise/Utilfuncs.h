#pragma once
#pragma once

namespace utilfuncs
{
	template <class TYPE>
	TYPE lerp(TYPE start, TYPE end, float value)
	{
		if (start == end)
		{
			return end;
		}

		return (TYPE)(start + (end - start) * value);
	}

	template <class TYPE>
	TYPE clamp(TYPE max, TYPE min, TYPE value)
	{
		if (value >= max)
		{
			return max;
		}

		if (value <= min)
		{
			return min;
		}

		return value;
	}
}