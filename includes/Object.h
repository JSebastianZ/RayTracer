#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <stdlib.h>
#include "Matrix.h"

namespace rtc {
	class Object {
	public:
		int m_id;
	public:
		Material b_material;
		Matrix b_transform;

		Object() { m_id = rand() % 1000; b_transform = Matrix::identity(4); }
		Object(Material m, Matrix t) : b_material{ m }, b_transform{ t }{ m_id = rand() % 1000; }
		~Object(){}

		int getID() const { return m_id; }
	};
}
#endif // !OBJECT_H
