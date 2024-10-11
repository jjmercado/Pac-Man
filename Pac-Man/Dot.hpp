#pragma once
#include <SFML/Graphics.hpp>

class Dot
{
	public:
		Dot();
		~Dot();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void SetPosition(sf::Vector2f position);
		sf::Sprite GetSprite();
};

