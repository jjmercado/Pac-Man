#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pacman
{
	public:
		Pacman();
		~Pacman();
		void Render(sf::RenderWindow& window);

	private:
		sf::Texture pacmanTexture;
		sf::Sprite pacman;
};

