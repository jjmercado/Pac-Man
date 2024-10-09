#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Collision.hpp"

class CollisionDetectionRect
{
	public:
		CollisionDetectionRect(sf::Vector2f position, sf::Vector2f direction);
		~CollisionDetectionRect();
		void Update(sf::Time deltaTime, sf::Vector2f position);
		void Render(sf::RenderWindow& window);
		void SetColor(sf::Color color);
		bool CheckCollisionWithWallColored(const std::vector<Collision*>& collisionRects);
		sf::Vector2f direction;

	private:
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
};

