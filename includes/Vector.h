/*
* Interface file for the Ray Tracer vectors.
*
*
* This file contains the definitions for the Vector class,
* which are used to represent rays direction, among others.
*
*/

#ifndef VECTOR_H
#define VECTOR_H

#include "Tuple.h"

namespace rtc {

	/*
	* Vectors are defined in 3D space by their x, y, and z values.
	* This class defines their construction and operations.
	*/

	class Vector : public Tuple {

	public:

		// 
		// Vectors are implemented as tuples holding x, y, and z values.
		// m_w member is '0' to distinguish from other tuples (e.g. points).
		real m_x;
		real m_y;
		real m_z;
		int m_w = 0;

		// Default constructor places a vector in the origin.
		Vector() :Tuple{ 0,0,0,0 } {}

		// Construct vector according to passed parameters.
		Vector(real x, real y, real z) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ 0 } {}

		// Destructor
		~Vector() {}

		// Returns a Vector resulting from the addition of two vectors.
		// A + B
		static Vector addVectors(const Vector& a, const Vector& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		// Returns a Vector resulting from substracting vector B from A.
		// A - B
		static Vector subVectors(const Vector& a, const Vector& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		// Returns the vector result from negating all vector A xyz values.
		static Vector negate(const Vector& a) {
			return { -a.m_x, -a.m_y, -a.m_z };
		}

		// Returns vector resulting from mutiplying vector A by X.
		static Vector scalarMultiplication(const Vector& a, const real& x) {
			return { x * a.m_x, x * a.m_y, x * a.m_z };
		}

		// Returns vector resulting from dividing vector A by X.
		Vector scalarDivision(const Vector& a, const real& x) {
			return { a.m_x / x, a.m_y / x, a.m_z / x };
		}

		// Returns the magnitude of vector A
		// |A|
		static real magnitude(const Vector& a) {
			return sqrt(a.m_x * a.m_x + a.m_y * a.m_y + a.m_z * a.m_z);
		}

		// Returns the vector A normalized.
		static Vector normalize(const Vector& a) {
			real x = magnitude(a);
			return { a.m_x / x, a.m_y / x, a.m_z / x };
		}

		// Returns the dot product of vectors A and B.
		// A * B
		static real dotProduct(const Vector& a, const Vector& b) {
			return { a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z };
		}

		// Returns the cross product of vectors A and B.
		// A x B
		static Vector crossProduct(const Vector& a, const Vector& b) {
			return { a.m_y * b.m_z - a.m_z * b.m_y,
				a.m_z * b.m_x - a.m_x * b.m_z,
				a.m_x * b.m_y - a.m_y * b.m_x };
		}

		// Returns the reflected vector resulting from the IN vector 
		// intersecting an object at a point with NORMAL vector.
		static Vector reflected(Vector& in, Vector& normal) {
			return subVectors(in, scalarMultiplication(normal, 2 * dotProduct(in, normal)));
		}

	};
}
#endif // !VECTOR_H
