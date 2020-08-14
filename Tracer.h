#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include "Shape.h"
#include <unordered_map>
#include "World.h"
#include "Camera.h"
#include <fstream>
#include "Canvas.h"

namespace rt {

	class Tracer {
	public:

		// Data structure that accumulates hit point from all shapes!
		std::vector<real> ix_points;

		// Data structure that maps intersection points with intersected objects.
		// Used to keep track of the object that is intersected at an specific point.
		std::unordered_map<real, Shape*> ix_shape_map;

		// Map that bonds Shapes with their respective Shape ID.
		std::unordered_map<int, Shape*> shape_id_map;

		// Define eye vector as negative of ray direction.
		Vector eye;

		// Normal at hitpoint after shape is transformed.
		Vector normal;

		// Stores the 3D point where a single ray intersects an object.
		Point hit3D;

		// Magnitude of hit3D
		real m_hit3D;

		// Transformed ray
		Ray m_tray;

		// Intersected shape
		Shape* s;

		// Reflected ray at hit point.
		Vector m_reflectv;

		// Stores refraction index of mediums traversed by a ray.
		struct Refr_i {
			real n1;
			real n2;
		};

		// Data structure with same size as ix_points that holds refraction indexes at hitpoints.
		std::vector<Refr_i> n_ix;

		// Chapter 11 refraction support variables.
		real n_ratio;
		real cos_i;
		real sin2_t;
		Point under_point;

		// Test for refraction ixs objects
		std::vector<int> io;

		// Test for snell law computation
		std::vector<real> snell_sin;

		Color black{ 0, 0, 0 };

		Color white{ 1,1,1 };

		Tracer();

		// Returns sorted collection of intersections. 
		void intersect_world(const World& w, const Ray& r);

		// Sort all hitpoints
		void sort_ix(std::vector<real>& ixs);

		// Returns the location where a ray hits an object.
		// Visible hit points must be the lowest positive real number
		// from all intersection points of a ray (ix_points).
		real min_hit_point(std::vector<real>& ixs);
	
		// Prepares data structures and information about intersections.
		void prepare_computations(Ray& r, World& w);

		// Determines if a hit point is in shadow.
		bool shadowed(World& w, Point& p);

		// Ray Tracer implements the reflection model proposed
		// by Bui Tuong Phong. It defines three types of reflection.
		// Ambient: lighting reflected from other objects in the scene.
		// Diffuse: light reflected from a matte surface.
		// Specular: reflection of light source on a curved surface.
		// All are represented as a Color object with range between 0~1.
		Color lighting(Material& m, Light& light, bool shadow);

		// Returns color at the intersection point by
		// invoking the lightning member function.
		Color shade_hit(World& w, real& remaining);

		// Intersects the world with a given ray and
		// returns the color at the intersection point.
		Color color_at(World& w,  Ray& r, real& remaining);

		// Camera renders a "world scene" into a 2D image drawn in the canvas.
		void render(Camera& camera, World& world);

		// Computes the color returned by intersecting a surface with a reflective ray.
		Color reflected_color(World& world, real& remaining);

		// Stores refraction indexes of traversed objects.
		void fill_rix(std::vector<Refr_i>& n_ix, Shape& s);

		// Computes Snell's Law
		real snell(const real& n1, const real& n2);

		// Computes the refracted color of an object.
		Color refracted_color(World& world, real& remaining, const int& index);
	};

}


#endif // !TRACER_H
