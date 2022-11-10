#pragma once
#include <SFML/Graphics.hpp>
#include "../Util/Coords.h"
#include "../Util/Size.h"

class Grid : public sf::Drawable {
public:
	Grid(const Size& size, int cellWidth, int spacing, const sf::Color& color = sf::Color::White);
	~Grid() = default;
public:
	void setPosition(const sf::Vector2f& positon);
	sf::Vector2f getPosition() const;

	void setCellColor(const Coords& position, const sf::Color& color);
	sf::Color getCellColor(const Coords& position) const;

	int getCellWidth() const;
	int getSpacing() const;

	sf::Vector2f getSize() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	std::size_t getFirstCellVertex(const Coords& position) const;
private:
	sf::VertexArray m_vertices;
	sf::Vector2f m_position;
	const sf::Vector2f m_size;
	const int m_width;
	const int m_cellWidth;
	const int m_spacing;
};