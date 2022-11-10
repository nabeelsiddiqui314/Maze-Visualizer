#pragma once
#include "Maze/Maze.h"
#include "View/MazeView.h"
#include "View/ControlPanel.h"
#include <SFGUI/Widgets.hpp>

class Application {
public:
	Application(std::uint32_t width, std::uint32_t height);
	~Application() = default;
public:
	void onEvent(const sf::RenderWindow& window, const sf::Event& event);
	void update(float dt);
	void render(sf::RenderWindow& window);
private:
	Maze m_maze;
	MazeView m_mazeView;
	ControlPanel m_panel;

	sfg::Desktop m_desktop;
};