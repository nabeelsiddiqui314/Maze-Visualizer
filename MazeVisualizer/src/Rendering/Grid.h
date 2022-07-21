#pragma once
#include <SFML/Graphics.hpp>

class Grid {
public:
	Grid(int width, int height, int cellWidth, int spacing, const sf::Color& color = sf::Color::White);
	~Grid() = default;
public:
	void setCellColor(const sf::Vector2i& position, const sf::Color& color);
	void render(sf::RenderTarget& target);
private:
	std::size_t getFirstCellVertex(const sf::Vector2i& position) const;
private:
	sf::VertexArray m_vertices;
	int m_width;
};