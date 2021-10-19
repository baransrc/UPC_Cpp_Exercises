#include <iostream>
#include "vector3.h"



int main()
{
	Math::vector3<float, float> vector_exercise;

	std::cout << "Vector x:" << vector_exercise.get_x() << " y: " << vector_exercise.get_y() << " z: " << vector_exercise.get_z();

	return 0;
}