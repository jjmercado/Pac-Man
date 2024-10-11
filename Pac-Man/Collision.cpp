#include "Collision.hpp"

Collision::Collision()
{
}

Collision::Collision(sf::Vector2f position, int width, int height)
{
	collisionImage.create(width, height, sf::Color::White);
	collisionTexture.loadFromImage(collisionImage);
	collision.setTexture(collisionTexture);
	collision.setPosition(position);
}

Collision::~Collision()
{
}

void Collision::Render(sf::RenderWindow& window)
{
	window.draw(collision);
}

void Collision::Update(sf::Time time)
{
}

void Collision::SetColor(sf::Color color)
{
	collision.setColor(color);
}

void Collision::SetPosition(sf::Vector2f position)
{
	collision.setPosition(position);
}
