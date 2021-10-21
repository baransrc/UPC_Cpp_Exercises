#include <iostream>
#include "vector3.h"



int main()
{
	std::cout << "Default Constructor Experiment: " << std::endl;
	std::cout << "Expected result is: Vector3_0 x:0.0f y:0.0f z:0.0f" << std::endl;

	math::vector3<float> vector_exercise_0;

	std::cout << "Vector3_0 x:" << vector_exercise_0.get_x() 
		      << " y:" << vector_exercise_0.get_y() 
		      << " z:" << vector_exercise_0.get_z() << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	math::vector3<float> vector_exercise_1;
	math::vector3<float> vector_exercise_2;

	vector_exercise_1 = math::vector3<float>(1.0f, 0.0f, 3.0f);
	vector_exercise_2 = math::vector3<float>(-1.0f, 4.0f, 2.0f);

	std::cout << "Constructor Experiment: " << std::endl;
	std::cout << "Vector3_1 x:" << vector_exercise_1.get_x() 
		      << " y:" << vector_exercise_1.get_y() << " z:" 
		      << vector_exercise_1.get_z() << std::endl;
	std::cout << "Vector3_2 x:" << vector_exercise_2.get_x() 
		      << " y:" << vector_exercise_2.get_y() 
		      << " z:" << vector_exercise_2.get_z() << std::endl;
	std::cout << std::endl;
	
	// ------------------------------------------------------------------------------
	
	std::cout << "Copy Constructor Experiment: " << std::endl;
	std::cout << "Expected result is: Vector3_3 x:1.0f y:0.0f z:3.0f" 
		      << std::endl;
	
	math::vector3<float> vector_exercise_3 = math::vector3<float>(vector_exercise_1);

	std::cout << "Vector3_3 x:" << vector_exercise_3.get_x() 
		      << " y:" << vector_exercise_3.get_y() 
		      << " z:" << vector_exercise_3.get_z() << std::endl;
	std::cout << std::endl;
	
	// ------------------------------------------------------------------------------

	std::cout << "(Vector3_4 = Vector3_1 + Vector3_2) Experiment:" << std::endl;
	std::cout << "Expected result is Vector3_4 x:0.0f y:4.0f z:5.0f" << std::endl;

	math::vector3<float> vector_exercise_4 = vector_exercise_1 + vector_exercise_2;

	std::cout << "Vector3_4 x:" << vector_exercise_4.get_x() 
		      << " y:" << vector_exercise_4.get_y() 
		      << " z:" << vector_exercise_4.get_z() << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Setter Experiment:" << std::endl;
	std::cout << "Expected result is Vector3_5 x:11.0f y:12.0f z:13.0f" << std::endl;
	
	math::vector3<float> vector_exercise_5;
	vector_exercise_5.set_x(11.0f);
	vector_exercise_5.set_y(12.0f);
	vector_exercise_5.set_z(13.0f);

	std::cout << "Vector3_5 x:" << vector_exercise_5.get_x()
		<< " y:" << vector_exercise_5.get_y()
		<< " z:" << vector_exercise_5.get_z() << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_5.normalize() Experiment:" << std::endl;
	std::cout << "Expected result is: Vector3_5 x:0.528f y:0.576f z:0.642f" << std::endl;
	
	vector_exercise_5.normalize();
	
	std::cout << "Vector3_5 x:" << vector_exercise_5.get_x()
		<< " y:" << vector_exercise_5.get_y()
		<< " z:" << vector_exercise_5.get_z() << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_1.distance_to(Vector3_2) Experiment:" << std::endl;
	std::cout << "Expected result is: 4.58258" << std::endl;

	float distance_to = vector_exercise_1.distance_to(vector_exercise_2);

	std::cout << "Distance is: " << distance_to << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_6.dot_product(Vector3_7) Experiment:" << std::endl;
	std::cout << "Expected result is: 32" << std::endl;

	math::vector3<float> vector_exercise_6 = math::vector3<float>(1.0f, 2.0f, 3.0f);
	math::vector3<float> vector_exercise_7 = math::vector3<float>(1.0f, 5.0f, 7.0f);

	float dot_product = vector_exercise_6.dot_product(vector_exercise_7);

	std::cout << "Dot product is: " << dot_product << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_6.cross_product(Vector3_7) Experiment:" << std::endl;
	std::cout << "Expected result is: x:-1.0f y:-4.0f z:3.0f" << std::endl;

	math::vector3<float> cross_product = vector_exercise_6.cross_product(vector_exercise_7);

	std::cout << "Cross product is x:" << cross_product.get_x() 
		      << " y:" << cross_product.get_y() << " z:" << cross_product.get_z() << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_6.angle_between(Vector3_7) Experiment:" << std::endl;
	std::cout << "Expected result is: 0.15802f radians" << std::endl;

	float angle_between = vector_exercise_6.angle_between(vector_exercise_7);

	std::cout << "Angle Between Vector3_6 and Vector3_7 is: " << angle_between << std::endl;
	std::cout << std::endl;

	// ------------------------------------------------------------------------------

	std::cout << "Vector3_7.magnitude() Experiment:" << std::endl;
	std::cout << "Expected result is: 8.66025" << std::endl;

	float magnitude = vector_exercise_7.magnitude();

	std::cout << "Magnitude of Vector3_5 is: " << magnitude << std::endl;
	std::cout << std::endl;

	return 0;
}