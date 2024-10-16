#include "Dot.hpp"

Dot::Dot()
{
}

Dot::Dot(sf::Vector2f startPos)
{
	circle.setRadius(5);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(startPos);
	circle.setOrigin(2.5, 2.5);
	points = 10;
	isActive = true;
}

Dot::~Dot()
{
}

void Dot::Render(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Dot::Update(sf::Time deltaTime)
{
}

void Dot::SetPosition(sf::Vector2f position)
{
	circle.setPosition(position);
}

sf::FloatRect Dot::GetGlobalBounds()
{
    return circle.getGlobalBounds();
}

void Dot::Remove()
{
	circle.setFillColor(sf::Color::Transparent);
	points = 0;
	isActive = false;
}

void Dot::Reset()
{
	circle.setFillColor(sf::Color::Yellow);
	points = 10;
	isActive = true;
}

int Dot::GetPoints()
{
	return points;
}
