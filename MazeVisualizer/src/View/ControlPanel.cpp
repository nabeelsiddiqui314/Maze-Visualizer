#include "ControlPanel.h"
#include "../Maze/Maze.h"
#include <SFML/Window/Event.hpp>

ControlPanel::ControlPanel(Maze* maze) : m_maze(maze) {
	m_mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);

	m_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 4.0f);
	
	initButtons();
	initComboBoxes();
	
	m_box->Pack(m_generatorCB);
	m_box->Pack(m_generateButton);
	m_box->Pack(m_pathfinderCB);
	m_box->Pack(m_findPathButton);
	m_box->Pack(m_randomizePathButton);

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

void ControlPanel::initButtons() {
	m_generateButton = sfg::Button::Create("Generate");
	m_generateButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { m_maze->generate(); });

	m_findPathButton = sfg::Button::Create("Find path");
	m_findPathButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { m_maze->findPath(); });

	m_randomizePathButton = sfg::Button::Create("Randomize path ends");
	m_randomizePathButton->GetSignal(sfg::Widget::OnLeftClick).Connect([=]() { m_maze->randomizePathEnds(); });
}

void ControlPanel::initComboBoxes() {
	m_generatorCB = sfg::ComboBox::Create();

	for (auto& name : m_algorithmFactory.getGeneratorNames())
		m_generatorCB->AppendItem(name);

	m_generatorCB->GetSignal(sfg::ComboBox::OnSelect).Connect([&]() {
		m_maze->setGenerator(m_algorithmFactory.getGenerator(m_generatorCB->GetSelectedText()));
	});

	m_pathfinderCB = sfg::ComboBox::Create();

	for (auto& name : m_algorithmFactory.getPathFinderNames())
		m_pathfinderCB->AppendItem(name);

	m_pathfinderCB->GetSignal(sfg::ComboBox::OnSelect).Connect([&]() {
		m_maze->setPathfinder(m_algorithmFactory.getPathfinder(m_pathfinderCB->GetSelectedText()));
	});
}