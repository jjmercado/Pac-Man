#include "Pacman.hpp"

Pacman::Pacman() : currentFrame(0), isColliding(false), directionChanged(false)
{
	if (!pacmanTexture.loadFromFile("..\\pacman.png"))
	{
		std::cout << "Error loading pacman.png" << std::endl;
	}
	else 
	{
		pacmanTexture.setSmooth(true);
		pacman.setTextureRect(sf::IntRect(0, 0, 50, 50));
		pacman.setTexture(pacmanTexture);
		pacman.setPosition(375, 575);
		pacman.setOrigin(25, 25);
		pacman.setScale(-1.0, -1.0);
	}

	speed = 100.0f;
	direction = sf::Vector2f(0, 0);

	leftCollisionRect.setOrigin(25, 25);
	leftCollisionRect.setSize(sf::Vector2f(50, 50));
	leftCollisionRect.setPosition(pacman.getPosition() - sf::Vector2f(50,0));
	leftCollisionRect.setFillColor(sf::Color::Blue);

	rightCollisionRect.setOrigin(25, 25);
	rightCollisionRect.setSize(sf::Vector2f(50, 50));
	rightCollisionRect.setPosition(pacman.getPosition() + sf::Vector2f(50, 0));
	rightCollisionRect.setFillColor(sf::Color::Blue);

	upCollisionRect.setOrigin(25, 25);
	upCollisionRect.setSize(sf::Vector2f(50, 50));
	upCollisionRect.setPosition(pacman.getPosition() - sf::Vector2f(0, 50));
	upCollisionRect.setFillColor(sf::Color::Blue);

	downCollisionRect.setOrigin(25, 25);
	downCollisionRect.setSize(sf::Vector2f(50, 50));
	downCollisionRect.setPosition(pacman.getPosition() + sf::Vector2f(0, 50));
	downCollisionRect.setFillColor(sf::Color::Blue);

	collisionDetectionRects.push_back(&leftCollisionRect);
	collisionDetectionRects.push_back(&rightCollisionRect);
	collisionDetectionRects.push_back(&upCollisionRect);
	collisionDetectionRects.push_back(&downCollisionRect);
}

Pacman::~Pacman()
{
}

void Pacman::Events(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = sf::Vector2f(-1, 0);
		directionChanged = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = sf::Vector2f(1, 0);
		directionChanged = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = sf::Vector2f(0, -1);
		directionChanged = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = sf::Vector2f(0, 1);
		directionChanged = true;
	}
}

void Pacman::Render(sf::RenderWindow& window)
{
	window.draw(pacman);
	for (auto& rect : collisionDetectionRects)
	{
		window.draw(*rect);
	}
}

void Pacman::Update(sf::Time deltaTime)
{
	Animation(direction);

	if (isColliding)
	{
		if (!directionChanged)
		{
			speed = 0.0f;
		}
		else
		{
			speed = 100.0f;
			directionChanged = false;
			isColliding = false;
		}
	}

	velocity = direction * speed * deltaTime.asSeconds();
	pacman.move(velocity);

	for (auto& rect : collisionDetectionRects)
	{
		rect->move(velocity);
	}
}

void Pacman::Animation(sf::Vector2f direction)
{
	sf::Time time = clock.getElapsedTime();
	float delay = 0.1f; // Zeit in Sekunden zwischen den Frames
	sf::Time lastUpdateTime = sf::Time::Zero; // Zeit des letzten Frame-Wechsels

	std::vector<sf::IntRect> pacmanFrames;
	pacmanFrames.push_back(sf::IntRect(0, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(50, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(100, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(150, 0, 50, 50));
	pacmanFrames.push_back(sf::IntRect(0, 50, 50, 50));
	pacmanFrames.push_back(sf::IntRect(50, 50, 50, 50));
	pacmanFrames.push_back(sf::IntRect(100, 50, 50, 50));
	pacmanFrames.push_back(sf::IntRect(150, 50, 50, 50));


	if (time - lastUpdateTime >= sf::seconds(delay))
	{
		if (direction == sf::Vector2f(-1, 0))
		{
			pacman.setScale(-1.0, 1.0);
			currentFrame = (currentFrame + 1) % 4; // Nächster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame]);
		}
		else if(direction == sf::Vector2f(1, 0))
		{
			pacman.setScale(1.0, 1.0);
			currentFrame = (currentFrame + 1) % 4; // Nächster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame]);
		}
		else if (direction == sf::Vector2f(0, -1))
		{
			pacman.setScale(1.0, 1.0);
			currentFrame = (currentFrame + 1) % 4; // Nächster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame + 4]);
		}
		else if (direction == sf::Vector2f(0, 1))
		{
			pacman.setScale(1.0, -1.0);
			currentFrame = (currentFrame + 1) % 4; // Nächster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame + 4]);
		}
		lastUpdateTime = time; // Timer zurücksetzen
		clock.restart();
	}
}

void Pacman::IsCollidingWithWall(std::vector<Collision*> collisionRects)
{
	for (auto& rect : collisionDetectionRects)
	{
		bool isColliding = false;
		for (auto& wall : collisionRects)
		{
			if (rect->getGlobalBounds().intersects(wall->collision.getGlobalBounds()))
			{
				isColliding = true;
				break; // Keine weitere Prüfung erforderlich, da eine Kollision gefunden wurde
			}
		}
		if (isColliding)
		{
			rect->setFillColor(sf::Color::White);
		}
		else
		{
			rect->setFillColor(sf::Color::Blue);
		}
	}
}