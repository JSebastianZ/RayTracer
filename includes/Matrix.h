#ifndef MATRIX_H
#define MATRIX_H


#include "precision.h"
#include "Tuple.h"
#include "Point.h"
#include "Vector.h"
#include <math.h>



namespace rtc {
	class Matrix {

	public:
		void create_matrix(int rows, int columns) {
			this->matrix = new real * [rows]();
			for (int i = 0; i < rows; ++i)
				matrix[i] = new real[columns]();
		}

	public:
		int m_rows{ 0 };
		int m_columns{ 0 };
		int size{ 0 };
		real** matrix;

		Matrix() { identity(4); }

		Matrix(int size) : m_rows{ size }, m_columns{ size }, size{ size } {
			create_matrix(m_rows, m_columns);
		}
		Matrix(int rows, int columns) : m_rows{ rows }, m_columns{ columns }{
			create_matrix(m_rows, m_columns);
		}

		real valueAt(int x, int y) {
			return matrix[x][y];
		}

		static bool identical_matrix(const Matrix& a, const Matrix& b) {
			if (a.m_rows != b.m_rows || a.m_columns != b.m_columns)
				return false;
			for (int i = 0; i < a.m_rows; i++) {
				for (int j = 0; j < a.m_columns; j++) {
					if (a.matrix[i][j] != b.matrix[i][j]) {
						return false;
					}
				}
			}
			return true;
		}

		static Matrix identity(int size) {
			Matrix m{ size };
			for (int i = 0; i < m.size; i++)
				for (int j = 0; j < m.size; j++)
					if (i == j) m.matrix[i][j] = 1; else m.matrix[i][j] = 0;
			return m;
		}

		static Matrix multiplyMatrices(const Matrix& a, const Matrix& b) {				// Multiply AxB
			Matrix c{ a.size };
			real x = 0;
			for (int i = 0; i < a.m_rows; i++) {
				for (int j = 0; j < b.m_columns; j++) {
					for (int f = 0; f < b.m_rows; f++) {
						x += a.matrix[i][f] * b.matrix[f][j];
					}
					c.matrix[i][j] = x;
					x = 0;
				}
			}
			return c;
		}
		template <typename T>
		static T multiplyByTuple(Matrix a, T b) {
			T t;
			t.m_x = a.matrix[0][0] * b.m_x + a.matrix[0][1] * b.m_y + a.matrix[0][2] * b.m_z + a.matrix[0][3] * b.m_w;
			t.m_y = a.matrix[1][0] * b.m_x + a.matrix[1][1] * b.m_y + a.matrix[1][2] * b.m_z + a.matrix[1][3] * b.m_w;
			t.m_z = a.matrix[2][0] * b.m_x + a.matrix[2][1] * b.m_y + a.matrix[2][2] * b.m_z + a.matrix[2][3] * b.m_w;
			t.m_w = a.matrix[3][0] * b.m_x + a.matrix[3][1] * b.m_y + a.matrix[3][2] * b.m_z + a.matrix[3][3] * b.m_w;
			return t;
		}

		static Matrix multiplyIdentity(const Matrix& a) {
			Matrix m{ a.size };
			m = identity(m.size);
			return multiplyMatrices(a, m);
		}

		static Matrix transpose(Matrix a) {
			Matrix t(a.size);
			for (int i = 0; i < a.size; i++)
				for (int j = 0; j < a.size; j++)
					t.matrix[i][j] = a.matrix[j][i];
			return t;
		}

		static Matrix submatrix(const Matrix& m, int x, int y) {
			Matrix sm{ m.size - 1 };
			int row = 0;
			int col = 0;
			for (int i = 0; i < sm.size; i++, ++row) {
				if (i == x) ++row;
				for (int j = 0; j < sm.size; j++, ++col) {
					if (j == y) ++col;
					sm.matrix[i][j] = m.matrix[row][col];
				}
				col = 0;
			}
			return sm;
		}

		static real determinant(const Matrix& m) {
			real deter{ 0 };
			real minor{ 0 };
			Matrix matrix{ m.size };
			for (int i = 0; i < matrix.size; i++) {
				for (int j = 0; j < matrix.size; j++) {
					matrix.matrix[i][j] = m.matrix[i][j];
				}
			}
			if (matrix.size == 2) {
				deter = matrix.matrix[0][0] * matrix.matrix[1][1] - matrix.matrix[0][1] * matrix.matrix[1][0];
				return deter;
			}
			for (int i = 0; i < matrix.size; i++) {
				Matrix x = submatrix(matrix, 0, i);
				if (i % 2 == 0) minor += matrix.matrix[0][i] * determinant(x);
				else minor += (-1 * matrix.matrix[0][i] * determinant(x));
			}
			deter = minor;
			return deter;
		}

		static Matrix cofactorMatrix(const Matrix& m) {
			real minor{ 0 };
			Matrix matrix{ m.size };
			Matrix cm{ m.size };
			for (int i = 0; i < matrix.size; i++) {
				for (int j = 0; j < matrix.size; j++) {
					matrix.matrix[i][j] = m.matrix[i][j];
				}
			}
			if (matrix.size == 2) {
				minor = matrix.matrix[0][0] * matrix.matrix[1][1] - matrix.matrix[0][1] * matrix.matrix[1][0];
				return minor;
			}
			for (int i = 0; i < matrix.size; i++) {
				for (int j = 0; j < matrix.size; j++) {
					Matrix x = submatrix(matrix, i, j);
					if ((i + j) % 2 == 0) minor = determinant(x);
					else minor = (-1 * determinant(x));
					cm.matrix[i][j] = minor;
				}
			}
			return cm;
		}

		static Matrix inverse(const Matrix& a) {
			real d{ determinant(a) };
			Matrix cofactor{ cofactorMatrix(a) };
			Matrix t{ transpose(cofactor) };
			Matrix inverse{ a.size };
			for (int i = 0; i < a.size; i++) {
				for (int j = 0; j < a.size; j++) {
					inverse.matrix[i][j] = t.matrix[i][j] / d;
				}
			}
			return inverse;
		}

		static Matrix translation_matrix_p(const Point& p) {
			Matrix t{ identity(4) };
			t.matrix[0][3] = p.m_x;
			t.matrix[1][3] = p.m_y;
			t.matrix[2][3] = p.m_z;
			t.matrix[3][3] = p.m_w;
			return t;
		}

		static Matrix translation_matrix_v(const Vector& v) {
			Matrix t{ 4 };
			t = identity(4);
			t.matrix[0][3] = v.m_x;
			t.matrix[1][3] = v.m_y;
			t.matrix[2][3] = v.m_z;
			t.matrix[3][3] = v.m_w;
			return t;
		}

		static Matrix scaling_matrix_p(const Point& p) {
			Matrix s{ 4 };
			s = identity(4);
			s.matrix[0][0] = p.m_x;
			s.matrix[1][1] = p.m_y;
			s.matrix[2][2] = p.m_z;
			s.matrix[3][3] = p.m_w;
			return s;
		}

		static Matrix scaling_matrix_v(const Vector& v) {
			Matrix s{ 4 };
			s = identity(4);
			s.matrix[0][0] = v.m_x;
			s.matrix[1][1] = v.m_y;
			s.matrix[2][2] = v.m_z;
			s.matrix[3][3] = v.m_w;
			return s;
		}

		static Matrix rotation_matrix_x(const real& d) {
			Matrix r{ identity(4) };
			r.matrix[1][1] = cos(d);
			r.matrix[1][2] = (-1 * sin(d));
			r.matrix[2][1] = sin(d);
			r.matrix[2][2] = cos(d);
			return r;
		}

		static Matrix rotation_matrix_y(const real& d) {
			Matrix r{ identity(4) };
			r.matrix[0][0] = cos(d);
			r.matrix[0][2] = sin(d);
			r.matrix[2][0] = (-1 * sin(d));
			r.matrix[2][2] = cos(d);
			return r;
		}

		static Matrix rotation_matrix_z(const real& d) {
			Matrix r{ 4 };
			r = identity(4);
			r.matrix[0][0] = cos(d);
			r.matrix[0][1] = (-1 * sin(d));
			r.matrix[1][0] = sin(d);
			r.matrix[1][1] = cos(d);
			return r;
		}

		static Matrix shearing_matrix(const real& xy, const real& xz, const real& yx,
			const real& yz, const real& zx, const real& zy)
		{
			Matrix s{ 4 };
			s = identity(4);
			s.matrix[0][1] = xy;
			s.matrix[0][2] = xz;
			s.matrix[1][0] = yx;
			s.matrix[1][2] = yz;
			s.matrix[2][0] = zx;
			s.matrix[2][1] = zy;
			return s;
		}

		static Matrix view_transform(Point& from, Point& to, Vector& up) {
			Vector forward = Point::subPoints(to, from);
			Vector upn = Vector::normalize(up);
			Vector left = Vector::crossProduct(forward, upn);
			Vector true_up = Vector::crossProduct(left, forward);
			true_up = Vector::normalize(true_up);
			forward = Vector::normalize(forward);
			left = Vector::normalize(left);
			Matrix orientation = Matrix(4);
			orientation.matrix[0][0] = left.m_x;
			orientation.matrix[0][1] = left.m_y;
			orientation.matrix[0][2] = left.m_z;
			orientation.matrix[0][3] = 0;
			orientation.matrix[1][0] = true_up.m_x;
			orientation.matrix[1][1] = true_up.m_y;
			orientation.matrix[1][2] = true_up.m_z;
			orientation.matrix[1][3] = 0;
			orientation.matrix[2][0] = -forward.m_x;
			orientation.matrix[2][1] = -forward.m_y;
			orientation.matrix[2][2] = -forward.m_z;
			orientation.matrix[2][3] = 0;
			orientation.matrix[3][0] = 0;
			orientation.matrix[3][1] = 0;
			orientation.matrix[3][2] = 0;
			orientation.matrix[3][3] = 1;
			Matrix translation = Matrix::translation_matrix_p(Point::scalarMultiplication(from,-1));
			return Matrix::multiplyMatrices(orientation, translation);
		}

	};
}
#endif // !MATRIX_H
