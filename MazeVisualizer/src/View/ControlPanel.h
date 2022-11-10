#pragma once
#include <SFGUI/Widgets.hpp>

class Maze;

class ControlPanel {
public:
	ControlPanel(Maze* maze);
	~ControlPanel() = default;
public:
	sfg::Window::Ptr getWindow() const;
private:
	sfg::Window::Ptr m_mainWindow;
	sfg::Button::Ptr m_generateButton;
	sfg::Button::Ptr m_findPathButton;
};