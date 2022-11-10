#include "ControlPanel.h"
#include "../Maze/Maze.h"
#include <SFML/Window/Event.hpp>

ControlPanel::ControlPanel(Maze* maze) {
	m_mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);

	auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	m_generateButton = sfg::Button::Create("Generate");
	m_generateButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { maze->generate(); });
	box->Pack(m_generateButton);

	m_findPathButton = sfg::Button::Create("Find path");
	m_findPathButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { maze->findPath(); });
	box->Pack(m_findPathButton);

	m_mainWindow->Add(box);
}

sfg::Window::Ptr ControlPanel::getWindow() const {
	return m_mainWindow;
}
