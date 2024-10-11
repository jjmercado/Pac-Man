#include "PowerPellet.hpp"

PowerPellet::PowerPellet()
{
}

PowerPellet::PowerPellet(sf::Vector2f startPos)
{
	circle.setRadius(12);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(startPos);
	circle.setOrigin(6, 6);
	points = 50;
}

PowerPellet::~PowerPellet()
{
}

void PowerPellet::Render(sf::RenderWindow& window)
{
	window.draw(circle);
}

void PowerPellet::Update(sf::Time deltaTime)
{
}

void PowerPellet::SetPosition(sf::Vector2f position)
{
	circle.setPosition(position);
}

sf::FloatRect PowerPellet::GetGlobalBounds()
{
	return circle.getGlobalBounds();
}

void PowerPellet::Remove()
{
	//punkte konto erhöhen
	circle.setFillColor(sf::Color::Transparent);
	points = 0;
}

void PowerPellet::Reset()
{
	circle.setFillColor(sf::Color::Yellow);
	points = 50;
}
