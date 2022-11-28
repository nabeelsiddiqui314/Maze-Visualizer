#pragma once
#include <SFGUI/Widgets.hpp>
#include "../Algorithms/AlgorithmFactory.h"

class Maze;

class ControlPanel {
public:
	ControlPanel(Maze* maze);
	~ControlPanel() = default;
public:
	sfg::Window::Ptr getWindow() const;
	void onEvent(const sf::Event& event);
private:
	void initButtons();
	void initComboBoxes();
private:
	sfg::Window::Ptr m_mainWindow;
	sfg::Box::Ptr m_box;

	sfg::ComboBox::Ptr m_generatorCB;
	sfg::Button::Ptr m_generateButton;

	sfg::ComboBox::Ptr m_pathfinderCB;
	sfg::Button::Ptr m_findPathButton;

	AlgorithmFactory m_algorithmFactory;
	Maze* m_maze;
};