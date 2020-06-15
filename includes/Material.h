/*
* Interface file for the Ray Tracer materials.
*
*
* This file contains the definitions for the Material class,
* which is used to specify the ambient, diffuse, and specular
* reflection values of an Object following Phong reflection model.
*
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "precision.h"
#include "Color.h"

namespace rtc {

	/*
	* The Material class implements the Phong reflection model to
	* simulate the reflection of light by an object, according to
	* its ambient, diffuse, and specular reflection attributes value.
	*/

	class Material {
	public:

		// Object RGB color.
		Color m_color;

		// Object ambient reflection attribute value (0 ~ 1).
		// Represents the light reflected by other objects in the scene.
		real m_ambient;

		// Object diffuse reflection attribute value (0 ~ 1).
		// Light reflected by a matte surface, depending on the angle
		// between the light source and object surface normal.
		real m_diffuse;

		// Object specular reflection attribute value (0 ~ 1).
		// Reflection of a light source into the object surface, know as specular highlight.
		// Depends on the angle between a reflection vector and
		// an "eye" vector.
		real m_specular;

		// Controls the specular highlight of the specular attribute.
		// A small value results in a broad and bigger specular highlight.
		real m_shininess;

		// Default constructor, with color black, and all attributes = 0.
		Material() : m_color{ 0,0,0 }, m_ambient{ 0 }, m_diffuse{ 0 }, m_specular{ 0 }, m_shininess{ 0 }{}

		// Constructor of material object with specified reflection values and color.
		Material(Color color, real ambient, real diffuse, real specular, real shininess) :
			m_color{ color }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular }, m_shininess{ shininess }{}
	};
}

#endif // !MATERIAL_H
