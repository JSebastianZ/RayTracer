/*
* Interface file for the Ray Tracer Sphere object.
*
*
* This file contains the definitions for the Sphere class,
* which provides the interfaces to create sphere objects.
*
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "precision.h"
#include "Point.h"
#include "Vector.h"
#include "Material.h"
#include "Object.h"

namespace rtc {

	/*
	* The Ray Tracer spheres derive from the Object class.
	*/

	class Sphere : public Object {

	public:

		// Spheres are defined by their diameter and position within the 3D space.
		real m_diameter;
		real m_radius = (m_diameter / 2);
		Point m_center;

		// Spheres are constructed according to specified parameters.
		// As objects, a material and transform matrix must be provided upon construction.
		Sphere(real diameter, Point center, Material material, Matrix transform) : m_diameter{ diameter }, m_center{ center }, Object{ material,transform } {}
	};
}

#endif // !SPHERE_H
