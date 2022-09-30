#pragma once
#include <SFML/Graphics/Color.hpp>

namespace Colors {
	const sf::Color Empty = sf::Color::White;
	const sf::Color Wall = sf::Color::Black;
	const sf::Color Path = sf::Color::Yellow;

	const sf::Color GenerationCursor = sf::Color::Red;
	const sf::Color PathCursor = sf::Color::Cyan;
	const sf::Color SearchCursor = sf::Color::Green;

	const sf::Color SearchArea = sf::Color::Magenta;

	const sf::Color PathStart = sf::Color::Blue;
	const sf::Color PathEnd = sf::Color::Blue;
}