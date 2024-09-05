#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>

class Game
{
public:
	Game();
	~Game();
	void Run(sf::RenderWindow& window);

private:
	void Events(sf::RenderWindow& window);
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow& window);
	sf::Clock fpsClock;
	unsigned int frameCount;
	void Reset();
};

