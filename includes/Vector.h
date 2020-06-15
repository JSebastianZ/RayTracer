#ifndef VECTOR_H
#define VECTOR_H


#include "Tuple.h"

namespace rtc {
	class Vector : public Tuple {
	public:
		real m_x;
		real m_y;
		real m_z;
		int m_w;
	public:
		Vector() :Tuple{ 0,0,0,0 } {}

		Vector(real x, real y, real z) : m_x{ x }, m_y{ y }, m_z{ z }, m_w{ 0 } {}

		~Vector() {}

		static Vector addVectors(const Vector& a, const Vector& b) {
			real x = a.m_x + b.m_x;
			real y = a.m_y + b.m_y;
			real z = a.m_z + b.m_z;
			return { x, y, z };
		}

		static Vector subVectors(const Vector& a, const Vector& b) {
			real x = a.m_x - b.m_x;
			real y = a.m_y - b.m_y;
			real z = a.m_z - b.m_z;
			return { x, y, z };
		}

		static Vector negate(const Vector& a) {
			return { -a.m_x, -a.m_y, -a.m_z };
		}

		static Vector scalarMultiplication(const Vector& a, const real& x) {
			return { x * a.m_x, x * a.m_y, x * a.m_z };
		}

		Vector scalarDivision(const Vector& a, const real& x) {
			return { a.m_x / x, a.m_y / x, a.m_z / x };
		}

		static real magnitude(const Vector& a) {
			return sqrt(a.m_x * a.m_x + a.m_y * a.m_y + a.m_z * a.m_z);
		}

		static Vector normalize(const Vector& a) {
			real x = magnitude(a);
			return { a.m_x / x, a.m_y / x, a.m_z / x };
		}

		static real dotProduct(const Vector& a, const Vector& b) {
			return { a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z };
		}

		static Vector crossProduct(const Vector& a, const Vector& b) {
			return { a.m_y * b.m_z - a.m_z * b.m_y,
				a.m_z * b.m_x - a.m_x * b.m_z,
				a.m_x * b.m_y - a.m_y * b.m_x };
		}

		static Vector reflected(Vector& in, Vector& normal) {
			return subVectors(in, scalarMultiplication(normal, 2 * dotProduct(in, normal)));
		}

	};
}
#endif // !VECTOR_H