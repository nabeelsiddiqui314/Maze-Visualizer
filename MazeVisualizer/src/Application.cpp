#include "Application.h"
#include <SFML/Window/Event.hpp>
#include "Util/Random.h"

Application::Application(std::uint32_t width, std::uint32_t height)
	: m_maze({(int)width / 20, (int)height / 20}), m_panel(&m_maze) {
	m_mazeView = MazeView::Create(&m_maze, 20, 0);
	
	m_maze.registerObserver(m_mazeView);

	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	auto panelWindow = m_panel.getWindow();
	
	box->Pack(panelWindow);
	box->Pack(m_mazeView);

	m_desktop.Add(box);
}

void Application::onEvent(const sf::RenderWindow& window, const sf::Event& event) {
	m_panel.onEvent(event);
	m_desktop.HandleEvent(event);
}

void Application::update(float dt) {
	m_desktop.Update(dt);
	m_mazeView->update();
	
}

void Application::render(sf::RenderWindow& window) {
	m_mazeView->render();
}