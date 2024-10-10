#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.hpp"

class Signpost
{
	public:
		Signpost(sf::Vector2f startPos);
		~Signpost();
		void GenerateRandomNumber();
		void Update(sf::Time deltaTime, Ghost& ghost);
		void Render(sf::RenderWindow& window);
		void SetColor(sf::Color color);
		void SetDirection(sf::Vector2f direction);
		void SetObjectDirection(Ghost& ghost);

	private:
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		std::vector<sf::Vector2f> directions;
		int randomNumber;
		sf::Vector2f randomDirection;
};

