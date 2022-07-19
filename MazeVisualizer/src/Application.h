#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Application {
public:
	Application(std::uint32_t width, std::uint32_t height, const std::string& title);
	~Application() = default;
public:
	void execute();
private:
	sf::RenderWindow m_window;
};