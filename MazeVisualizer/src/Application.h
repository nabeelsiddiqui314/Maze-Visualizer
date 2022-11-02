#pragma once
#include "Maze/Maze.h"
#include "Rendering/MazeView.h"

class Application {
public:
	Application(std::uint32_t width, std::uint32_t height);
	~Application() = default;
public:
	void onEvent(const sf::RenderWindow& window, const sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);
	void imguiRender();
private:
	Maze m_maze;
	MazeView m_mazeView;
};