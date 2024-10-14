#pragma once
#include <SFML/Graphics.hpp>

class Dot
{
	public:
		Dot();
		Dot(sf::Vector2f startPos);
		~Dot();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void SetPosition(sf::Vector2f position);
		sf::FloatRect GetGlobalBounds();
		void Remove();
		void Reset();
		int GetPoints();

	private:
		sf::CircleShape circle;
		sf::Sprite sprite;
		int points;
};

