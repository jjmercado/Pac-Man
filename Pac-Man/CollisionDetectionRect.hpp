#pragma once
#include <SFML/Graphics.hpp>

class CollisionDetectionRect
{
	public:
		CollisionDetectionRect();
		CollisionDetectionRect(sf::Vector2f startPos, sf::Vector2f direction);
		~CollisionDetectionRect();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime, sf::Vector2f velocity);
		sf::RectangleShape collisionDetectionRect;
		sf::Vector2f direction;

	private:
};

