#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pac Man");
	Game game;
	game.Run(window);
	return 0;
}