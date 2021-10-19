#include "vector3.h"

namespace Math
{
	template<class T, class S>
	vector3<T, S>::vector3()
	{
		this->set_x(T());
		this->set_y(T());
		this->set_z(T());
	}
	
	/*template<class T, class S>
	vector3<T, S>::vector3(T new_x, T new_y, T new_z)
	{
	}
	
	template<class T, class S>
	vector3<T, S>::vector3(vector3<T, S>& other)
	{
	}*/
	
	template<class T, class S>
	void vector3<T, S>::normalize()
	{
	}
	
	template<class T, class S>
	const vector3<T, S> vector3<T, S>::normalized() const
	{
		return vector3<T, S>();
	}
	
	template<class T, class S>
	const S vector3<T, S>::distance_to(const vector3<T, S>& other) const
	{
		return S();
	}
	
	template<class T, class S>
	const S vector3<T, S>::dot_product(const vector3<T, S>& other) const
	{
		return S();
	}
	
	template<class T, class S>
	const vector3<T, S> vector3<T, S>::cross_product(const vector3<T, S>& other) const
	{
		return vector3<T, S>();
	}
	
	template<class T, class S>
	const S vector3<T, S>::angle_between(const vector3<T, S>& other) const
	{
		return S();
	}
	
	template<class T, class S>
	const vector3<T, S> vector3<T, S>::operator+(const vector3<T, S>& other) const
	{
		return vector3<T, S>();
	}
	
	template<class T, class S>
	vector3<T, S>::~vector3()
	{
	}

	// Available types:
	template class vector3<float, float>;
	template class vector3<double, double>;
	template class vector3<int, float>;
	template class vector3<int, double>;
}

