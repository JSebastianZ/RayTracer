/*
* Interface file for the Ray Tracer rays.
*
*
* This file contains the definitions for the ray class,
* which create rays and find intersections with objects.
*
*/

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

	/*
	* The Ray Tracer cast rays (lines) and computes hit points
	* with every object within the 3D scene. To determine the
	* color of the hit point, the color_at function identifies
	* the closest object intersect by a ray, and evaluates its
	* material, light sources, and other attributes.
	*/

	class Ray {

	public:

		// Every ray has an origin and direction
		Point m_origin;
		Vector m_direction;

		// m_inside is used to identify when a ray or eye vector
		// originates inside an object's volume.
		bool m_inside = false;															
		
		// Point in the 3D world where a ray intersects an object.
		Point m_choke;

		// m_hit is the magnitude of m_choke;
		real m_hit;

		// Collection of points where a ray intersects an object.
		std::vector<real> accummulate_ix;

		// Data structure that maps intersection points with intersected objects.
		// Used to keep track of the object that is intersected at an specific point.
		std::unordered_map<real, Object> intersections;

		// Vector pointing from the ray intersection point of 
		// an object to the origin of the ray.
		Vector m_eye;

		// Vector perpendicular to the surface of an object.
		Vector m_normal;

		// Default constructor of a ray at the origin.
		Ray() : m_origin{ Point(0,0,0) }, m_direction{ Vector(0,0,0) }{}	

		// Construct ray at specified origin and position.
		// Ray direction must be normalized.
		Ray(Point origin, Vector position) : m_origin{ origin }, m_direction{ position }{}

		// Destructor.
		~Ray() {}

		// Given a ray, and a hit value, returns the 
		// 3D coordinates of the hit point.
		static Point position(const Ray& r, const real& d) {
			Vector v(Vector::scalarMultiplication(r.m_direction, d));
			Point p(Point::addVector2Point(r.m_origin, v));
			return p;
		}

		// Vector that represents the "eye" looking at the 3D scene.
		// "Light" received through this vector is composed of
		// the diffuse and specular reflection of the incident light.
		static Vector eye_vector(const Ray& r) {
			return Vector::negate(r.m_direction);
		}

		// Computation of normal vector to the surface at hit point to be shaded.
		static Vector normal_at_hit(const Matrix& transform, const Point& p) {
			Matrix m_inverse_trans(Matrix::inverse(transform));
			Point object_point(rtc::Matrix::multiplyByTuple(m_inverse_trans, p));		
			Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));	
			Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(m_inverse_trans), object_normal));
			world_normal.m_w = 0;
			return  (Vector::normalize(world_normal));
		}

		// Computes Ray-Sphere intersections by calculating the discriminant 
		// and two Sphere quadratic function roots (t0/t1). The two roots are 
		// mapped to a sphere, and stored in the accummulate_ix data structure. 
		void sphere_intersections( Ray& ray, const Sphere& s) {	
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
				ray.accummulate_ix.push_back(t0);
				ray.intersections.insert({ t0, s });
				t1 = ((-1 * b) + sqrt(discriminant)) / (2 * a);
				ray.accummulate_ix.push_back(t1);
				ray.intersections.insert({ t1,s });
			}
			else if ((approxEqual(discriminant, 0.0, 1e-8)) || discriminant == 0) {
				t0 = (-1 * b) / (2 * a);
				ray.accummulate_ix.push_back(t0);
				ray.intersections.insert({ t0, s });
				t1 = (b) / (2 * a);
				ray.accummulate_ix.push_back(t1);
				ray.intersections.insert({ t1,s });
			}
			else { r.accummulate_ix.push_back(INFINITE);	// If the discriminant is negative, the ray misses,
				ray.accummulate_ix.push_back(INFINITE);		// no intersections exist (hit point at infinity).
			}
		}

		// Returns the location where a ray hits an object.
		// Visible hit points must be the lowest positive real number
		// from all intersection points of a ray (accumulate_ix).
		real hit_location(std::vector<real>& i) {	
			real minimum{ HIGH_NUMBER };					 // Initialize "minimum" to a high value for comparison purposes.
			for (int q = 0; q < i.size(); q++) {   
				if (i[q] < minimum && i[q] >= 0) {
					minimum = i[q];
				}
				else continue;
			}
			if (minimum >= 0) return minimum;
			else return -1;
		}

		// Apply the inverse of the transformation matrix
		// of an Object to a Ray. Returns a new ray with
		// transformed origin and direction. This is used 
		// to render transformed objects.
		static Ray transform(const Ray& ray, const Matrix& transmatrix) {
			Ray r;
			r.m_origin = Matrix::multiplyByTuple(transmatrix, ray.m_origin);
			r.m_direction = Matrix::multiplyByTuple(transmatrix, ray.m_direction);
			r.m_direction.m_w = 0;
			return r;
		}

		// Ray Tracer implements the reflection model proposed
		// by Bui Tuong Phong. It defines three types of reflection.
		// Ambient: lightning reflected from other objects in the scene.
		// Diffuse: light reflected from a matte surface.
		// Specular: reflection of light source on a curved surface.
		// All are represented as a Color object with range between 0~1.
		static Color lighting(Material& m, Light& light, Point& p_p, Vector& p_eye, Vector& p_normal, bool shadow) {
			Color diffuse(0, 0, 0);																// Diffuse reflection component.
			Color specular(0, 0, 0);															// Specular reflection component.
			Color effective_color(Color::multColors(m.m_color, light.m_intensity)); 			// Combine object surface and light source colors.
			Vector lightv(Vector::normalize(Point::subPoints(light.m_source, p_p))); 			// Vector represents direction of light source.
			Color ambient_contribution(Color::scalarMultiplication(effective_color, m.m_ambient));			// Compute ambient contribution.
			real cosine_light_normal(Vector::dotProduct(lightv, p_normal));			// Cosine of angle between light vector and object surface normal. 
			if (cosine_light_normal < 0 || (shadow == true)) {														// If negative, the light is "in the other side" of the surface.
				diffuse = Color(0, 0, 0);
				specular = Color(0, 0, 0);
			}
			else {																				// If light and normal are in the same side...
				Color d(Color::scalarMultiplication(effective_color, (m.m_diffuse * cosine_light_normal)));	// Compute diffusion contribution.		
				diffuse = Color(d.m_r, d.m_g, d.m_b);
				Vector lightv_n(Vector::negate(lightv)); 										// Compute the reflection of the light vector towards
				Vector reflectv(Vector::reflected(lightv_n, p_normal));							// the viewer ("eye" vector).
				real reflect_dot_eye(Vector::dotProduct(reflectv, p_eye));  					
				if ((reflect_dot_eye < 0) || (approxEqual(reflect_dot_eye, 0.0000, EPSILON))) {				// If negative, there is no specular reflection contribution.
					specular = Color(0, 0, 0);
				}
				else {
					real factor(pow(reflect_dot_eye, m.m_shininess));										// If positive compute the specular contribution.
					Color s(Color::scalarMultiplication(light.m_intensity, (m.m_specular * factor)));
					specular = Color(s.m_r, s.m_g, s.m_b);
				}
			}
			Color kodak(Color::addColors(ambient_contribution, (Color::addColors(diffuse, specular))));		// Add and return all reflection contributions.
			return kodak;
		}

		// Returns sorted collection of intersections. 
		std::vector<real> intersect_world(const World& w, Ray& r) {
			for (int i = 0; i < w.m_objects.size(); ++i) {
				r.sphere_intersections(r, w.m_objects[i]);
			}
			std::sort(r.accummulate_ix.begin(), r.accummulate_ix.end());
			return r.accummulate_ix;
		}

		// Prepares data structures and information about intersections.
		void prepare_computations(const real& p_hit, Ray& r, World& w) {
			// p_hit = 0;										// set p_hit to 0 for test purposes.
			m_hit = r.hit_location(r.accummulate_ix);			// stores hit location, return if there is none. 
			if (m_hit < 0 || m_hit == HIGH_NUMBER) {
				return;
			}   
			std::unordered_map<real, Object>::const_iterator got = intersections.find(m_hit);	// Stores object mapped to the hit location
			Object s = got->second;																// according to hash map data structure.
			Matrix transform(s.b_transform);
			Point choke(Ray::position(r, m_hit));												// Computes 3D coordinate of hit point as hitPoint = ray.orig + ray.dir * hit_location.
			Vector eye(Vector::negate(r.m_direction));											// Define eye vector as negative of ray direction.
			Point object_point(rtc::Matrix::multiplyByTuple(Matrix::inverse(transform), choke));			// Computes normal vector at hit point choke.
			Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));
			Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(Matrix::inverse(transform)), object_normal));
			world_normal.m_w = 0;
			Vector normal(Vector::normalize(world_normal));

			if (Vector::dotProduct(normal, eye) < 0) {			// If normal and eye vector dot product is negative
				r.m_inside = true;								// then the "viewer" is inside the object.
				normal = Vector::negate(normal);
			}
			else {
				r.m_inside = false;
			}
			r.m_eye = eye;										// associated with the current ray.
			r.m_normal = normal;
			Point over_point = Point::addPoints(choke,			// compensate for shadows computation.
				Point::scalarMultiplication
					(Point(normal.m_x,normal.m_y,normal.m_z),0.0008));
			choke = over_point;
			r.m_choke = choke;									// Set hit point, eye, and normal vectors


		}
		
		bool shadowed(World& w, Point& p) {
			Vector v = Point::subPoints(w.m_light_source.m_source, p);
			real distance = Vector::magnitude(v);
			Vector direction = Vector::normalize(v);
			Ray r = Ray(p, direction);
			intersect_world(w, r);
			m_hit = r.hit_location(r.accummulate_ix);
			if (m_hit < 0 || m_hit == HIGH_NUMBER) {
				return false;
			}
			else {
				if (m_hit < distance) return true; else return false;
			}
		}

		// Returns color at the intersection point by
		// invoking the lightning member function.
		Color shade_hit( World& w, Point choke, Vector eye, Vector normal, real hit) {
			Color color;
			if (hit < 0 || hit == HIGH_NUMBER) { 
				color = Color(0, 0, 0);
				return color; 
			}
			else {
				std::unordered_map<real, Object>::const_iterator got = intersections.find(hit);
				Object s = got->second;
				bool shadow = shadowed(w, choke);
				color = lighting(s.b_material, w.m_light_source, choke, eye, normal, shadow); 
				return color;
			}
	   }

		// Intersects the world with a given ray and
		// returns the color at the intersection point.
		Color color_at(World& w, Ray& r) {
			intersect_world(w, r);
			prepare_computations(0, r, w);
			Color c = shade_hit(w, m_choke, m_eye, m_normal, m_hit);
			return c;
		}

		// Computes 3D coordinates at the center of a given pixel
		// and constructs a ray that passes through it.
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
