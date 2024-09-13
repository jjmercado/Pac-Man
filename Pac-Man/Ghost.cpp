#include "Ghost.hpp"

Ghost::Ghost(sf::Color color, sf::Vector2f startPos) : currentFrame(0)
{
	if (!ghostTexture.loadFromFile("..\\Ghost.png"))
	{
		std::cout << "Error loading ghost.png" << std::endl;
	}
	else
	{
		ghost.setColor(color);
		ghost.setTextureRect(sf::IntRect(0, 0, 50, 50));
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

void Ghost::Animation()
{
	sf::Time time = clock.getElapsedTime();
	float delay = 0.1f; // Zeit in Sekunden zwischen den Frames
	sf::Time lastUpdateTime = sf::Time::Zero; // Zeit des letzten Frame-Wechsels

	std::vector<sf::IntRect> ghostFrames;
	ghostFrames.push_back(sf::IntRect(0, 0, 50, 50));
	ghostFrames.push_back(sf::IntRect(50, 0, 50, 50));
	ghostFrames.push_back(sf::IntRect(100, 0, 50, 50));

	if (time - lastUpdateTime >= sf::seconds(delay))
	{
		currentFrame = (currentFrame + 1) % ghostFrames.size(); // Nächster Frame
		ghost.setTextureRect(ghostFrames[currentFrame]);
		lastUpdateTime = time; // Timer zurücksetzen
		clock.restart();
	}
}
