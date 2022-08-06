#pragma once
#include <cstddef>
#include <vector>
#include "Size.h"
#include "Coords.h"

template <typename T>
class Array2D {
private:
	std::vector<T> m_array;
	std::size_t m_width;
public:
	Array2D(const Size& size, const T& value = T()) 
		: m_array(size.width * size.height, value),
		  m_width(size.width) {}
	~Array2D() = default;
private:
	std::size_t getIndex(const Coords& position) const {
		return position.x + position.y * m_width;
	}
public:
	T& operator[](const Coords& position) {
		return m_array[getIndex(position)];
	}

	const T& operator[](const Coords& position) const {
		return m_array[getIndex(position)];
	}

	void fill(const T& value) {
		std::fill(m_array.begin(), m_array.end(), value);
	}
};