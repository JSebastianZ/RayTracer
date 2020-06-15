/*
* Interface file for the Ray Tracer color class.
*
*
* This file contains the definitions for the Color class,
* which provides functions to manipulate RGB color values.
*
*/

#ifndef COLOR_H
#define COLOR_H


#include "Tuple.h"
#include "precision.h"

namespace rtc {

	/*
	* The Ray Tracer camera renders a 3D scene onto a 2D image.
	* It is located one unit away from the final 2D rendered image.
	*/

	class Color {

	public:

		// An RGB color object consist of a tuple of three real numbers.
		// r for Red, g for Green, and b for Blue.
		real m_r;
		real m_g;
		real m_b;

		// Default constructor, color black.
		Color() {
			m_r = 0;
			m_g = 0;
			m_b = 0;
		}

		// Constructor with RGB values specified.
		Color(real r, real g, real b) : m_r{ r }, m_g{ g }, m_b{ b } {}

		// Color addition.
		static Color addColors(const Color& x, const Color& y) {
			real m_r = x.m_r + y.m_r;
			real m_g = x.m_g + y.m_g;
			real m_b = x.m_b + y.m_b;
			return{ m_r, m_g, m_b };
		}

		// Color substraction.
		Color subColors(const Color& x, const Color& y) {
			real m_r = x.m_r - y.m_r;
			real m_g = x.m_g - y.m_g;
			real m_b = x.m_b - y.m_b;
			return{ m_r, m_g, m_b };
		}

		// Modify RGB value by specified number of times to adjust brightness.
		static Color scalarMultiplication(const Color& a, const real& x) {
			real r = a.m_r * x;
			real g = a.m_g * x;
			real b = a.m_b * x;
			return{ r, g, b };
		}

		// Mix two colors.
		static Color multColors(const Color& x, const Color& y) {
			real r = x.m_r * y.m_r;
			real g = x.m_g * y.m_g;
			real b = x.m_b * y.m_b;
			return{ r, g, b };
		}
	};
}
#endif // !COLOR_H
