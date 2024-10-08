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

Shape::Vertex Triangle::GetCenter() const {
	auto tri = GetVertices();

	float centerX = (tri[0].x + tri[1].x + tri[2].x) / 3.0f;
	float centerY = (tri[0].y + tri[1].y + tri[2].y) / 3.0f;

	return Vertex{ centerX, centerY };
}

Triangle::operator double() const {
	auto verts = GetVertices();

	double area = 0.5 * abs((verts[0].x - verts[2].x) * (verts[1].y - verts[0].y)
		- (verts[0].x - verts[1].x) * (verts[2].y - verts[0].y));

	return area;
}

std::istream& operator>>(std::istream& is, Triangle& tri) {
	std::vector<Shape::Vertex> verts;

	is >> verts[0].x;
	is >> verts[0].y;
	is >> verts[1].x;
	is >> verts[1].y;
	is >> verts[2].x;
	is >> verts[2].y;

	tri.SetVertices(verts);

	return is;
}

Shape::Vertex Square::GetCenter() const {
	return Vertex{ pos.x + width * 0.5f, pos.y + width * 0.5f };
}

Square::operator double() const {
	return width * width;
}

std::istream& operator>>(std::istream& is, Square& sqr) {
	is >> sqr.pos.x;
	is >> sqr.pos.y;
	is >> sqr.width;

	return is;
}

std::vector<Shape::Vertex> Square::FromWidth(const Vertex& v, float width) const {
	std::vector<Shape::Vertex> verts;

	verts.push_back(v);
	verts.push_back({v.x + width, v.y});
	verts.push_back({v.x, v.y + width});
	verts.push_back({v.x + width, v.y + width});

	return verts;
}


Shape::Vertex Rectangle::GetCenter() const {
	return Vertex{ pos.x + width * 0.5f, pos.y + height * 0.5f};
}

Rectangle::operator double() const {
	return width * height;
}

std::istream& operator>>(std::istream& is, Rectangle& shape) {
	is >> shape.pos.x;
	is >> shape.pos.y;
	is >> shape.width;
	is >> shape.height;

	return is;
}

std::vector<Shape::Vertex> Rectangle::FromWidthAndHeight(const Vertex& v, float width, float height) const {
	std::vector<Shape::Vertex> verts;

	verts.push_back(v);
	verts.push_back({ v.x + width, v.y });
	verts.push_back({ v.x, v.y + height });
	verts.push_back({ v.x + width, v.y + height });

	return verts;
}