#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pacman
{
	public:
		Pacman();
		~Pacman();
		void Render(sf::RenderWindow& window);
		void Animation();

	private:
		sf::Texture pacmanTexture;
		sf::Sprite pacman;
		sf::Clock clock;
};

