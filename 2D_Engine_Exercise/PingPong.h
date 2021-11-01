#pragma once

template <class TYPE> 
class PingPong
{
public:
	TYPE speed;
	
private:
	TYPE time;
	bool reversing;

public:
	PingPong() : speed(TYPE(0)), time(TYPE(0)), reversing(false) {}

	TYPE GetCurrent()
	{
		time = reversing ? time - speed : time + speed;
		
		if (time >= TYPE(1.0))
		{
			time = TYPE(1.0);
			reversing = true;
		}
		else if (time <= TYPE(0.0))
		{
			time = TYPE(0.0);
			reversing = false;
		}

		return time;
	}
};