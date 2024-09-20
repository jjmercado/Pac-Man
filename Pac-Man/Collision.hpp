#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Collision
{
	public:
		Collision(sf::Vector2f position, int width, int height);
		~Collision();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		bool IsColliding(sf::RectangleShape collisionRect);

	private:
		sf::Sprite collision;
		sf::Image collisionImage;
		sf::Texture collisionTexture;
};

