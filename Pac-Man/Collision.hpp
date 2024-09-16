#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
	public:
		Collision(sf::Vector2f position, int width, int height);
		~Collision();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);

	private:
		sf::Image collisionImage;
		sf::Texture collisionTexture;
		sf::Sprite collision;
};

