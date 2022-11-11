#include "ControlPanel.h"
#include "../Maze/Maze.h"
#include <SFML/Window/Event.hpp>

ControlPanel::ControlPanel(Maze* maze) {
	m_mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);

	m_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	m_generateButton = sfg::Button::Create("Generate");
	m_generateButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { maze->generate(); });
	m_box->Pack(m_generateButton);

	m_findPathButton = sfg::Button::Create("Find path");
	m_findPathButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { maze->findPath(); });
	m_box->Pack(m_findPathButton);

	m_mainWindow->Add(m_box);
}

sfg::Window::Ptr ControlPanel::getWindow() const {
	return m_mainWindow;
}

void ControlPanel::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::Resized) {
		auto windowAllocation = m_mainWindow->GetAllocation();
		auto boxAllocation = m_box->GetAllocation();

		windowAllocation.width = boxAllocation.width = event.size.width;

		m_mainWindow->SetAllocation(windowAllocation);
		m_box->SetAllocation(boxAllocation);
	}
}