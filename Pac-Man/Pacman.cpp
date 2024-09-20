#include "Pacman.hpp"

Pacman::Pacman() : currentFrame(0), isColliding(false), directionChanged(false)
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
	speed = 100.0f;
	direction = sf::Vector2f(0, 0);

	collision.setOrigin(25, 18);
	collision.setSize(sf::Vector2f(2, 36));
	collision.setPosition(pacman.getPosition());
	collision.setFillColor(sf::Color::Blue);
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
	window.draw(collision);
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
	collision.move(velocity);

	if (direction == sf::Vector2f(1, 0))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(50, 0));
		collision.setSize(sf::Vector2f(2, 36));
		collision.setOrigin(25, 18);
	}
	else if (direction == sf::Vector2f(-1, 0))
	{
		collision.setPosition(pacman.getPosition());
		collision.setSize(sf::Vector2f(2, 36));
		collision.setOrigin(25, 18);
	}
	else if (direction == sf::Vector2f(0, 1))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(0, 50));
		collision.setSize(sf::Vector2f(36, 2));
		collision.setOrigin(18, 25);
	}
	else if (direction == sf::Vector2f(0, -1))
	{
		collision.setPosition(pacman.getPosition());
		collision.setSize(sf::Vector2f(36, 2));
		collision.setOrigin(18, 25);
	}

	if (isColliding && direction == sf::Vector2f(1, 0))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(50 - 10, 0));
	}
	else if(isColliding && direction == sf::Vector2f(-1, 0))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(10, 0));
	}
	else if (isColliding && direction == sf::Vector2f(0, 1))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(0, 50 - 10));
	}
	else if (isColliding && direction == sf::Vector2f(0, -1))
	{
		collision.setPosition(pacman.getPosition() + sf::Vector2f(0, 10));
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
