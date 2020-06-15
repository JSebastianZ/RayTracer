#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"

namespace rtc {
	class Transform {
	public:
		static Point translate_point(const Point& p, const Point& b);

		static Vector translate_vector(const Point& p, const Vector& v);

		static Point scale_point(const Point& p, const Point& b);

		static Vector scale_vector(const Point& p, const Vector& v);

		static Point reflect_point_x(const Point& p);

		static Point reflect_point_y(const Point& p);

		static Point reflect_point_z(const Point& p);

		static Point mirror_point(const Point& p);

		static Vector reflect_vector_x(const Vector& v);

		static Vector reflect_vector_y(const Vector& v);

		static Vector reflect_vector_z(const Vector& v);

		static Vector mirror_vector(const Vector& v);

		static Point rotate_point_x(const Point& p, real d);

		static Point rotate_point_y(const Point& p, real d);

		static Point rotate_point_z(const Point& p, real d);

		static Vector rotate_vector_x(const Vector& v, real d);

		static Vector rotate_vector_y(const Vector& v, real d);

		static Vector rotate_vector_z(const Vector& v, real d);

		static Point shearing(const Point& p, const real& xy, const real& xz, const real& yx,
			const real& yz, const real& zx, const real& zy);
	};
}

#endif // !TRANSFORM_H
