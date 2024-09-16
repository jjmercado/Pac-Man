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

	collisionRects.push_back(new Collision(sf::Vector2f(75, 175), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(225, 175), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(425, 175), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(525, 175), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(225, 325), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(325, 275), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(425, 325), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(225, 425), 25, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(450, 425), 25, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(325, 525), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(225, 525), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(425, 525), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(75, 625), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(225, 625), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(425, 625), 50, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(525, 625), 100, 100));
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

		pacman.Events(event);
	}
}

void Game::Update(sf::Time deltaTime)
{
	pacman.Update(deltaTime);
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
	for(auto& rect : collisionRects)
	{
		rect->Render(window);
	}
	window.display();
}

void Game::Reset()
{
}
