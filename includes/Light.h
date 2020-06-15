#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

namespace rtc {
	class Light {
	public:
		Point m_source;
		Color m_intensity;

		Light() : m_source{ 0,0,0 }, m_intensity{ 0,0,0 }{}
		Light(Point source, Color intensity) : m_source{ source }, m_intensity{ intensity }{}
	};
}

#endif // !LIGHT_H
