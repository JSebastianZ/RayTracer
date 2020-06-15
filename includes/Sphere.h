#ifndef SPHERE_H
#define SPHERE_H

#include "precision.h"
#include "Point.h"
#include "Vector.h"
#include "Material.h"
#include "Object.h"

namespace rtc {
	class Sphere : public Object {

	public:
		//Material m_material;
		real m_diameter;
		real m_radius = (m_diameter / 2);
		Point m_center;
		Sphere(real diameter, Point center, Material material, Matrix transform) : m_diameter{ diameter }, m_center{ center }, Object{ material,transform } {}
	};
}

#endif // !SPHERE_H
