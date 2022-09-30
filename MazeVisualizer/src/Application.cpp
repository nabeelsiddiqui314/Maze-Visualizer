#include "Application.h"
#include <SFML/Window/Event.hpp>
#include "Util/Random.h"

#include "Algorithms/Generation/RecursiveBacktracker.h"
#include "Algorithms/Pathfinding/Wavefront.h"

Application::Application(std::uint32_t width, std::uint32_t height, const std::string& title)
	: m_window(sf::VideoMode(width, height), title), m_maze({(int)width / 21, (int)height / 21}), m_mazeView(&m_maze, 20, 1) {
	m_maze.registerObserver(&m_mazeView);
	m_maze.setGenerator(std::make_unique<RecursiveBacktracker>());
	m_maze.setPathfinder(std::make_unique<Wavefront>());
}

void Application::execute() {
	while (m_window.isOpen()) {

		sf::Event event;
		while (m_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
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

		m_window.clear();
		
		m_mazeView.update();
		m_mazeView.render(m_window);

		m_window.display();
	}
}
