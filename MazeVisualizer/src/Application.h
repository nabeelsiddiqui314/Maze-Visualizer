#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Maze/Maze.h"
#include "Rendering/MazeView.h"

class Application {
public:
	Application(std::uint32_t width, std::uint32_t height, const std::string& title);
	~Application() = default;
public:
	void execute();
private:
	sf::RenderWindow m_window;
	Maze m_maze;
	MazeView m_mazeView;
};