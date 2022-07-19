#include "Application.h"
#include <SFML/Window/Event.hpp>

Application::Application(std::uint32_t width, std::uint32_t height, const std::string& title)
	: m_window(sf::VideoMode(width, height), title) {}

void Application::execute() {
	while (m_window.isOpen()) {

		sf::Event event;
		while (m_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}

		m_window.clear();

		m_window.display();
	}
}
