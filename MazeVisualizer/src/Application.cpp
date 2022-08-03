#include "Application.h"
#include <SFML/Window/Event.hpp>
#include "Util/Random.h"

#include "Algorithms/Generation/RecursiveBacktracker.h"

Application::Application(std::uint32_t width, std::uint32_t height, const std::string& title)
	: m_window(sf::VideoMode(width, height), title), m_maze({(int)width / 21, (int)height / 21}), m_visualizer(&m_maze, 20, 1) {
	Random::init();
	
	m_maze.registerObserver(&m_visualizer);
	m_maze.setGenerator(std::make_unique<RecursiveBacktracker>());
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
				break;
			}
		}

		m_window.clear();

		m_visualizer.render(m_window);

		m_window.display();
	}
}
