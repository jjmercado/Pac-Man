#include "CollisionDetectionRect.hpp"



CollisionDetectionRect::CollisionDetectionRect()
{
}

CollisionDetectionRect::CollisionDetectionRect(sf::Vector2f startPos, sf::Vector2f direction)
{
	collisionDetectionRect.setSize(sf::Vector2f(50, 50));
	collisionDetectionRect.setFillColor(sf::Color::Blue);
	collisionDetectionRect.setOrigin(25, 25);
	collisionDetectionRect.setPosition(startPos);
	this->direction = direction;
}

CollisionDetectionRect::~CollisionDetectionRect()
{
}

void CollisionDetectionRect::Render(sf::RenderWindow& window)
{
	window.draw(collisionDetectionRect);
}

void CollisionDetectionRect::Update(sf::Time deltaTime, sf::Vector2f velocity)
{
	collisionDetectionRect.move(velocity);
}
