#ifndef CAMERA_H
#define CAMERA_H

#include "Precision.h"
#include "Matrix.h"
#include <math.h>

namespace rtc {
	class Camera {

	public:
		real m_hsize;
		real m_vsize;
		real m_field_of_view;
		real m_half_width;
		real m_half_height;
		Matrix m_transform;

		Camera() : m_hsize{ 0 }, m_vsize{ 0 }, m_field_of_view{ 0 }, m_transform{Matrix::identity(4)} {}
		
		Camera(real hsize, real vsize, real field_of_view) : m_hsize{ hsize }, m_vsize{ vsize }, m_field_of_view{ field_of_view }, m_transform{ Matrix::identity(4) }{}

		Camera(real hsize, real vsize, real field_of_view, Matrix transform) : m_hsize{ hsize }, m_vsize{ vsize }, m_field_of_view{ field_of_view }, m_transform{ transform }{}

		~Camera(){}

		real pixel_size() {
			real half_view = std::tan(m_field_of_view / 2);
			real aspect = m_hsize / m_vsize;

			if (aspect >= 1) {
				m_half_width = half_view;
				m_half_height = half_view / aspect;
			}
			else {
				m_half_width = half_view * aspect;
				m_half_height = half_view; 
			}
			return ((m_half_width * 2) / m_hsize);
		}

	};
}

#endif // !CAMERA_H
