#include "Ghost.hpp"

Ghost::Ghost(sf::Color color, sf::Vector2f startPos)
{
	if (!ghostTexture.loadFromFile("..\\Ghost.png", sf::IntRect(0,0,50,50)))
	{
		std::cout << "Error loading ghost.png" << std::endl;
	}
	else
	{
		ghost.setColor(color);
		ghost.setTexture(ghostTexture);
		ghost.setPosition(startPos);
	}

	if (!eyesBackgroundTexture.loadFromFile("..\\eyesBack.png"))
	{
		std::cout << "Error loading eyesbackground.png" << std::endl;
	}
	else
	{
		eyesBackground.setTexture(eyesBackgroundTexture);
		eyesBackground.setPosition(ghost.getPosition().x + 15, ghost.getPosition().y + 15);
	}

	if (!pupilsTexture.loadFromFile("..\\pupils.png"))
	{
		std::cout << "Error loading pupils.png" << std::endl;
	}
	else
	{
		pupils.setTexture(pupilsTexture);
		pupils.setPosition(eyesBackground.getPosition());
	}
}

Ghost::~Ghost()
{
}

void Ghost::Render(sf::RenderWindow& window)
{
	window.draw(ghost);
	window.draw(eyesBackground);
	window.draw(pupils);
}
