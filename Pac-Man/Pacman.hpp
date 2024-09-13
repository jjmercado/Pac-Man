#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pacman
{
	public:
		Pacman();
		~Pacman();
		void Events(sf::Event event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void Animation(sf::Vector2f direction);

	private:
		sf::Texture pacmanTexture;
		sf::Sprite pacman;
		sf::Clock clock;
		int currentFrame;
		sf::Vector2f direction;
		float speed;
};

