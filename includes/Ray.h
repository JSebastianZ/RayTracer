#ifndef RAY_H
#define RAY_H

#include "precision.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Sphere.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include "Light.h"
#include "World.h"
#include <unordered_map>
#include "Object.h"
#include <iostream>
#include "Camera.h"

namespace rtc {
	class Ray {
	public:
		Point m_origin;
		Vector m_direction;

		bool m_inside = false;															// Determine if the eye is inside the sphere
		Point m_choke;
		Vector m_eye;
		Vector m_normal;
		real m_hit;
		std::unordered_map<real, Object> intersections;									// map intersectioin point with objects
		std::vector<real> accummulate_ix;

	public:

		Ray() : m_origin{ Point(0,0,0) }, m_direction{ Vector(0,0,0) }{}		// The position Vector must be NORMALIZED

		Ray(Point origin, Vector position) : m_origin{ origin }, m_direction{ position }{}

		~Ray() {}

		static Point position(const Ray& r, const real& d) {
			Vector v(Vector::scalarMultiplication(r.m_direction, d));
			Point p(Point::addVector2Point(r.m_origin, v));
			return p;
		}

		static Vector eye_vector(const Ray& r) {
			return Vector::negate(r.m_direction);
		}

		static Vector normal_at_hit(const Matrix& transform, const Point& p) {
			Matrix m_inverse_trans(Matrix::inverse(transform));

			Point object_point(rtc::Matrix::multiplyByTuple(m_inverse_trans, p));		// Calculo del vector Normal al hit point choke
			Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));	// punto podria ser origen de la esfera?
			Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(m_inverse_trans), object_normal));
			world_normal.m_w = 0;
			return  (Vector::normalize(world_normal));
		}

		void sphere_intersections( Ray& ray, const Sphere& s) {	// Estas intersecciones no son coordenadas 3D! son puntos de la ecuacion implicita!
			Point origin = ray.m_origin;
			Vector direction = ray.m_direction;
			Ray ray2 = Ray(origin,direction);			
			Ray r = transform(ray2, Matrix::inverse(s.b_transform));
			real t0;
			real t1;
			real a = Vector::dotProduct(r.m_direction, r.m_direction);
			real b = 2 * (Vector::dotProduct(r.m_direction, Point::subPoints(r.m_origin, s.m_center)));
			real c = (Vector::dotProduct(Point::subPoints(r.m_origin, s.m_center), Point::subPoints(r.m_origin, s.m_center))
				- (s.m_radius * s.m_radius));
			real discriminant = (pow(b, 2) - (4.0 * a * c));
			if (discriminant > 0) {
				t0 = ((-1 * b) - sqrt(discriminant)) / (2 * a);
				r.accummulate_ix.push_back(t0);
				ray.accummulate_ix.push_back(t0);

				r.intersections.insert({ t0, s});
				ray.intersections.insert({ t0, s });
				t1 = ((-1 * b) + sqrt(discriminant)) / (2 * a);
				r.accummulate_ix.push_back(t1);
				ray.accummulate_ix.push_back(t1);

				r.intersections.insert({ t1,s });
				ray.intersections.insert({ t1,s });
			}
			else if ((approxEqual(discriminant, 0.0, 1e-8)) || discriminant == 0) {
				t0 = (-1 * b) / (2 * a);
				r.accummulate_ix.push_back(t0);
				ray.accummulate_ix.push_back(t0);

				r.intersections.insert({ t0, s });
				ray.intersections.insert({ t0, s });
				t1 = (b) / (2 * a);
				r.accummulate_ix.push_back(t1);
				ray.accummulate_ix.push_back(t1);

				r.intersections.insert({ t1,s });
				ray.intersections.insert({ t1,s });
			}
			else { r.accummulate_ix.push_back(-999999);
				ray.accummulate_ix.push_back(-999999);
			}
		}

		real hit_location(std::vector<real>& i) {	// Hit location es punto t de la ecuacion implicita, no coordenadas/punto 3D!
			real minimum{ 9999 };					// El hecho de que sea negativo no quiere decir nada, solo que 
			for (int q = 0; q < i.size(); q++) {    // el valor de t es negativo en la interseccion de esfera
				if (i[q] < minimum && i[q] >= 0) {
					minimum = i[q];
				}
				else continue;
			}
			return minimum;
			if (minimum >= 0) return minimum;
			else return -1;
		}

		static Ray transform(const Ray& ray, const Matrix& transmatrix) {
			Ray r;
			r.m_origin = Matrix::multiplyByTuple(transmatrix, ray.m_origin);
			r.m_direction = Matrix::multiplyByTuple(transmatrix, ray.m_direction);
			r.m_direction.m_w = 0;
			return r;
		}

		static Color lighting(Material& m, Light& light, Point& p_p, Vector& p_eye, Vector& p_normal) {
			Point p(p_p.m_x, p_p.m_y, p_p.m_z);
			Vector eye(p_eye.m_x, p_eye.m_y, p_eye.m_z);
			Vector normal(p_normal.m_x, p_normal.m_y, p_normal.m_z);

			Color diffuse(0, 0, 0);															// Componente reflexion diffuse
			Color specular(0, 0, 0);														// Componente de reflexion especular
			Color effective_color(Color::multColors(m.m_color, light.m_intensity)); 			// Combinacion del color de la superficie del objeto y el color de la fuente de luz
			Vector lightv(Vector::normalize(Point::subPoints(light.m_source, p))); 			// Vector LightV que va desde el HIT hacia la fuente de luz
			Color ambient_contribution(Color::scalarMultiplication(effective_color, m.m_ambient));			// Componente de reflexion de ambiente, como multiplicacion de color efectivo y propiedad ambiental del material

			real cosine_light_normal(Vector::dotProduct(lightv, static_cast<Vector>(normal)));			// Coseno del angulo entre vector de luz y vector normal. 
			if (cosine_light_normal < 0) {													// Si es coseno de lightv y normal es < 0 la luz esta del otro lado de la superficie
				diffuse.m_r = 0;
				diffuse.m_g = 0;
				diffuse.m_b = 0;
				specular.m_r = 0;
				specular.m_g = 0;
				specular.m_b = 0;
			}
			else {
				Color d(Color::scalarMultiplication(effective_color, (m.m_diffuse * cosine_light_normal)));				// contribucion de diffusion
				diffuse.m_r = d.m_r;
				diffuse.m_g = d.m_g;
				diffuse.m_b = d.m_b;

				Vector lightv_n(Vector::negate(lightv)); 									// reflection vector
				Vector reflectv(Vector::reflected(lightv_n, normal));

				real reflect_dot_eye(Vector::dotProduct(reflectv, eye));  					// Coseno del angulo entre el vector reflejado y el ojo.

				if ((reflect_dot_eye < 0) || (approxEqual(reflect_dot_eye, 0.0000, EPSILON))) {				// Si es < 0 significa que la luz se refleja alejandose del ojo?
					specular.m_r = 0;
					specular.m_g = 0;
					specular.m_b = 0;
				}
				else {
					real factor(pow(reflect_dot_eye, m.m_shininess));						// calculo de la contribucion specular
					Color s(Color::scalarMultiplication(light.m_intensity, (m.m_specular * factor)));
					specular.m_r = s.m_r;
					specular.m_g = s.m_g;
					specular.m_b = s.m_b;
				}
			}
			Color kodak(Color::addColors(ambient_contribution, (Color::addColors(diffuse, specular))));
			return kodak;
		}

		std::vector<real> intersect_world(const World& w, Ray& r) {
			for (int i = 0; i < w.m_objects.size(); ++i) {
				r.sphere_intersections(r, w.m_objects[i]);
			}
			std::sort(r.accummulate_ix.begin(), r.accummulate_ix.end());
			return r.accummulate_ix;
		}

		void prepare_computations(const real& p_hit, Ray& r, World& w) {
			// real p_hit = 0;										// Usa hit solamente si el test te lo pide
			m_hit = r.hit_location(r.accummulate_ix);			// Este es el hit + que el current ray toca(minimum positive)
			if (m_hit < 0 || m_hit == 9999) {

				return;
			}   
			std::unordered_map<real, Object>::const_iterator got = intersections.find(m_hit);
			Object s = got->second;
			Matrix transform(s.b_transform);
			Point choke(Ray::position(r, m_hit));											// Ahora necesito los PUNTOS de INTERSECCION en 3D Phit = ray.orig + ray.dir * t

			Vector eye(Vector::negate(r.m_direction));										// Defino el vector EYE como el negativo del rayo

			Point object_point(rtc::Matrix::multiplyByTuple(Matrix::inverse(transform), choke));			// Calculo del vector Normal al hit point choke
			Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));
			Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(Matrix::inverse(transform)), object_normal));
			world_normal.m_w = 0;
			Vector normal(Vector::normalize(world_normal));

			if (Vector::dotProduct(normal, eye) < 0) {
				r.m_inside = true;
				normal = Vector::negate(normal);
			}
			else {
				r.m_inside = false;
			}

			r.m_choke = choke;
			r.m_eye = eye;
			r.m_normal = normal;

		}
		
		Color shade_hit( World& w, Point choke, Vector eye, Vector normal, real hit) {
			Color color;
			if (hit < 0 || hit == 9999) { 
				color = Color(0, 0, 0);
				return color; 
			}
			else {
				std::unordered_map<real, Object>::const_iterator got = intersections.find(hit);
				Object s = got->second;
				m_choke = choke;
				m_eye = eye;
				m_normal = normal;
				color = lighting(s.b_material, w.m_light_source, m_choke, m_eye, m_normal);
				return color;
			}
	   }

		Color color_at(World& w, Ray& r) {
			intersect_world(w, r);
			prepare_computations(0, r, w);
			Color c = shade_hit(w, m_choke, m_eye, m_normal, m_hit);
			return c;
		}

		static Ray ray_for_pixel(Camera& camera, const int& x, const int& y) {
			real xoffset = (x + 0.5) * camera.pixel_size();			// Offset from edge of canvas to pixels center
			real yoffset = (y + 0.5) * camera.pixel_size();
			real world_x = camera.m_half_width - xoffset;			// Untransformed coordinates of pixel in world space
			real world_y = camera.m_half_height - yoffset;
			Point pixel = Matrix::multiplyByTuple((Matrix::inverse(camera.m_transform)), (Point(world_x, world_y, -1)));
			Point origin = Matrix::multiplyByTuple((Matrix::inverse(camera.m_transform)), (Point(0, 0, 0)));
			Vector direction = Vector::normalize(Point::subPoints(pixel, origin));
			Ray ray = Ray(origin, direction);
			return ray;
		}

	};
}

#endif // !RAY_H