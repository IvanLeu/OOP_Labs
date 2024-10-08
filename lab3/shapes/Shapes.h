#pragma once

#include <vector>
#include <string>
#include <assert.h>

class Shape {
protected:
	struct Vertex {
		float x;
		float y;
	};
public:
	Shape(const std::string& name_in, const std::vector<Vertex>& vertices_in)
		:
		shapeName(name_in),
		vertices(vertices_in)
	{}
	friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
	virtual Vertex GetCenter() const = 0;
	virtual operator double() const = 0;
	inline std::string GetName() const { return shapeName; }
	virtual ~Shape() = 0;
private:
	std::string shapeName;
	std::vector<Vertex> vertices;
};

class Triangle : public Shape {
public:
	Triangle(const std::vector<Vertex>& vertices_in)
		:
		Shape("Triangle", vertices_in)
	{
		assert(vertices_in.size() == 3);
	}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Shape& shape);
};

class Cube : public Shape {
public:
	Cube(const Vertex& pos, float width)
		:
		Shape("Cube", FromWidth(pos, width))
	{}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Shape& shape);
private:
	std::vector<Vertex> FromWidth(const Vertex& v, float width) const;
};

class Rectangle : public Shape {
public:
	Rectangle( const Vertex& pos, float width, float height )
		:
		Shape("Rectangle", FromWidthAndHeight(pos, width, height))
	{}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Shape& shape);
private:
	std::vector<Vertex> FromWidthAndHeight(const Vertex& v, float width, float height) const;
};