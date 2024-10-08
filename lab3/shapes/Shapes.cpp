#include "Shapes.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
	os << shape.GetName() << ": " << " { ";
	for (auto& v : shape.vertices) {
		os << "( " << v.x << "," << v.y << " ) ";
	}
	os << "}";

	return os;
}


