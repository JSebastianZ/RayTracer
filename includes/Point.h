#ifndef POINT_H
#define POINT_H


#include "Tuple.h"
#include "Vector.h"

namespace rtc {

	class Point : public Tuple {
	public:
		real m_x;
		real m_y;
		real m_z;
		int m_w;

	public:
		Point() : Tuple{ 0,0,0,1 } {}

		Point(real x, real y, real z) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ 1 } {}

		~Point(){}

		static Point addPoints(const Point& a, const Point& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		static Point addVector2Point(const Point& a, const Vector& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		static Vector subPoints(const Point& a, const Point& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		static Point subVectorFromPoint(const Point& a, const Vector& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		static Point scalarMultiplication(const Point& a, const real& i) {
			return { i * a.m_x, i * a.m_y, i * a.m_z };
		}

		static Point scalarDivision(const Point& a, const real& i) {
			return { a.m_x / i, a.m_y / i, a.m_z / i };
		}
	};

}
#endif // !POINT_H