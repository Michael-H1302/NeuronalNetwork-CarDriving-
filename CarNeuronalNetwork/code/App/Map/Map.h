#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Map
{
	public:

		static std::vector<sf::RectangleShape*> DrawLine(sf::Vector2f StartPos, sf::Vector2f EndPos);

};