#ifndef TUPLE_H
#define TUPLE_H



#include "precision.h"

namespace rtc {

	/*
	Representation of 3D primitives in Cartesian plane
	*/

	class Tuple {

	public:
		real m_x;	// Holds the value along the x axis.

		real m_y;	// Holds the value along the y axis.

		real m_z;	// Holds the value along the z axis.

		int m_w;	// Indicates primitive type. 0 = vector / 1 = point.

	public:

		Tuple() : m_x(0), m_y(0), m_z(0), m_w(0) {}

		Tuple(real x, real y, real z, int w)
			: m_x{ x }, m_y{ y }, m_z{ z }, m_w{ w }{}

		~Tuple() {}

		static Tuple scalarMultiplication(const Tuple& a, const real& x) {}

		static Tuple scalarDivision(const Tuple& a, const real& x) {}
	};

}
#endif // !TUPLE_H