#include "Grid.h"

Grid::Grid(const Size& size, int cellWidth, int spacing, const sf::Color& color)
 : m_vertices(sf::Quads, size.width * size.height * 4),
   m_position(0.0f, 0.0f),
   m_width(size.width),
   m_cellWidth(cellWidth),
   m_spacing(spacing) {
	int totalWidth = cellWidth + spacing;

	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			std::size_t index = getFirstCellVertex({x, y});
	
			m_vertices[index].position     = sf::Vector2f(x * totalWidth, y * totalWidth);
			m_vertices[index + 1].position = sf::Vector2f(x * totalWidth, y * totalWidth + cellWidth);
			m_vertices[index + 2].position = sf::Vector2f(x * totalWidth + cellWidth, y * totalWidth + cellWidth);
			m_vertices[index + 3].position = sf::Vector2f(x * totalWidth + cellWidth, y * totalWidth);
	
			setCellColor({x, y}, color);
		}
	}
}

void Grid::setPosition(const sf::Vector2f& positon) {
	m_position = positon;
}

sf::Vector2f Grid::getPosition() const {
	return m_position;
}

void Grid::setCellColor(const Coords& position, const sf::Color& color) {
	std::size_t index = getFirstCellVertex(position);

	for (std::size_t i = 0; i < 4; i++) {
		m_vertices[index + i].color = color;
	}
}

sf::Color Grid::getCellColor(const Coords& position) const {
	std::size_t index = getFirstCellVertex(position);
	return m_vertices[index].color;
}

int Grid::getCellWidth() const {
	return m_cellWidth;
}

int Grid::getSpacing() const {
	return m_spacing;
}

void Grid::render(sf::RenderTarget& target) {
	sf::Transform transform;
	transform.translate(m_position);
	target.draw(m_vertices, transform);
}

std::size_t Grid::getFirstCellVertex(const Coords& position) const {
	return (position.x + position.y * m_width) * 4;
}