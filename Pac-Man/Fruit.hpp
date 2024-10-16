#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Fruit
{
	public:
		Fruit();
		Fruit(sf::IntRect rect, int points);
		~Fruit();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		sf::FloatRect GetGlobalBounds();
		void Remove();
		int GetPoints();
		bool isActive;
	
	private:
		bool SetStartTime();
		float clockTime;
		sf::Texture texture;
		sf::Sprite sprite;
		int points;
		sf::Clock startClock;
};

