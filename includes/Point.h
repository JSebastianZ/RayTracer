/*
* Interface file for the Ray Tracer Point class.
*
*
* This file contains the definitions for the Point class,
* which provides the "view" of the rendered scene.
*
*/

#ifndef POINT_H
#define POINT_H

#include "Tuple.h"
#include "Vector.h"

namespace rtc {

	/*
	* Points in the Ray Tracer are implemented as tuples of 4 elementes,
	* corresponding to X, Y, and Z position values within the 3D space.
	* The last "w" element value is always "1", and is used to 
	* differentiate a point from a vector (tuple with w = 0).
	*/

	class Point : public Tuple {

	public:

		// Points consist of X,Y, and Z values. Points m_w member is always "1". 
		real m_x;
		real m_y;
		real m_z;
		int m_w = 1;

		// Default constructor. Point in the origin of 3D space.
		Point() : Tuple{ 0,0,0,1 } {}

		// Creates a point object at the specified xyz position.
		Point(real x, real y, real z) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ 1 } {}

		// Destructor.
		~Point(){}

		// Returns the Point resulting from the addition of points A and B.
		static Point addPoints(const Point& a, const Point& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		// Returns the Point resulting from the addition of point A and vector B.
		static Point addVector2Point(const Point& a, const Vector& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		// Returns the Vector resulting from substracting point B from A.
		// A - B returns a vector point from B towards A.
		static Vector subPoints(const Point& a, const Point& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		// Returns the point resulting from substracting vector B from point A.
		static Point subVectorFromPoint(const Point& a, const Vector& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		// Returns the point that results from scaling point A by I.
		static Point scalarMultiplication(const Point& a, const real& i) {
			return { i * a.m_x, i * a.m_y, i * a.m_z };
		}

		// Returns the point that results from dividing point A by I.
		static Point scalarDivision(const Point& a, const real& i) {
			return { a.m_x / i, a.m_y / i, a.m_z / i };
		}
	};

}
#endif // !POINT_H
