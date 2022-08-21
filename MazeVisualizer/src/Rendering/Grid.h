#pragma once
#include <SFML/Graphics.hpp>
#include "../Util/Coords.h"
#include "../Util/Size.h"

class Grid {
public:
	Grid(const Size& size, int cellWidth, int spacing, const sf::Color& color = sf::Color::White);
	~Grid() = default;
public:
	void setCellColor(const Coords& position, const sf::Color& color);
	sf::Color getCellColor(const Coords& position) const;

	void render(sf::RenderTarget& target);
private:
	std::size_t getFirstCellVertex(const Coords& position) const;
private:
	sf::VertexArray m_vertices;
	int m_width;
};