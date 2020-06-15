#ifndef COLOR_H
#define COLOR_H


#include "Tuple.h"
#include "precision.h"

namespace rtc {
	class Color {
	public:
		real m_r;
		real m_g;
		real m_b;

		Color() {
			m_r = 0;
			m_g = 0;
			m_b = 0;
		}

		Color(real r, real g, real b) : m_r{ r }, m_g{ g }, m_b{ b } {}

		static Color addColors(const Color& x, const Color& y) {
			real m_r = x.m_r + y.m_r;
			real m_g = x.m_g + y.m_g;
			real m_b = x.m_b + y.m_b;
			return{ m_r, m_g, m_b };
		}

		Color subColors(const Color& x, const Color& y) {
			real m_r = x.m_r - y.m_r;
			real m_g = x.m_g - y.m_g;
			real m_b = x.m_b - y.m_b;
			return{ m_r, m_g, m_b };
		}

		static Color scalarMultiplication(const Color& a, const real& x) {
			real r = a.m_r * x;
			real g = a.m_g * x;
			real b = a.m_b * x;
			return{ r, g, b };
		}

		static Color multColors(const Color& x, const Color& y) {
			real r = x.m_r * y.m_r;
			real g = x.m_g * y.m_g;
			real b = x.m_b * y.m_b;
			return{ r, g, b };
		}
	};
}
#endif // !COLOR_H
