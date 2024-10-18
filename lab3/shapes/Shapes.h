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
	virtual Vertex GetCenter() const = 0;
	virtual operator double() const = 0;
};

class Polygon : public Shape {
public:
	Polygon(const std::string& name_in, const std::vector<Vertex>& vertices_in)
		:
		shapeName(name_in),
		vertices(vertices_in)
	{}
	friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
	virtual inline std::string GetName() const { return shapeName; }
	virtual inline std::vector<Vertex> GetVertices() const { return vertices; }
	inline void SetVertices(const std::vector<Vertex>& verts) { vertices = verts; }
	virtual ~Polygon() = default;
private:
	std::string shapeName;
	std::vector<Vertex> vertices;
};

class Triangle : public Polygon {
public:
	Triangle(const std::vector<Vertex>& vertices_in)
		:
		Polygon("Triangle", vertices_in)
	{
		assert(vertices_in.size() == 3);
	}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Triangle& shape);
};

class Square : public Polygon {
public:
	Square(const Vertex& pos, float width)
		:
		pos(pos),
		width(width),
		Polygon("Square", FromWidth(pos, width))
	{}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Square& shape);
private:
	static std::vector<Vertex> FromWidth(const Vertex& v, float width);
private:
	Vertex pos;
	float width;
};

class Rectangle : public Polygon {
public:
	Rectangle( const Vertex& pos, float width, float height )
		:
		pos(pos),
		width(width),
		height(height),
		Polygon("Rectangle", FromWidthAndHeight(pos, width, height))
	{}
	virtual Vertex GetCenter() const override;
	virtual operator double() const override;
	friend std::istream& operator>>(std::istream& is, Rectangle& shape);
private:
	static std::vector<Vertex> FromWidthAndHeight(const Vertex& v, float width, float height);
private:
	Vertex pos;
	float width;
	float height;
};