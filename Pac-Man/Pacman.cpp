#include "Pacman.hpp"

Pacman::Pacman()
{
	if (!pacmanTexture.loadFromFile("..\\pacman.png", sf::IntRect(0,0,50,50)))
	{
		std::cout << "Error loading pacman.png" << std::endl;
	}
	pacmanTexture.setSmooth(true);
	pacman.setTexture(pacmanTexture);
	pacman.setPosition(335, 618);
	pacman.setRotation(22);
}

Pacman::~Pacman()
{
}

void Pacman::Render(sf::RenderWindow& window)
{
	window.draw(pacman);
}
