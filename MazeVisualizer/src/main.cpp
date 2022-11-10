#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.h"

#include <SFGUI/SFGUI.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Maze Visualizer");
	window.resetGLStates();

	sfg::SFGUI sfgui;
	
	Application application(window.getSize().x, window.getSize().y);

	sf::Clock clock;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			}
			application.onEvent(window, event);
		}

		application.update(clock.getElapsedTime().asSeconds());

		window.clear();

		application.render(window);
		sfgui.Display(window);

		window.display();
	}

	return 0;
}