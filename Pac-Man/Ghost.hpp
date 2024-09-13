#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ghost
{
	public:
		Ghost(sf::Color color, sf::Vector2f startPos);
		~Ghost();
		void Render(sf::RenderWindow& window);
		void Animation();

	private:
		sf::Texture ghostTexture;
		sf::Sprite ghost;
		sf::Texture eyesBackgroundTexture;
		sf::Sprite eyesBackground;
		sf::Texture pupilsTexture;
		sf::Sprite pupils;
		sf::Clock clock;
		int currentFrame;
};

