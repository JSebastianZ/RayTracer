/*
* Interface file for the Ray Tracer camera.
* 
*
* This file contains the definitions for the camera class,
* which provides the "view" of the rendered scene.
*
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "Precision.h"
#include "Matrix.h"
#include <math.h>

namespace rtc {
	
	/*
	* The Ray Tracer camera renders a 3D scene onto a 2D image.
	* It is located one unit away from the final 2D rendered image.
	*/
	
	class Camera {

	public:
		
		// Horizontal size (in pixels) of the final 2D rendered image.
		real m_hsize;

		// Vertical size (in pixels) of the final 2D rendered image.
		real m_vsize;

		// Angle (radians) of aperture of the camera. Large angle translates into a "zoom out" view.
		real m_field_of_view;

		// Aspect is the ratio of the horizontal size of the final 2D image, to its vertical size.
		real aspect;

		// The width of half of the 2D rendered image. If >= 1, then it is half the horizontal size.
		// If < 1, then it is half the vertical size.
		real half_view;

		// Hold half of the 2D rendered image width and heigth, necessary for pixel size computation.
		real m_half_width;
		real m_half_height;

		// Describes how a "scene" moves relative to the camera.
		Matrix m_transform;

		// Default constructor.
		Camera() : m_hsize{ 0 }, m_vsize{ 0 }, m_field_of_view{ 0 }, m_transform{Matrix::identity(4)} {}
		
		// Constructs camera with specified parameter values, and identity matrix as transform.
		Camera(real hsize, real vsize, real field_of_view) : m_hsize{ hsize }, m_vsize{ vsize }, m_field_of_view{ field_of_view }, m_transform{ Matrix::identity(4) }{}

		// Constructor for camera object.
		Camera(real hsize, real vsize, real field_of_view, Matrix transform) : m_hsize{ hsize }, m_vsize{ vsize }, m_field_of_view{ field_of_view }, m_transform{ transform }{}

		// Destructor
		~Camera(){}

		// Computes the size of a pixel of the final 2D rendered image
		// by dividing its width by its horizontal size.
		// The returned value is used by Ray::ray_for_pixel in order to
		// determine the exact point where a ray must pass through the pixel.
		real pixel_size() {
			half_view = std::tan(m_field_of_view / 2);
			aspect = m_hsize / m_vsize;

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
