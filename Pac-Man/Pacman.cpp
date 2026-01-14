#include "Pacman.hpp"

Pacman::Pacman() : currentFrame(0), directionChanged(false), isColliding(false), speedX(100.0f), speedY(0.0f), direction(sf::Vector2f(0, 0)),
					nextDirectionDown(sf::Vector2f(0,0)), nextDirectionUp(sf::Vector2f(0, 0)), 
					nextDirectionRight(sf::Vector2f(0, 0)), nextDirectionLeft(sf::Vector2f(0, 0))
{
	if (!pacmanTexture.loadFromFile("./assets/pacman.png"))
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

	collisionRect = new Collision(pacman.getPosition() + sf::Vector2f(-24, -24), 48, 48);
	collisionRect->SetColor(sf::Color::Transparent);

	collisionDetectionRects.resize(4);
	isCollisionDetectionRectColliding.resize(4);

	collisionDetectionRects[0] = new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(50, 0), Direction::Left);
	collisionDetectionRects[1] = new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(0, 50), Direction::Up);
	collisionDetectionRects[2] = new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(0, -50), Direction::Down);
	collisionDetectionRects[3] = new CollisionDetectionRect(pacman.getPosition() + sf::Vector2f(-50, 0), Direction::Right);

	for (auto& rect : collisionDetectionRects)
	{
		rect->SetColor(sf::Color::Blue);
	}
}

Pacman::~Pacman()
{
}

void Pacman::Events(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isCollisionDetectionRectColliding[0])
	{
		direction = Direction::Left;

		//speedX = 0.0f;
		SetSpeedX();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isCollisionDetectionRectColliding[0])
	{
		nextDirectionLeft = Direction::Left;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isCollisionDetectionRectColliding[3])
	{
		direction = Direction::Right;

		//speedX = 0.0f;
		SetSpeedX();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isCollisionDetectionRectColliding[3])
	{
		nextDirectionRight = Direction::Right;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isCollisionDetectionRectColliding[1])
	{
		direction = Direction::Up;

		//speedY = 0.0f;
		SetSpeedY();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isCollisionDetectionRectColliding[1])
	{
		nextDirectionUp = Direction::Up;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isCollisionDetectionRectColliding[2])
	{
		direction = Direction::Down;
		
		//speedY = 0.0f;
		SetSpeedY();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && isCollisionDetectionRectColliding[2])
	{
		nextDirectionDown = Direction::Down;
	}
}

void Pacman::Render(sf::RenderWindow& window)
{
	window.draw(pacman);
	//collisionRect->Render(window);

	//for (auto& rect : collisionDetectionRects)
	//{
	//	rect->Render(window);
	//}
}

void Pacman::Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects)
{
	if (!isCollisionDetectionRectColliding[0] && nextDirectionLeft != sf::Vector2f(0, 0))
	{
		direction = nextDirectionLeft;
		SetSpeedX();
		nextDirectionLeft = sf::Vector2f(0, 0);
	}

	if (!isCollisionDetectionRectColliding[1] && nextDirectionUp != sf::Vector2f(0, 0))
	{
		direction = nextDirectionUp;
		SetSpeedY();
		nextDirectionUp = sf::Vector2f(0, 0);
	}

	if (!isCollisionDetectionRectColliding[2] && nextDirectionDown != sf::Vector2f(0, 0))
	{
		direction = nextDirectionDown;
		SetSpeedY();
		nextDirectionDown = sf::Vector2f(0, 0);
	}

	if (!isCollisionDetectionRectColliding[3] && nextDirectionRight != sf::Vector2f(0, 0))
	{
		direction = nextDirectionRight;
		SetSpeedX();
		nextDirectionRight = sf::Vector2f(0, 0);
	}

	Animation(direction);
	OutOfBounds();

	velocity.x = direction.x * speedX;
	velocity.y = direction.y * speedY;

	velocity *= deltaTime.asSeconds();
	pacman.move(velocity);
	collisionRect->collision.move(velocity);

	collisionDetectionRects[0]->Update(deltaTime, pacman.getPosition() - sf::Vector2f(50, 0));
	collisionDetectionRects[1]->Update(deltaTime, pacman.getPosition() - sf::Vector2f(0, 50));
	collisionDetectionRects[2]->Update(deltaTime, pacman.getPosition() - sf::Vector2f(0, -50));
	collisionDetectionRects[3]->Update(deltaTime, pacman.getPosition() - sf::Vector2f(-50, 0));

	for (int i = 0; i < collisionDetectionRects.size(); i++)
	{
		if (collisionDetectionRects[i]->CheckCollisionWithWallColored(collisionRects))
		{
			isCollisionDetectionRectColliding[i] = true;
		}
		else
		{
			isCollisionDetectionRectColliding[i] = false;
		}
	}

	if (direction == collisionDetectionRects[0]->direction && isCollisionDetectionRectColliding[0])
	{
		CheckCollisionWithWallColored(collisionRects);
	}
	else if (direction == collisionDetectionRects[3]->direction && isCollisionDetectionRectColliding[3])
	{
		CheckCollisionWithWallColored(collisionRects);
	}
	else if (direction == collisionDetectionRects[1]->direction && isCollisionDetectionRectColliding[1])
	{
		CheckCollisionWithWallColored(collisionRects);
	}
	else if (direction == collisionDetectionRects[2]->direction && isCollisionDetectionRectColliding[2])
	{
		CheckCollisionWithWallColored(collisionRects);
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
			currentFrame = (currentFrame + 1) % 4; // N�chster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame]);
		}
		else if(direction == sf::Vector2f(1, 0))
		{
			pacman.setScale(1.0, 1.0);
			currentFrame = (currentFrame + 1) % 4; // N�chster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame]);
		}
		else if (direction == sf::Vector2f(0, -1))
		{
			pacman.setScale(1.0, 1.0);
			currentFrame = (currentFrame + 1) % 4; // N�chster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame + 4]);
		}
		else if (direction == sf::Vector2f(0, 1))
		{
			pacman.setScale(1.0, -1.0);
			currentFrame = (currentFrame + 1) % 4; // N�chster Frame
			pacman.setTextureRect(pacmanFrames[currentFrame + 4]);
		}
		lastUpdateTime = time; // Timer zur�cksetzen
		clock.restart();
	}
}

void Pacman::CheckCollisionWithWallColored(const std::vector<Collision*>& collisionRects)
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

void Pacman::SetSpeedX()
{
	speedX = 300.0f;
	speedY = 0.0f;
}

void Pacman::SetSpeedY()
{
	speedY = 300.0f;
	speedX = 0.0f;
}

void Pacman::OutOfBounds()
{
	if (pacman.getPosition().x + pacman.getGlobalBounds().width < 0)
	{
		pacman.setPosition(800, pacman.getPosition().y);
	}
	else if (pacman.getPosition().x - pacman.getGlobalBounds().width > 800)
	{
		pacman.setPosition(0, pacman.getPosition().y);
	}
}

void Pacman::Reset()
{
	pacman.setPosition(375, 575);
	collisionRect->SetPosition(pacman.getPosition() - sf::Vector2f(24.5, 24.5));
	collisionDetectionRects[0]->SetPosition(pacman.getPosition() + sf::Vector2f(50, 0));
	collisionDetectionRects[1]->SetPosition(pacman.getPosition() + sf::Vector2f(0, 50));
	collisionDetectionRects[2]->SetPosition(pacman.getPosition() + sf::Vector2f(0, -50));
	collisionDetectionRects[3]->SetPosition(pacman.getPosition() + sf::Vector2f(-50, 0));
	direction = sf::Vector2f(-1, 0);
	SetSpeedY();
}

const sf::Texture* Pacman::GetTexture()
{
	return pacman.getTexture();
}

bool Pacman::CollisionWith(Ghost& ghost)
{
	if (pacman.getGlobalBounds().intersects(ghost.GetSprite().getGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Pacman::CollisionWith(Dot& dot)
{
	if (pacman.getGlobalBounds().intersects(dot.GetGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Pacman::CollisionWith(PowerPellet& powerPellet)
{
	if (pacman.getGlobalBounds().intersects(powerPellet.GetGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Pacman::CollisionWith(Fruit& fruit)
{
	if (pacman.getGlobalBounds().intersects(fruit.GetGlobalBounds()))
	{
		return true;
	}
	return false;
}


