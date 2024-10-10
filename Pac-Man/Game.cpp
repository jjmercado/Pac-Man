#include "Game.hpp"

Game::Game() : frameCount(0), fpsClock(), backgroundTexture(), background(), 
				redGhost(sf::Color::Red, sf::Vector2f(350,350), 2.0f), 
				pinkGhost(sf::Color::Magenta, sf::Vector2f(300, 450), 5.0f),
				orangeGhost(sf::Color(255, 165, 0), sf::Vector2f(350, 450), 5.0f),
				turquoiseGhost(sf::Color::Cyan, sf::Vector2f(400, 450), 5.0f),
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

	// Inner collision rects left side
	collisionRects.push_back(new Collision(sf::Vector2f(100, 200), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(100, 350), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(100, 500), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(100, 650), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(250, 200), 50, 150));
	collisionRects.push_back(new Collision(sf::Vector2f(250, 700), 50, 50));

	// Inner collision rects right side
	collisionRects.push_back(new Collision(sf::Vector2f(550, 200), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(550, 350), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(550, 500), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(550, 650), 100, 100));
	collisionRects.push_back(new Collision(sf::Vector2f(450, 200), 50, 150));
	collisionRects.push_back(new Collision(sf::Vector2f(450, 700), 50, 50));

	// Middle collision rects
	collisionRects.push_back(new Collision(sf::Vector2f(350, 150), 50, 200));

	// Ghost house collision rects
	collisionRects.push_back(new Collision(sf::Vector2f(250, 400), 100, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(250, 450), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(400, 400), 100, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(450, 450), 50, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(250, 500), 250, 50));

	// T collions rects
	collisionRects.push_back(new Collision(sf::Vector2f(250, 600), 250, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(350, 650), 50, 100));

	// Top half collision rects
	collisionRects.push_back(new Collision(sf::Vector2f(0, 100), 800, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(0, 150), 50, 300));
	collisionRects.push_back(new Collision(sf::Vector2f(700, 150), 50, 300));

	// Bottom half collision rects
	collisionRects.push_back(new Collision(sf::Vector2f(0, 800), 800, 50));
	collisionRects.push_back(new Collision(sf::Vector2f(0, 500), 50, 300));
	collisionRects.push_back(new Collision(sf::Vector2f(700, 500), 50, 300));

	for (auto& rect : collisionRects)
	{
		rect->SetColor(sf::Color::Red);
	}

	//signposts
	signposts.resize(10);

	//left left side from top down
	signposts[0] = new Signpost(sf::Vector2f(50, 150));
	signposts[1] = new Signpost(sf::Vector2f(50, 300));
	signposts[2] = new Signpost(sf::Vector2f(50, 450));
	signposts[3] = new Signpost(sf::Vector2f(50, 600));
	signposts[4] = new Signpost(sf::Vector2f(50, 750));

	//left middle side from top down
	signposts[5] = new Signpost(sf::Vector2f(200, 150));
	signposts[6] = new Signpost(sf::Vector2f(200, 300));
	signposts[7] = new Signpost(sf::Vector2f(200, 450));
	signposts[8] = new Signpost(sf::Vector2f(200, 600));
	signposts[9] = new Signpost(sf::Vector2f(200, 750));

	for (auto& signpost : signposts)
	{
		signpost->SetColor(sf::Color::Green);
	}

	//signposts directions
	signposts[0]->SetDirection(Direction::Right);
	signposts[0]->SetDirection(Direction::Down);

	signposts[1]->SetDirection(Direction::Up);
	signposts[1]->SetDirection(Direction::Right);
	signposts[1]->SetDirection(Direction::Down);

	signposts[2]->SetDirection(Direction::Up);
	signposts[2]->SetDirection(Direction::Right);
	signposts[2]->SetDirection(Direction::Down);
	signposts[2]->SetDirection(Direction::Left);

	signposts[3]->SetDirection(Direction::Up);
	signposts[3]->SetDirection(Direction::Right);
	signposts[3]->SetDirection(Direction::Down);

	signposts[4]->SetDirection(Direction::Up);
	signposts[4]->SetDirection(Direction::Right);

	signposts[5]->SetDirection(Direction::Left);
	signposts[5]->SetDirection(Direction::Right);
	signposts[5]->SetDirection(Direction::Down);

	signposts[6]->SetDirection(Direction::Up);
	signposts[6]->SetDirection(Direction::Left);
	signposts[6]->SetDirection(Direction::Down);

	signposts[7]->SetDirection(Direction::Up);
	signposts[7]->SetDirection(Direction::Down);
	signposts[7]->SetDirection(Direction::Left);

	signposts[8]->SetDirection(Direction::Up);
	signposts[8]->SetDirection(Direction::Left);
	signposts[8]->SetDirection(Direction::Down);

	signposts[9]->SetDirection(Direction::Up);
	signposts[9]->SetDirection(Direction::Right);
	signposts[9]->SetDirection(Direction::Left);

	//init signposts rnd direction necessary for the size of the array
	for (auto& signpost : signposts)
	{
		signpost->GenerateRandomNumber();
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

		pacman.Events(event);
	}
}

void Game::Update(sf::Time deltaTime)
{
	pacman.Update(deltaTime, collisionRects);
	redGhost.Update(deltaTime, collisionRects);

	for (auto& signpost : signposts)
	{
		signpost->Update(deltaTime, redGhost);
	}
}

void Game::Render(sf::RenderWindow& window)
{
	window.clear();
	window.draw(background);
	//pinkGhost.Render(window);
	//orangeGhost.Render(window);
	//turquoiseGhost.Render(window);
	for(auto& rect : collisionRects)
	{
		rect->Render(window);
	}
	redGhost.Render(window);
	pacman.Render(window);

	for (auto& signpost : signposts)
	{
		signpost->Render(window);
	}

	for (int i = 0; i < window.getSize().y; i += 50)
	{
		lineY[0] = sf::Vertex(sf::Vector2f(0, i), sf::Color::White);
		lineY[1] = sf::Vertex(sf::Vector2f(window.getSize().x, i), sf::Color::White);
		window.draw(lineY, 2, sf::Lines);
		for (int j = 0; j < window.getSize().x; j += 50)
		{
			lineX[0] = sf::Vertex(sf::Vector2f(j, 0), sf::Color::White);
			lineX[1] = sf::Vertex(sf::Vector2f(j, window.getSize().y), sf::Color::White);
			window.draw(lineX, 2, sf::Lines);
		}
	}
	window.display();
}

void Game::Reset()
{
}
