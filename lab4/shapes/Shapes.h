#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include <type_traits>

template<class T>
concept Vert = requires {
	std::is_scalar_v<T>;
};

template<Vert T>
struct Vertex {
	Vertex() = default;
	Vertex(T x_in, T y_in)
		: 
		x(x_in), y(y_in) {}
	Vertex operator+(const Vertex& v_in) const {
		return Vertex(x + v_in.x, y + v_in.y);
	}
	Vertex operator-(const Vertex& v_in) const {
		return Vertex(x - v_in.x, y - v_in.y);
	}
	Vertex& operator+=(const Vertex& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}
	Vertex& operator-=(const Vertex& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
	bool operator==(const Vertex& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Vertex& rhs) const {
		return !(*this == rhs);
	}
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
		os << "(" << vertex.x << " ," << vertex.y << ")";
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Vertex& vertex) {
		is >> vertex.x >> vertex.y;
		return is;
	}
public:
	T x = 0.0f;
	T y = 0.0f;
};

template<Vert T>
class Shape {
public:
	virtual Vertex<T> GetCenter() const = 0;
	virtual double GetArea() const = 0;
	virtual explicit operator double() const = 0;
};

template<Vert T>
class Polygon : public Shape<T> {
protected:
	Polygon(const std::string& name_in, const std::vector<Vertex<T>>& vertices_in)
		:
		shapeName(name_in),
		vertices(vertices_in)
	{}
public:
	friend std::ostream& operator<<(std::ostream& os, const Polygon& shape)
	{
		os << shape.GetName() << ": " << " { ";
		for (auto& v : shape.vertices) {
			os << v;
		}
		os << "}";

		return os;
	}
	virtual inline std::string GetName() const { return shapeName; }
	virtual inline std::vector<Vertex> GetVertices() const { return vertices; }
	inline void SetVertices(const std::vector<Vertex>& verts) { vertices = verts; }
	virtual ~Polygon() = default;
	bool operator==(const Polygon& rhs) const {
		if (GetVertices().size() != rhs.GetVertices().size())
		{
			return false;
		}

		auto size = GetVertices().size();
		for (int i = 0, j = 0; j < size; ++j)
		{
			if (i == size)
			{
				return true;
			}
			else if (vertices[i] == rhs.vertices[j])
			{
				++i;
				j = -1;
			}
		}
		return false;
	}
protected:
	std::string shapeName;
	std::vector<Vertex<T>> vertices;
};

template<Vert T>
class Triangle : public Polygon<T> {
public:
	Triangle(const std::vector<Vertex<T>>& vertices_in)
		:
		Polygon("Triangle", vertices_in)
	{
		assert(vertices_in.size() == 3);
	}
	virtual Vertex<T> GetCenter() const override {
		auto tri = GetVertices();

		float centerX = (tri[0].x + tri[1].x + tri[2].x) / 3.0f;
		float centerY = (tri[0].y + tri[1].y + tri[2].y) / 3.0f;

		return Vertex<T>{ centerX, centerY };
	}
	virtual double GetArea() const override {
		auto verts = GetVertices();

		double area = 0.5 * abs((verts[0].x - verts[2].x) * (verts[1].y - verts[0].y)
			- (verts[0].x - verts[1].x) * (verts[2].y - verts[0].y));

		return area;
	}
	virtual explicit operator double() const override {
		return GetArea();
	}
	bool operator==(const Triangle& rhs) const {
		for (int i = 0, j = 0; j < 3; ++j)
		{
			if (i == 3)
			{
				return true;
			}
			else if (vertices[i] == rhs.vertices[j])
			{
				++i;
				j = -1;
			}
		}
		return false;
	}
	friend std::istream& operator>>(std::istream& is, Triangle& shape) {
		std::vector<Vertex<T>> verts;

		is >> verts[0];
		is >> verts[1];
		is >> verts[2];

		tri.SetVertices(verts);

		return is;
	}
};

template<Vert T>
class Square : public Polygon<T> {
public:
	Square(const Vertex<T>& pos, T width)
		:
		pos(pos),
		width(width),
		Polygon("Square", FromWidth(pos, width))
	{}
	virtual Vertex<T> GetCenter() const override {
		return Vertex<T>{ pos.x + width * (T)0.5f, pos.y + width * (T)0.5f };
	}
	virtual explicit operator double() const override {
		return GetArea();
	}
	virtual double GetArea() const override {
		return width * width;
	}
	friend std::istream& operator>>(std::istream& is, Square& shape) {
		is >> sqr.pos;
		is >> sqr.width;

		return is;
	}
	bool operator==(const Square& rhs) const {
		return width == rhs.width && pos == rhs.pos;
	}
private:
	static std::vector<Vertex<T>> FromWidth(const Vertex<T>& v, float width) {
		std::vector<Vertex> verts;

		verts.push_back(v);
		verts.push_back({ v.x + width, v.y });
		verts.push_back({ v.x, v.y + width });
		verts.push_back({ v.x + width, v.y + width });

		return verts;
	}
private:
	Vertex<T> pos;
	T width;
};

template<Vert T>
class Rectangle : public Polygon<T> {
public:
	Rectangle( const Vertex<T>& pos, T width, T height )
		:
		pos(pos),
		width(width),
		height(height),
		Polygon("Rectangle", FromWidthAndHeight(pos, width, height))
	{}
	virtual Vertex<T> GetCenter() const override {
		return Vertex<T>{ pos.x + width * (T)0.5f, pos.y + height * (T)0.5f };
	}
	virtual explicit operator double() const override {
		return GetArea();
	}
	virtual double GetArea() const override {
		return width * height;
	}
	friend std::istream& operator>>(std::istream& is, Rectangle& shape) {
		is >> shape.pos;
		is >> shape.width;
		is >> shape.height;

		return is;
	}
	bool operator==(const Rectangle& rhs) const {
		return width == rhs.width && height == rhs.height && pos == rhs.pos;
	}
private:
	static std::vector<Vertex<T>> FromWidthAndHeight(const Vertex<T>& v, T width, T height) {
		std::vector<Vertex<T>> verts;

		verts.push_back(v);
		verts.push_back({ v.x + width, v.y });
		verts.push_back({ v.x, v.y + height });
		verts.push_back({ v.x + width, v.y + height });

		return verts;
	}
private:
	Vertex<T> pos;
	T width;
	T height;
};