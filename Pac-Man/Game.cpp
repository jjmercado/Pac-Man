#include "Game.hpp"

Game::Game() : frameCount(0), fpsClock(), backgroundTexture(), background(), 
				redGhost(sf::Color::Red, sf::Vector2f(350,350), 5.0f, Direction::Left), 
				pinkGhost(sf::Color::Magenta, sf::Vector2f(300, 450), 10.0f, Direction::Right),
				orangeGhost(sf::Color(255, 165, 0), sf::Vector2f(350, 450), 15.0f, Direction::Up),
				turquoiseGhost(sf::Color::Cyan, sf::Vector2f(400, 450), 20.0f, Direction::Left),
				pacman(), live(2)
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

	pacmanUiImages[0].setTexture(*pacman.GetTexture());
	pacmanUiImages[0].setTextureRect(sf::IntRect(50, 0, 50, 50));
	pacmanUiImages[0].setPosition(sf::Vector2f(0, 850));

	pacmanUiImages[1].setTexture(*pacman.GetTexture());
	pacmanUiImages[1].setTextureRect(sf::IntRect(50, 0, 50, 50));
	pacmanUiImages[1].setPosition(sf::Vector2f(50, 850));

	pacmanUiImages[2].setTexture(*pacman.GetTexture());
	pacmanUiImages[2].setTextureRect(sf::IntRect(50, 0, 50, 50));
	pacmanUiImages[2].setPosition(sf::Vector2f(100, 850));

	InitCollisionRects();

	for (auto& rect : collisionRects)
	{
		rect->SetColor(sf::Color::Red);
	}

	//signposts
	signposts.resize(36);

	InitSignposts();

	for (auto& signpost : signposts)
	{
		signpost->SetColor(sf::Color::Green);
	}

	InitSignpostDirections();

	//init signposts rnd direction necessary for the size of the array
	for (auto& signpost : signposts)
	{
		signpost->GenerateRandomNumber();
	}

	InitDots();
	InitPowerPellets();
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
	pinkGhost.Update(deltaTime, collisionRects);
	orangeGhost.Update(deltaTime, collisionRects);
	turquoiseGhost.Update(deltaTime, collisionRects);

	for (auto& signpost : signposts)
	{
		signpost->Update(deltaTime, redGhost);
		signpost->Update(deltaTime, pinkGhost);
		signpost->Update(deltaTime, orangeGhost);
		signpost->Update(deltaTime, turquoiseGhost);
	}

	for (auto& dot : dots)
	{
		if (pacman.CollisionWith(dot))
		{
			dot.Remove();
		}
	}

	for (auto& powerPellet : powerPellets)
	{
		if (pacman.CollisionWith(powerPellet))
		{
			powerPellet.Remove();
		}
	}

	if (pacman.CollisionWith(redGhost) || pacman.CollisionWith(pinkGhost) || pacman.CollisionWith(orangeGhost) || pacman.CollisionWith(turquoiseGhost))
	{
		pacmanUiImages[live].setColor(sf::Color::Transparent);
		live--;
		Reset();
	}
}

void Game::Render(sf::RenderWindow& window)
{
	window.clear();

	window.draw(background);

	for (auto& dot : dots)
	{
		dot.Render(window);
	}

	for (auto& powerPellet : powerPellets)
	{
		powerPellet.Render(window);
	}

	redGhost.Render(window);
	pinkGhost.Render(window);
	orangeGhost.Render(window);
	turquoiseGhost.Render(window);
	//for(auto& rect : collisionRects)
	//{
	//	rect->Render(window);
	//}
	pacman.Render(window);
	
	for (auto& pacmanUiImage : pacmanUiImages)
	{
		window.draw(pacmanUiImage);
	}

	//for (auto& signpost : signposts)
	//{
	//	signpost->Render(window);
	//}

	//for (int i = 0; i < window.getSize().y; i += 50)
	//{
	//	lineY[0] = sf::Vertex(sf::Vector2f(0, i), sf::Color::White);
	//	lineY[1] = sf::Vertex(sf::Vector2f(window.getSize().x, i), sf::Color::White);
	//	window.draw(lineY, 2, sf::Lines);
	//	for (int j = 0; j < window.getSize().x; j += 50)
	//	{
	//		lineX[0] = sf::Vertex(sf::Vector2f(j, 0), sf::Color::White);
	//		lineX[1] = sf::Vertex(sf::Vector2f(j, window.getSize().y), sf::Color::White);
	//		window.draw(lineX, 2, sf::Lines);
	//	}
	//}
	window.display();
}

void Game::Reset()
{
	pacman.Reset();
	redGhost.Reset(sf::Vector2f(350, 350), Direction::Left);
	pinkGhost.Reset(sf::Vector2f(300, 450), Direction::Right);
	orangeGhost.Reset(sf::Vector2f(350, 450), Direction::Up);
	turquoiseGhost.Reset(sf::Vector2f(400, 450), Direction::Left);

	if (live < 0)
	{
		live = 2;

		for (auto& dot : dots)
		{
			dot.Reset();
		}

		for (auto& powerPellet : powerPellets)
		{
			powerPellet.Reset();
		}

		for (auto& pacmanUiImage : pacmanUiImages)
		{
			pacmanUiImage.setColor(sf::Color::White);
		}
	}
}

void Game::InitCollisionRects()
{
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
}

void Game::InitSignposts()
{
	//left half of game map
	//left left side from top down
	signposts[0] = new Signpost(sf::Vector2f(50, 150));
	signposts[1] = new Signpost(sf::Vector2f(50, 300));
	signposts[2] = new Signpost(sf::Vector2f(50, 450));
	signposts[3] = new Signpost(sf::Vector2f(50, 600));
	signposts[4] = new Signpost(sf::Vector2f(50, 750));

	//left middle side from top down
	signposts[5] = new Signpost(sf::Vector2f(200, 150));
	signposts[6] = new Signpost(sf::Vector2f(200, 300));
	signposts[7] = new Signpost(sf::Vector2f(200, 350));
	signposts[8] = new Signpost(sf::Vector2f(200, 450));
	signposts[9] = new Signpost(sf::Vector2f(200, 550));
	signposts[10] = new Signpost(sf::Vector2f(200, 600));
	signposts[11] = new Signpost(sf::Vector2f(200, 650));
	signposts[12] = new Signpost(sf::Vector2f(200, 750));

	//left right side from top down
	signposts[13] = new Signpost(sf::Vector2f(300, 150));
	signposts[14] = new Signpost(sf::Vector2f(300, 350));
	signposts[15] = new Signpost(sf::Vector2f(300, 650));
	signposts[16] = new Signpost(sf::Vector2f(300, 750));

	//right half side of game map
	//right left side of game map
	signposts[17] = new Signpost(sf::Vector2f(400, 150));
	signposts[18] = new Signpost(sf::Vector2f(400, 350));
	signposts[19] = new Signpost(sf::Vector2f(400, 650));
	signposts[20] = new Signpost(sf::Vector2f(400, 750));

	//right middle side of game map
	signposts[21] = new Signpost(sf::Vector2f(500, 150));
	signposts[22] = new Signpost(sf::Vector2f(500, 300));
	signposts[23] = new Signpost(sf::Vector2f(500, 350));
	signposts[24] = new Signpost(sf::Vector2f(500, 450));
	signposts[25] = new Signpost(sf::Vector2f(500, 550));
	signposts[26] = new Signpost(sf::Vector2f(500, 600));
	signposts[27] = new Signpost(sf::Vector2f(500, 650));
	signposts[28] = new Signpost(sf::Vector2f(500, 750));

	//right right side of game map
	signposts[29] = new Signpost(sf::Vector2f(650, 150));
	signposts[30] = new Signpost(sf::Vector2f(650, 300));
	signposts[31] = new Signpost(sf::Vector2f(650, 450));
	signposts[32] = new Signpost(sf::Vector2f(650, 600));
	signposts[33] = new Signpost(sf::Vector2f(650, 750));

	//ghost start section in the middle
	signposts[34] = new Signpost(sf::Vector2f(350, 350));
	signposts[35] = new Signpost(sf::Vector2f(350, 450));
}

void Game::InitSignpostDirections()
{
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
	signposts[7]->SetDirection(Direction::Right);

	signposts[8]->SetDirection(Direction::Up);
	signposts[8]->SetDirection(Direction::Down);
	signposts[8]->SetDirection(Direction::Left);

	signposts[9]->SetDirection(Direction::Up);
	signposts[9]->SetDirection(Direction::Right);
	signposts[9]->SetDirection(Direction::Down);

	signposts[10]->SetDirection(Direction::Up);
	signposts[10]->SetDirection(Direction::Left);
	signposts[10]->SetDirection(Direction::Down);

	signposts[11]->SetDirection(Direction::Up);
	signposts[11]->SetDirection(Direction::Right);
	signposts[11]->SetDirection(Direction::Down);

	signposts[12]->SetDirection(Direction::Up);
	signposts[12]->SetDirection(Direction::Right);
	signposts[12]->SetDirection(Direction::Left);

	signposts[13]->SetDirection(Direction::Left);
	signposts[13]->SetDirection(Direction::Down);

	signposts[14]->SetDirection(Direction::Up);
	signposts[14]->SetDirection(Direction::Right);
	signposts[14]->SetDirection(Direction::Left);

	signposts[15]->SetDirection(Direction::Down);
	signposts[15]->SetDirection(Direction::Left);

	signposts[16]->SetDirection(Direction::Up);
	signposts[16]->SetDirection(Direction::Right);
	signposts[16]->SetDirection(Direction::Left);

	signposts[17]->SetDirection(Direction::Right);
	signposts[17]->SetDirection(Direction::Down);

	signposts[18]->SetDirection(Direction::Up);
	signposts[18]->SetDirection(Direction::Right);
	signposts[18]->SetDirection(Direction::Left);

	signposts[19]->SetDirection(Direction::Down);
	signposts[19]->SetDirection(Direction::Right);

	signposts[20]->SetDirection(Direction::Up);
	signposts[20]->SetDirection(Direction::Right);
	signposts[20]->SetDirection(Direction::Left);

	signposts[21]->SetDirection(Direction::Left);
	signposts[21]->SetDirection(Direction::Right);
	signposts[21]->SetDirection(Direction::Down);

	signposts[22]->SetDirection(Direction::Up);
	signposts[22]->SetDirection(Direction::Right);
	signposts[22]->SetDirection(Direction::Down);

	signposts[23]->SetDirection(Direction::Up);
	signposts[23]->SetDirection(Direction::Down);
	signposts[23]->SetDirection(Direction::Left);

	signposts[24]->SetDirection(Direction::Up);
	signposts[24]->SetDirection(Direction::Down);
	signposts[24]->SetDirection(Direction::Right);

	signposts[25]->SetDirection(Direction::Up);
	signposts[25]->SetDirection(Direction::Left);
	signposts[25]->SetDirection(Direction::Down);

	signposts[26]->SetDirection(Direction::Up);
	signposts[26]->SetDirection(Direction::Right);
	signposts[26]->SetDirection(Direction::Down);

	signposts[27]->SetDirection(Direction::Up);
	signposts[27]->SetDirection(Direction::Left);
	signposts[27]->SetDirection(Direction::Down);

	signposts[28]->SetDirection(Direction::Up);
	signposts[28]->SetDirection(Direction::Right);
	signposts[28]->SetDirection(Direction::Left);

	signposts[29]->SetDirection(Direction::Left);
	signposts[29]->SetDirection(Direction::Down);

	signposts[30]->SetDirection(Direction::Up);
	signposts[30]->SetDirection(Direction::Left);
	signposts[30]->SetDirection(Direction::Down);

	signposts[31]->SetDirection(Direction::Up);
	signposts[31]->SetDirection(Direction::Right);
	signposts[31]->SetDirection(Direction::Down);
	signposts[31]->SetDirection(Direction::Left);

	signposts[32]->SetDirection(Direction::Up);
	signposts[32]->SetDirection(Direction::Left);
	signposts[32]->SetDirection(Direction::Down);

	signposts[33]->SetDirection(Direction::Up);
	signposts[33]->SetDirection(Direction::Left);

	signposts[34]->SetDirection(Direction::Right);
	signposts[34]->SetDirection(Direction::Left);

	signposts[35]->SetDirection(Direction::Up);
}

void Game::InitDots()
{
	// left left side from top down
	//dots[0] = Dot(sf::Vector2f(75, 175));
	dots[0] = Dot(sf::Vector2f(75, 225));
	dots[1] = Dot(sf::Vector2f(75, 275));
	dots[2] = Dot(sf::Vector2f(75, 325));
	dots[3] = Dot(sf::Vector2f(75, 375));
	dots[4] = Dot(sf::Vector2f(75, 425));
	dots[5] = Dot(sf::Vector2f(75, 475));
	dots[6] = Dot(sf::Vector2f(75, 525));
	dots[7] = Dot(sf::Vector2f(75, 575));
	dots[8] = Dot(sf::Vector2f(75, 625));
	dots[9] = Dot(sf::Vector2f(75, 675));
	dots[10] = Dot(sf::Vector2f(75, 725));
	//dots[12] = Dot(sf::Vector2f(75, 775));

	// left middle side from top down
	dots[11] = Dot(sf::Vector2f(225, 175));
	dots[12] = Dot(sf::Vector2f(225, 225));
	dots[13] = Dot(sf::Vector2f(225, 275));
	dots[14] = Dot(sf::Vector2f(225, 325));
	dots[15] = Dot(sf::Vector2f(225, 375));
	dots[16] = Dot(sf::Vector2f(225, 425));
	dots[17] = Dot(sf::Vector2f(225, 475));
	dots[18] = Dot(sf::Vector2f(225, 525));
	dots[19] = Dot(sf::Vector2f(225, 575));
	dots[20] = Dot(sf::Vector2f(225, 625));
	dots[21] = Dot(sf::Vector2f(225, 675));
	dots[22] = Dot(sf::Vector2f(225, 725));
	dots[23] = Dot(sf::Vector2f(225, 775));

	// left right side from top down
	dots[24] = Dot(sf::Vector2f(325, 175));
	dots[25] = Dot(sf::Vector2f(325, 225));
	dots[26] = Dot(sf::Vector2f(325, 275));
	dots[27] = Dot(sf::Vector2f(325, 325));
	dots[28] = Dot(sf::Vector2f(325, 375));
	dots[29] = Dot(sf::Vector2f(325, 575));
	dots[30] = Dot(sf::Vector2f(325, 675));
	dots[31] = Dot(sf::Vector2f(325, 725));
	dots[32] = Dot(sf::Vector2f(325, 775));

	// right left side from top down
	dots[33] = Dot(sf::Vector2f(425, 175));
	dots[34] = Dot(sf::Vector2f(425, 225));
	dots[35] = Dot(sf::Vector2f(425, 275));
	dots[36] = Dot(sf::Vector2f(425, 325));
	dots[37] = Dot(sf::Vector2f(425, 375));
	dots[38] = Dot(sf::Vector2f(425, 575));
	dots[39] = Dot(sf::Vector2f(425, 675));
	dots[40] = Dot(sf::Vector2f(425, 725));
	dots[41] = Dot(sf::Vector2f(425, 775));

	// right middle side from top down
	dots[42] = Dot(sf::Vector2f(525, 175));
	dots[43] = Dot(sf::Vector2f(525, 225));
	dots[44] = Dot(sf::Vector2f(525, 275));
	dots[45] = Dot(sf::Vector2f(525, 325));
	dots[46] = Dot(sf::Vector2f(525, 375));
	dots[47] = Dot(sf::Vector2f(525, 425));
	dots[48] = Dot(sf::Vector2f(525, 475));
	dots[49] = Dot(sf::Vector2f(525, 525));
	dots[50] = Dot(sf::Vector2f(525, 575));
	dots[51] = Dot(sf::Vector2f(525, 625));
	dots[52] = Dot(sf::Vector2f(525, 675));
	dots[53] = Dot(sf::Vector2f(525, 725));
	dots[54] = Dot(sf::Vector2f(525, 775));

	// right right side from top down
	//dots[55] = Dot(sf::Vector2f(675, 175));
	dots[55] = Dot(sf::Vector2f(675, 225));
	dots[56] = Dot(sf::Vector2f(675, 275));
	dots[57] = Dot(sf::Vector2f(675, 325));
	dots[58] = Dot(sf::Vector2f(675, 375));
	dots[59] = Dot(sf::Vector2f(675, 425));
	dots[60] = Dot(sf::Vector2f(675, 475));
	dots[61] = Dot(sf::Vector2f(675, 525));
	dots[62] = Dot(sf::Vector2f(675, 575));
	dots[63] = Dot(sf::Vector2f(675, 625));
	dots[64] = Dot(sf::Vector2f(675, 675));
	dots[65] = Dot(sf::Vector2f(675, 725));
	//dots[67] = Dot(sf::Vector2f(675, 775));

	// left to right from top down
	dots[66] = Dot(sf::Vector2f(125, 175));
	dots[67] = Dot(sf::Vector2f(175, 175));
	dots[68] = Dot(sf::Vector2f(275, 175));
	dots[69] = Dot(sf::Vector2f(475, 175));
	dots[70] = Dot(sf::Vector2f(575, 175));
	dots[71] = Dot(sf::Vector2f(625, 175));

	dots[72] = Dot(sf::Vector2f(125, 325));
	dots[73] = Dot(sf::Vector2f(175, 325));
	dots[74] = Dot(sf::Vector2f(575, 325));
	dots[75] = Dot(sf::Vector2f(625, 325));

	dots[76] = Dot(sf::Vector2f(275, 375));
	dots[77] = Dot(sf::Vector2f(375, 375));
	dots[78] = Dot(sf::Vector2f(475, 375));

	dots[79] = Dot(sf::Vector2f(125, 475));
	dots[80] = Dot(sf::Vector2f(175, 475));
	dots[81] = Dot(sf::Vector2f(575, 475));
	dots[82] = Dot(sf::Vector2f(625, 475));

	dots[83] = Dot(sf::Vector2f(275, 575));
	dots[84] = Dot(sf::Vector2f(475, 575));

	dots[85] = Dot(sf::Vector2f(125, 625));
	dots[86] = Dot(sf::Vector2f(175, 625));
	dots[87] = Dot(sf::Vector2f(575, 625));
	dots[88] = Dot(sf::Vector2f(625, 625));

	dots[89] = Dot(sf::Vector2f(275, 675));
	dots[90] = Dot(sf::Vector2f(475, 675));

	dots[91] = Dot(sf::Vector2f(125, 775));
	dots[92] = Dot(sf::Vector2f(175, 775));
	dots[93] = Dot(sf::Vector2f(275, 775));
	dots[94] = Dot(sf::Vector2f(375, 775));
	dots[95] = Dot(sf::Vector2f(475, 775));
	dots[96] = Dot(sf::Vector2f(575, 775));
	dots[97] = Dot(sf::Vector2f(625, 775));
}

void Game::InitPowerPellets()
{
	powerPellets[0] = PowerPellet(sf::Vector2f(70, 170));
	powerPellets[1] = PowerPellet(sf::Vector2f(670, 170));
	powerPellets[2] = PowerPellet(sf::Vector2f(70, 770));
	powerPellets[3] = PowerPellet(sf::Vector2f(670, 770));
}
