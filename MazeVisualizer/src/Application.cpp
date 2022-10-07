#include "Application.h"
#include <SFML/Window/Event.hpp>
#include "Util/Random.h"

#include "Algorithms/Generation/RecursiveBacktracker.h"
#include "Algorithms/Generation/RecursiveDivision.h"
#include "Algorithms/Pathfinding/Wavefront.h"

Application::Application(std::uint32_t width, std::uint32_t height)
	: m_maze({(int)width / 20, (int)height / 20}), m_mazeView(&m_maze, 20, 0) {
	m_maze.registerObserver(&m_mazeView);
	m_maze.setGenerator(std::make_unique<RecursiveDivision>());
	m_maze.setPathfinder(std::make_unique<Wavefront>());
}

void Application::onEvent(const sf::RenderWindow& window, const sf::Event& event) {
	switch (event.type) {
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::G) {
			m_maze.generate();
		}
		if (event.key.code == sf::Keyboard::P) {
			m_maze.findPath();
		}
		break;
	case sf::Event::MouseButtonPressed:
		Coords cellPosition = m_mazeView.getCellFromPoint(sf::Mouse::getPosition(window));
		if (!m_maze.isOutOfBounds(cellPosition)) {
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				m_maze.setCellAt(cellPosition, Cell::WALL);
			else
				m_maze.setCellAt(cellPosition, Cell::EMPTY);
		}
		break;
	}
}

void Application::update() {
	m_mazeView.update();
}

void Application::render(sf::RenderWindow& window) {
	m_mazeView.render(window);
}