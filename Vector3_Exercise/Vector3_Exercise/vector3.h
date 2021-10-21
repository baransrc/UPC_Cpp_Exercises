#pragma once
#include <math.h>
#include "defines.h"

namespace math
{
	template <class T> class vector3
	{
	private:
		T x;
		T y;
		T z;
	public:
		vector3();
		vector3(T new_x, T new_y, T new_z);
		vector3(const vector3<T>& other);

		inline const T get_x() const { return this->x; }
		inline void set_x(const T new_x) { this->x = new_x; }

		inline const T get_y() const { return this->y; }
		inline void set_y(const T new_y) { this->y = new_y; }

		inline const T get_z() const { return this->z; }
		inline void set_z(const T new_z) { this->z = new_z; }

		void normalize();

		const T distance_to(const vector3<T>& other) const;

		const T dot_product(const vector3<T>& other) const;

		const vector3<T> cross_product(const vector3<T>& other) const;

		const T angle_between(const vector3<T>& other) const;

		inline const T magnitude() const 
		{
			T magnitude = (T) sqrt(this->get_x() * this->get_x() + this->get_y() * this->get_y() + this->get_z() * this->get_z());
			return magnitude;
		};

		const vector3<T> operator+(const vector3<T>& other) const;

		~vector3();
	};
}
