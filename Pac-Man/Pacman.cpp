#include "Pacman.hpp"

Pacman::Pacman()

{
	if (!pacmanTexture.loadFromFile("..\\pacman.png"))
	{
		std::cout << "Error loading pacman.png" << std::endl;
	}
	pacmanTexture.setSmooth(true);
	pacman.setTextureRect(sf::IntRect(0, 0, 50, 50));
	pacman.setTexture(pacmanTexture);
	pacman.setPosition(350, 650);
	pacman.setOrigin(25, 25);
	pacman.setScale(-1.0, -1.0);
}

Pacman::~Pacman()
{
}

void Pacman::Render(sf::RenderWindow& window)
{
	window.draw(pacman);
}

void Pacman::Animation()
{
	sf::Time time = clock.getElapsedTime();
	float delay = 0.1f; // Zeit in Sekunden zwischen den Frames
	static int currentFrame = 0; // Aktueller Frame-Index
	static sf::Time lastUpdateTime = sf::Time::Zero; // Zeit des letzten Frame-Wechsels

	std::vector<sf::IntRect> pacmanFrames;
	pacmanFrames.push_back(sf::IntRect(0, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(50, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(100, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(150, 0, 50, 50));

	if (time - lastUpdateTime >= sf::seconds(delay))
	{
		currentFrame = (currentFrame + 1) % pacmanFrames.size(); // Nächster Frame
		pacman.setTextureRect(pacmanFrames[currentFrame]);
		lastUpdateTime = time; // Timer zurücksetzen
	}
}
