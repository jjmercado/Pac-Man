#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "Ghost.hpp"
#include "Pacman.hpp"
#include "Collision.hpp"
#include "Signpost.hpp"
#include "Direction.hpp"
#include "Dot.hpp"
#include "PowerPellet.hpp"


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
	sf::Texture backgroundTexture;
	sf::Sprite background;
	void Reset();
	Ghost redGhost;
	Ghost pinkGhost;
	Ghost orangeGhost;
	Ghost turquoiseGhost;
	Pacman pacman;
	std::vector<Collision*> collisionRects;
	std::vector<Signpost*> signposts;
	std::array<Dot, 98> dots;
	std::array<PowerPellet, 4> powerPellets;
	sf::Vertex lineY[2];
	sf::Vertex lineX[2];
	void InitCollisionRects();
	void InitSignposts();
	void InitSignpostDirections();
	void InitDots();
	void InitPowerPellets();
	std::array<sf::Sprite, 3> pacmanUiImages;
	int live;
	sf::Font font;
	sf::Text currentScore;
	sf::Text highScore;
	sf::Text currentScoreLabel;
	sf::Text highScoreLabel;
	int currentPoints;
};

