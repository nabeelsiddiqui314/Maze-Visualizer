#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.h"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Maze Visualizer");
	Application application(window.getSize().x, window.getSize().y);

	sfg::SFGUI sfgui;

	sfg::Desktop desktop;
	application.addGUI(desktop);

	sf::Clock clock;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			desktop.HandleEvent(event);

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			}
			application.onEvent(window, event);
		}

		desktop.Update(clock.restart().asSeconds());
		application.update();

		window.clear();

		application.render(window);
		sfgui.Display(window);

		window.display();
	}

	return 0;
}