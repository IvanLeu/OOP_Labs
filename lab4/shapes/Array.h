#pragma once
#include "Shapes.h"
#include <initializer_list>

template<Vert T>
class Array {
public:
	Array() = default;
	Array(const std::initializer_list<Shape<T>*>& shapes)
	{
		m_capacity = shapes.size();
		m_size = shapes.size();
		m_shapes = new Shape<T> * [m_capacity];

		std::copy_n(shapes.begin(), m_size, begin());
	}
	Array(const Array& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_shapes;

		m_shapes = new Shape * [m_capacity];
		std::copy(other.begin(), other.end(), begin());
	}
	Array& operator=(const Array& other)
	{
		if (this != &other) {
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			delete[] m_shapes;

			m_shapes = new Shape * [m_capacity];
			std::copy(other.begin(), other.end(), begin());
		}

		return *this;
	}
	Array(Array&& other) noexcept
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_shapes;

		m_shapes = other.m_shapes;
		other.m_shapes = nullptr;
	}
	Array& operator=(Array&& other) noexcept
	{
		if (this != &other) {
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			delete[] m_shapes;

			m_shapes = other.m_shapes;
			other.m_shapes = nullptr;
		}
		return *this;
	}
	~Array()
	{
		delete[] m_shapes;
	}
	void push_back(const Shape<T>* shape)
	{
		if (m_size < m_capacity) {
			memcpy(m_shapes[m_size++], shape, sizeof(Shape));
		}
		else {
			m_capacity *= 2;
			auto new_buf = new Shape * [m_capacity];
			std::copy(begin(), end(), new_buf);
			delete[] m_shapes;
			m_shapes = new_buf;

			memcpy(m_shapes[m_size++], shape, sizeof(Shape));
		}
	}
	void pop_back()
	{
		m_shapes[m_size--]->~Shape();
	}
	void erase(size_t index)
	{
		if (index >= 0 && index <= m_size) {
			std::swap(m_shapes[m_size], m_shapes[index]);
			pop_back();
		}
	}
	const Shape<T>* operator[](int index) const
	{
		if (index >= 0 && index <= m_size) {
			return this->m_shapes[index];
		}
		return nullptr;
	}
	Shape<T>* operator[](int index)
	{
		if (index >= 0 && index <= m_size) {
			return this->m_shapes[index];
		}
		return nullptr;
	}
	bool empty() const
	{
		return m_size == 0;
	}
	size_t size() const
	{
		return m_size;
	}
	size_t capacity() const
	{
		return m_capacity;
	}
	void reserve(size_t new_capacity)
	{
		m_capacity = new_capacity;
		if (!m_shapes) {
			m_shapes = new Shape * [m_capacity];
		}
		else {
			auto new_buf = new Shape * [m_capacity];
			std::copy(begin(), end(), new_buf);
			delete[] m_shapes;
			m_shapes = new_buf;
		}
	}
	Shape<T>** data() const
	{
		return m_shapes;
	}
	Shape<T>** begin() const
	{
		return m_shapes;
	}
	Shape<T>** end() const
	{
		return m_shapes + m_size;
	}
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	Shape<T>** m_shapes = nullptr;
};