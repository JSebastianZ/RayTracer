#ifndef MATERIAL_H
#define MATERIAL_H

#include "precision.h"
#include "Color.h"

namespace rtc {
	class Material {
	public:
		Color m_color;
		real m_ambient;
		real m_diffuse;
		real m_specular;
		real m_shininess;

		Material() : m_color{ 0,0,0 }, m_ambient{ 0 }, m_diffuse{ 0 }, m_specular{ 0 }, m_shininess{ 0 }{}
		Material(Color color, real ambient, real diffuse, real specular, real shininess) :
			m_color{ color }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular }, m_shininess{ shininess }{}
	};
}

#endif // !MATERIAL_H
