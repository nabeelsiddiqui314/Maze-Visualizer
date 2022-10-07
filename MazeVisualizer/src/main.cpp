#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Maze Visualizer");
	Application application(window.getSize().x, window.getSize().y);

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

		window.clear();

		application.update();
		application.render(window);

		window.display();
	}

	return 0;
}