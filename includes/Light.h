/*
* Interface file for the Ray Tracer Light source.
*
*
* This file contains the definitions for the Light class,
* which represents a point that illuminates the rendered scene.
*
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

namespace rtc {

	/*
	* The Ray Tracer renders an image illuminated by one or several
	* Light objects.
	*/

	class Light {

	public:

		// Light source position within a 3D scene.
		Point m_source;

		// The intensity of the light source is represented by its RGB color.
		Color m_intensity;

		// Default constructor with light source at the origin and no illumination.
		Light() : m_source{ 0,0,0 }, m_intensity{ 0,0,0 }{}

		// Light object constructor with specified position and color.
		Light(Point source, Color intensity) : m_source{ source }, m_intensity{ intensity }{}
	};
}

#endif // !LIGHT_H
