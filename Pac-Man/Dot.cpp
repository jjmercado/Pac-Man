#include "Dot.hpp"

Dot::Dot()
{
	circle.setRadius(5);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(275, 575);
	circle.setOrigin(2.5, 2.5);
	points = 10;
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
	//punkte konto erhöhen
	circle.setFillColor(sf::Color::Transparent);
	points = 0;
}

void Dot::Reset()
{
	circle.setFillColor(sf::Color::Yellow);
	points = 10;
}
