#pragma once
#include <SFGUI/Widgets.hpp>

class Maze;

class ControlPanel {
public:
	ControlPanel(Maze* maze);
	~ControlPanel() = default;
public:
	sfg::Window::Ptr getWindow() const;
	void onEvent(const sf::Event& event);
private:
	sfg::Window::Ptr m_mainWindow;
	sfg::Box::Ptr m_box;
	sfg::Button::Ptr m_generateButton;
	sfg::Button::Ptr m_findPathButton;
};