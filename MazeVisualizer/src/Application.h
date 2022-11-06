#pragma once
#include "Maze/Maze.h"
#include "Rendering/MazeView.h"

namespace sfg {
	class Desktop;
}

class Application {
public:
	Application(std::uint32_t width, std::uint32_t height);
	~Application() = default;
public:
	void onEvent(const sf::RenderWindow& window, const sf::Event& event);
	void addGUI(sfg::Desktop& desktop);
	void update();
	void render(sf::RenderWindow& window);
private:
	Maze m_maze;
	MazeView m_mazeView;
};