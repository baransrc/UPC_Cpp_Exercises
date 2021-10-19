#pragma once

namespace Math
{
	template <class T, class S> class vector3
	{
	private:
		T x;
		T y;
		T z;
	public:
		vector3();
		/*vector3(T new_x, T new_y, T new_z);
		vector3(vector3<T, S>& other);*/

		inline const T get_x() { return this->x; }
		inline void set_x(const T new_x) { this->x = new_x; }

		inline const T get_y() { return this->y; }
		inline void set_y(const T new_y) { this->y = new_y; }

		inline const T get_z() { return this->z; }
		inline void set_z(const T new_z) { this->z = new_z; }

		void normalize();

		const vector3<T, S> normalized() const;

		const S distance_to(const vector3<T, S>& other) const;

		const S dot_product(const vector3<T, S>& other) const;

		const vector3<T, S> cross_product(const vector3<T, S>& other) const;

		const S angle_between(const vector3<T, S>& other) const;


		const vector3<T, S> operator+(const vector3<T, S>& other) const;


		~vector3();
	};
}
