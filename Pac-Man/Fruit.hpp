#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class State
{
	ACTIVE,
	INACTIVE
};

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
		bool GetState();
		void SetState(State state);
	
	private:
		bool canGetEat;
		void SetStartTime();
		float clockTime;
		sf::Texture texture;
		sf::Sprite sprite;
		int points;
		sf::Clock startClock;
		State currentState;
		void Activate();
		void Deactivate();
};

