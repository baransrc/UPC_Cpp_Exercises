#include "vector3.h"

namespace math
{
	template<class T>
	vector3<T>::vector3()
	{
		this->set_x(T());
		this->set_y(T());
		this->set_z(T());
	}

	template<class T>
	vector3<T>::vector3(T new_x, T new_y, T new_z)
	{
		this->set_x(T(new_x));
		this->set_y(T(new_y));
		this->set_z(T(new_z));
	}

	template<class T>
	vector3<T>::vector3(const vector3<T>& other)
	{
		this->set_x(other.get_x());
		this->set_y(other.get_y());
		this->set_z(other.get_z());
	}

	template<class T>
	void vector3<T>::normalize()
	{
		T magnitude = this->magnitude();

		if (!magnitude)
		{
			return;
		}

		this->set_x(get_x() / magnitude);
		this->set_y(get_y() / magnitude);
		this->set_z(get_z() / magnitude);
	}

	template<class T>
	const T vector3<T>::distance_to(const vector3<T>& other) const
	{
		double x_sub = ((double)this->get_x() - (double)other.get_x());
		double y_sub = ((double)this->get_y() - (double)other.get_y());
		double z_sub = ((double)this->get_z() - (double)other.get_z());

		return (T) sqrt(x_sub * x_sub + y_sub * y_sub + z_sub * z_sub);
	}

	template<class T>
	const T vector3<T>::dot_product(const vector3<T>& other) const
	{
		return this->get_x() * other.get_x() + this->get_y() * other.get_y() + this->get_z() * other.get_z();
	}

	template<class T>
	const vector3<T> vector3<T>::cross_product(const vector3<T>& other) const
	{
		return vector3<T>(
			this->get_y() * other.get_z() - this->get_z() * other.get_y(),
			this->get_z() * other.get_x() - this->get_x() * other.get_z(),
			this->get_x() * other.get_y() - this->get_y() * other.get_x()
			);
	}

	template<class T>
	const T vector3<T>::angle_between(const vector3<T>& other) const
	{
		vector3<T> this_copy = vector3<T>(*this);
		vector3<T> other_copy = vector3<T>(other);

		this_copy.normalize();
		other_copy.normalize();

		T dot_product = this_copy.dot_product(other_copy);
		
		if (dot_product <= T(-1.0))
		{
			return MATH_PI;
		}

		if (dot_product >= T(1.0))
		{
			return 0;
		}

		return acosl(dot_product);
	}

	template<class T>
	const vector3<T> vector3<T>::operator+(const vector3<T>& other) const
	{
		vector3<T> sum_vector3;

		sum_vector3.set_x(other.get_x() + this->get_x());
		sum_vector3.set_y(other.get_y() + this->get_y());
		sum_vector3.set_z(other.get_z() + this->get_z());

		return sum_vector3;
	}

	template<class T>
	vector3<T>::~vector3()
	{
	}

	// Available types:
	template class vector3<char>;
	template class vector3<unsigned char>;
	template class vector3<short>;
	template class vector3<unsigned short>;
	template class vector3<int>;
	template class vector3<unsigned int>;
	template class vector3<long>;
	template class vector3<unsigned long>;
	template class vector3<float>;
	template class vector3<double>;
	template class vector3<long double>;
}

