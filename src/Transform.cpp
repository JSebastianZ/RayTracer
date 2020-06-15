#include "Transform.h"

namespace rtc {
	
		static Point translate_point(const Point& p, const Point& b) {
			Matrix m = Matrix::translation_matrix_p(p);
			Point k = Matrix::multiplyByTuple(m, b);
			return k;
		}

		static Vector translate_vector(const Point& p, const Vector& v) {
			Matrix m = Matrix::translation_matrix_p(p);
			Vector k = Matrix::multiplyByTuple(m, v);
			k.m_w = 0;
			return k;
		}

		static Point scale_point(const Point& p, const Point& b) {
			Matrix m = Matrix::scaling_matrix_p(p);
			Point k = Matrix::multiplyByTuple(m, b);
			return k;
		}

		static Vector scale_vector(const Point& p, const Vector& v) {
			Matrix m = Matrix::scaling_matrix_p(p);
			Vector k = Matrix::multiplyByTuple(m, v);
			k.m_w = 0;
			return k;
		}

		static Point reflect_point_x(const Point& p) {
			Point n{ -1,1,1 };
			return scale_point(n, p);
		}

		static Point reflect_point_y(const Point& p) {
			Point n{ 1,-1,1 };
			return scale_point(n, p);
		}

		static Point reflect_point_z(const Point& p) {
			Point n{ 1,1,-1 };
			return scale_point(n, p);
		}

		static Point mirror_point(const Point& p) {
			Point n{ -1,-1,-1 };
			return scale_point(n, p);
		}

		static Vector reflect_vector_x(const Vector& v) {
			Point n{ -1,1,1 };
			return scale_vector(n, v);
		}

		static Vector reflect_vector_y(const Vector& v) {
			Point n{ 1,-1,1 };
			return scale_vector(n, v);
		}

		static Vector reflect_vector_z(const Vector& v) {
			Point n{ 1,1,-1 };
			return scale_vector(n, v);
		}

		static Vector mirror_vector(const Vector& v) {
			Point n{ -1,-1,-1 };
			return scale_vector(n, v);
		}

		static Point rotate_point_x(const Point& p, real d) {
			Point r = Matrix::multiplyByTuple(Matrix::rotation_matrix_x(d), p);
			return r;
		}

		static Point rotate_point_y(const Point& p, real d) {
			Point r = Matrix::multiplyByTuple(Matrix::rotation_matrix_y(d), p);
			return r;
		}

		static Point rotate_point_z(const Point& p, real d) {
			Point r = Matrix::multiplyByTuple(Matrix::rotation_matrix_z(d), p);
			return r;
		}

		static Vector rotate_vector_x(const Vector& v, real d) {
			Vector r = Matrix::multiplyByTuple(Matrix::rotation_matrix_x(d), v);
			r.m_w = 0;
			return r;
		}

		static Vector rotate_vector_y(const Vector& v, real d) {
			Vector r = Matrix::multiplyByTuple(Matrix::rotation_matrix_y(d), v);
			r.m_w = 0;
			return r;
		}

		static Vector rotate_vector_z(const Vector& v, real d) {
			Vector r = Matrix::multiplyByTuple(Matrix::rotation_matrix_z(d), v);
			r.m_w = 0;
			return r;
		}

		static Point shearing(const Point& p, const real& xy, const real& xz, const real& yx,
			const real& yz, const real& zx, const real& zy) {
			Point s = Matrix::multiplyByTuple(Matrix::shearing_matrix(xy, xz, yx, yz, zx, zy), p);
			return s;
		}
	
}
