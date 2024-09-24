#include "Collision.hpp"

Collision::Collision(sf::Vector2f position, int width, int height)
{
	collisionImage.create(width, height, sf::Color::Red);
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
