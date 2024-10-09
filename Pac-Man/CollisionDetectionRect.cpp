#include "CollisionDetectionRect.hpp"

CollisionDetectionRect::CollisionDetectionRect(sf::Vector2f position, sf::Vector2f direction)
{
	image.create(49, 49, sf::Color::White);
	texture.loadFromImage(image);
	sprite.setOrigin(24.5, 24.5);
	sprite.setTexture(texture);
	sprite.setPosition(position);
	this->direction = direction;
}

CollisionDetectionRect::~CollisionDetectionRect()
{
}

void CollisionDetectionRect::Update(sf::Time deltaTime, sf::Vector2f position)
{
	sprite.setPosition(position);
}

void CollisionDetectionRect::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void CollisionDetectionRect::SetColor(sf::Color color)
{
	sprite.setColor(color);
}

bool CollisionDetectionRect::CheckCollisionWithWallColored(const std::vector<Collision*>& collisionRects)
{
	for (auto& rect : collisionRects)
	{
		if (sprite.getGlobalBounds().intersects(rect->collision.getGlobalBounds()))
		{
			SetColor(sf::Color::White);
			return true;
		}
		else
		{
			SetColor(sf::Color::Blue);
		}
	}
	return false;
}
