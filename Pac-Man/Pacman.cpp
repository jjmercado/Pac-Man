#include "Pacman.hpp"

Pacman::Pacman() : currentFrame(0), directionChanged(false)
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

	collisionDetectionRects.push_back(new CollisionDetectionRect(pacman.getPosition() - sf::Vector2f(50, 0), sf::Vector2f(-1, 0)));
	collisionDetectionRects.push_back(new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(50, 0), sf::Vector2f(1, 0)));
	collisionDetectionRects.push_back(new CollisionDetectionRect(pacman.getPosition() - sf::Vector2f(0, 50), sf::Vector2f(0, -1)));
	collisionDetectionRects.push_back(new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(0, 50), sf::Vector2f(0, 1)));
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
	for (auto& collisionRect : collisionDetectionRects)
	{
		collisionRect->Render(window);
	}
}

void Pacman::Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects)
{
	Animation(direction);

	CheckCollisionWithWall(collisionRects);
	ReactToCollision();

	velocity = direction * speed * deltaTime.asSeconds();
	pacman.move(velocity);

	for (auto& collisionRect : collisionDetectionRects)
	{
		collisionRect->Update(deltaTime, velocity);
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

void Pacman::CheckCollisionWithWall(const std::vector<Collision*>& collisionRects)
{
	for (auto& collisionRect : collisionDetectionRects)
	{
		if (collisionRect->IsColliding(collisionRects))
		{
			ReactToCollision();
		}
	}
}

void Pacman::ReactToCollision()
{
	if (collisionDetectionRects[0]->GetIsColliding() && direction == collisionDetectionRects[0]->direction)
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
}