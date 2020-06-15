/*
* Interface file for the Ray Tracer objects.
*
*
* This file contains the definitions for the object class,
* which is the base template for all objects within a 3D scene.
*
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <stdlib.h>
#include "Matrix.h"

namespace rtc {

	/*
	* All the Ray Tracer objects posses some common basic attributes
	* defined by this Object class.
	*/

	class Object {

	public:

		// Objects intersected by rays are identified by an ID.
		int m_id;

		// All Objecs posses a material, and a transform matrix to define its position.
		Material b_material;
		Matrix b_transform;

		// Default constructor. Assigns a random ID, and an identity tranform matrix.
		Object() { m_id = rand() % 1000; b_transform = Matrix::identity(4); }

		// Object constructed with specified material and transform matrix. ID is random.
		Object(Material m, Matrix t) : b_material{ m }, b_transform{ t }{ m_id = rand() % 1000; }

		// Destructor.
		~Object(){}

		// Returns an Object ID.
		int getID() const { return m_id; }
	};
}
#endif // !OBJECT_H
