#ifndef WORLD_H
#define WORLD_H

#include "Light.h"
#include <vector>
#include "Color.h"
#include "Point.h"
#include "Sphere.h"
#include "Material.h"

namespace rtc {
	class World {
	public:

		Light m_light_source;
		std::vector<Sphere> m_objects;	// Trata de generalizar para que acepte todo tipo de obje
		Material m1 = Material((Color(1, 0.9, 0.9)), 0.1, 0.7, 0, 200.0);
		Material m4 = Material(Color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0);
		Material m5 = Material(Color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200.0);
		Material m6 = Material(Color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200.0);

		Point p1 = Point(10, 0.01, 10);

		Matrix t1 = Matrix::multiplyMatrices(Matrix::translation_matrix_p(Point(0,0,0)), Matrix::scaling_matrix_p(p1));
		Matrix t2 = Matrix::multiplyMatrices(Matrix::translation_matrix_p(Point(0, 0, 5)),
			(Matrix::multiplyMatrices(Matrix::rotation_matrix_y(-PI / 4),
				(Matrix::multiplyMatrices(Matrix::rotation_matrix_x(PI / 2), Matrix::scaling_matrix_p(p1))))));
		Matrix t3 = Matrix::multiplyMatrices(Matrix::translation_matrix_p(Point(0, 0, 5)),
			(Matrix::multiplyMatrices(Matrix::rotation_matrix_y(PI / 4),
				(Matrix::multiplyMatrices(Matrix::rotation_matrix_x(PI / 2), Matrix::scaling_matrix_p(p1))))));
		Matrix t4 = Matrix::translation_matrix_p(Point(-0.5, 1, 0.5));
		Matrix t5 = Matrix::multiplyMatrices(Matrix::translation_matrix_p(Point(1.5, 0.5, -0.5)), Matrix::scaling_matrix_p(Point(0.5, 0.5, 0.5)));
		Matrix t6 = Matrix::multiplyMatrices(Matrix::translation_matrix_p(Point(-1.5, 0.33, -0.75)), Matrix::scaling_matrix_p(Point(0.33, 0.33, 0.33)));
		
		
		World() {
			Sphere floor(Sphere(2, Point(0, 0, 0), m1, t1));
			Sphere left_wall(Sphere(2, Point(0, 0, 0), m1, t2));
			Sphere right_wall(Sphere(2, Point(0, 0, 0), m1, t3));
			Sphere middle(Sphere(2, Point(0, 0, 0), m4, t4));
			Sphere right(Sphere(2, Point(0, 0, 0), m5, t5));
			Sphere left(Sphere(2, Point(0, 0, 0), m6, t6));


			m_light_source = (Light((Point(-10, 10, -10)), (Color(1, 1, 1))));


			m_objects.push_back(floor);
			m_objects.push_back(left_wall);
			m_objects.push_back(right_wall);
			m_objects.push_back(middle);
			m_objects.push_back(right);
			m_objects.push_back(left);


		}
	};
}

#endif // !WORLD_H
