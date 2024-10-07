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

	speedX = 100.0f;
	speedY = 100.0f;
	direction = sf::Vector2f(0, 0);
	collisionRect = new Collision(pacman.getPosition() - sf::Vector2f(24.5, 24.5), 49, 49);
}

Pacman::~Pacman()
{
}

void Pacman::Events(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = sf::Vector2f(-1, 0);
		SetVelocityX();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = sf::Vector2f(1, 0);
		SetVelocityX();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = sf::Vector2f(0, -1);
		SetVelocityY();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = sf::Vector2f(0, 1);
		SetVelocityY();
	}
}

void Pacman::Render(sf::RenderWindow& window)
{
	window.draw(pacman);
	collisionRect->Render(window);
}

void Pacman::Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects)
{
	Animation(direction);

	CheckCollisionWithWall(collisionRects);

	velocity.x = direction.x * speedX;
	velocity.y = direction.y * speedY;

	velocity *= deltaTime.asSeconds();
	pacman.move(velocity);
	collisionRect->collision.move(velocity);
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
	for (auto& wall : collisionRects)
	{
		if (collisionRect->collision.getGlobalBounds().left + velocity.x < wall->collision.getGlobalBounds().left + wall->collision.getGlobalBounds().width &&
			collisionRect->collision.getGlobalBounds().left + collisionRect->collision.getGlobalBounds().width + velocity.x > wall->collision.getGlobalBounds().left &&
			collisionRect->collision.getGlobalBounds().top + collisionRect->collision.getGlobalBounds().height + velocity.y > wall->collision.getGlobalBounds().top &&
			collisionRect->collision.getGlobalBounds().top + velocity.y < wall->collision.getGlobalBounds().top + wall->collision.getGlobalBounds().height)
		{
			collisionRect->collision.setColor(sf::Color::White);

			ReactToCollision();
			break;
		}
		else
		{
			collisionRect->collision.setColor(sf::Color::Transparent);
		}
	}
}

void Pacman::ReactToCollision()
{
	speedX = 0.0f;
	speedY = 0.0f;
}

float Pacman::SetVelocityX()
{
	speedX = 100.0f;
	velocity.y = 0;
	return velocity.x;
}

float Pacman::SetVelocityY()
{
	speedY = 100.0f;
	velocity.x = 0;
	return velocity.y;
}
