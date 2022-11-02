#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui-SFML.h>
#include "Application.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Maze Visualizer");

	ImGui::SFML::Init(window);

	Application application(window.getSize().x, window.getSize().y);
	sf::Clock deltaClock;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			}
			application.onEvent(window, event);
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		window.clear();

		application.update();
		application.render(window);
		application.imguiRender();

		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}