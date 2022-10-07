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

void Application::onEvent(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::G) {
			m_maze.generate();
		}
		if (event.key.code == sf::Keyboard::P) {
			m_maze.findPath();
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