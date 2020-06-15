/*
* Interface file for the Ray Tracer tuples.
*
*
* This file contains the definitions for the Tuple class,
* which is the base class for Points and Vectors.
*
*/

#ifndef TUPLE_H
#define TUPLE_H

#include "precision.h"

namespace rtc {

	/*
	* Tuples are used to represent  3D primitives in Cartesian plane (e.g. point, vectors).
	*/

	class Tuple {

	public:
		
		// Holds the value along the x axis.
		real m_x;	

		// Holds the value along the y axis.
		real m_y;	

		// Holds the value along the z axis.
		real m_z;	

		// Indicates primitive type. 0 = vector / 1 = point.
		int m_w;	

		// Default constructor.
		Tuple() : m_x(0), m_y(0), m_z(0), m_w(0) {}

		// Constructs a tuple according to parameters passed.
		Tuple(real x, real y, real z, int w)
			: m_x{ x }, m_y{ y }, m_z{ z }, m_w{ w }{}

		// Destructor.
		~Tuple() {}

		// Returns the tuple that results from scaling tuple A by X.
		static Tuple scalarMultiplication(const Tuple& a, const real& x) {}

		// Returns the tuple that results from dividing tuple A by X.
		static Tuple scalarDivision(const Tuple& a, const real& x) {}
	};

}
#endif // !TUPLE_H
