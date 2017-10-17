#include "Map.h"

std::vector<sf::RectangleShape*> Map::DrawLine(sf::Vector2f StartPos, sf::Vector2f EndPos)
{
	std::vector<sf::RectangleShape*> Rects;

	float Gradiant = (EndPos.y - StartPos.y) / (EndPos.x - StartPos.x);

	for (int x = static_cast<int>(StartPos.x); x < static_cast<int>(EndPos.x); x++)
	{
		Rects.push_back(new sf::RectangleShape);
		Rects[Rects.size() - 1]->setSize(sf::Vector2f(5, 5));
		Rects[Rects.size() - 1]->setPosition(static_cast<float>(x), StartPos.y + static_cast<float>((x - StartPos.x) * Gradiant));
		Rects[Rects.size() - 1]->setFillColor(sf::Color(0, 0, 255));
	}

	return Rects;
}