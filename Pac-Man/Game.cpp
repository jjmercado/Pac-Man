#include "Game.hpp"

Game::Game() : frameCount(0), fpsClock(), backgroundTexture(), background(), 
				redGhost(sf::Color::Red, sf::Vector2f(325,375)), 
				pinkGhost(sf::Color::Magenta, sf::Vector2f(275, 427)),
				orangeGhost(sf::Color(255, 165, 0), sf::Vector2f(325, 427)),
				turquoiseGhost(sf::Color::Cyan, sf::Vector2f(375, 427)),
				pacman()
{
	if (!backgroundTexture.loadFromFile("..\\Background.png"))
	{
		std::cout << "Error loading background.png" << std::endl;
	}
	else
	{
		background.setTexture(backgroundTexture);
		background.setPosition(0, 100);
	}
}

Game::~Game()
{
}

void Game::Run(sf::RenderWindow& window)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			Events(window);
			Update(TimePerFrame);
			Render(window);

			frameCount++;
			if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
			{
				std::cout << "FPS: " << frameCount << std::endl;
				frameCount = 0;
				fpsClock.restart();
			}
		}

	}
}

void Game::Events(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Game::Update(sf::Time deltaTime)
{
}

void Game::Render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(background);
	redGhost.Render(window);
	pinkGhost.Render(window);
	orangeGhost.Render(window);
	turquoiseGhost.Render(window);
	pacman.Render(window);
	window.display();
}

void Game::Reset()
{
}
