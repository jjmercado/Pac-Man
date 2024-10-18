#include "Ghost.hpp"

// TODOS 
// - Implement Collision Detection Rects for Ghosts
// - Implement Ghost Movement
// - Implement different start times for Ghosts

Ghost::Ghost()
{
}

Ghost::Ghost(sf::Color color, sf::Vector2f startPos, float startTime, sf::Vector2f startDirection) : currentFrame(0), startTime(startTime), eatable(false), color(color),
			startDirection(startDirection), startPosition(startPos), points(200)
{
	if (!ghostTexture.loadFromFile("..\\Ghost.png"))
	{
		std::cout << "Error loading ghost.png" << std::endl;
	}
	else
	{
		ghost.setColor(color);
		ghost.setTextureRect(sf::IntRect(0, 0, 50, 50));
		ghost.setTexture(ghostTexture);
		ghost.setPosition(startPos);
	}

	if (!eyesBackgroundTexture.loadFromFile("..\\eyesBack.png"))
	{
		std::cout << "Error loading eyesbackground.png" << std::endl;
	}
	else
	{
		eyesBackground.setTexture(eyesBackgroundTexture);
		eyesBackground.setPosition(ghost.getPosition().x + 15, ghost.getPosition().y + 15);
	}

	if (!pupilsTexture.loadFromFile("..\\pupils.png"))
	{
		std::cout << "Error loading pupils.png" << std::endl;
	}
	else
	{
		pupils.setTexture(pupilsTexture);
		pupils.setPosition(eyesBackground.getPosition());
	}

	speedX = 100.0f;
	speedY = 100.0f;
	direction = startDirection;
}

Ghost::~Ghost()
{
}

void Ghost::Render(sf::RenderWindow& window)
{
	if (!eatable)
	{
		ghost.setColor(color);
	}
	else
	{
		ghost.setColor(sf::Color::Blue);
	}

	window.draw(ghost);
	window.draw(eyesBackground);
	window.draw(pupils);
}

void Ghost::Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects)
{
	if (SetStartTime(startTime))
	{
		velocity.x = direction.x * speedX;
		velocity.y = direction.y * speedY;

		velocity *= deltaTime.asSeconds();
		ghost.move(velocity);
		eyesBackground.move(velocity);
		pupils.move(velocity);

		Animation();
		OutOfBounds();
	}

	if (eatable)
	{
		ResetEatableState(10.0f);
	}
	else
	{
		eatableClock.restart();
	}
}

void Ghost::Animation()
{
	sf::Time time = animationClock.getElapsedTime();
	float delay = 0.1f; // Zeit in Sekunden zwischen den Frames
	sf::Time lastUpdateTime = sf::Time::Zero; // Zeit des letzten Frame-Wechsels

	std::vector<sf::IntRect> ghostFrames;
	ghostFrames.push_back(sf::IntRect(0, 0, 50, 50));
	ghostFrames.push_back(sf::IntRect(50, 0, 50, 50));
	ghostFrames.push_back(sf::IntRect(100, 0, 50, 50));

	if (time - lastUpdateTime >= sf::seconds(delay))
	{
		currentFrame = (currentFrame + 1) % ghostFrames.size(); // Nächster Frame
		ghost.setTextureRect(ghostFrames[currentFrame]);
		lastUpdateTime = time; // Timer zurücksetzen
		animationClock.restart();
	}
}

void Ghost::SetDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

sf::Sprite Ghost::GetSprite()
{
	return ghost;
}

bool Ghost::SetStartTime(float startTime)
{
	// Setzt die Startzeit für den Ghost
	// startTime = 0 -> Ghost bewegt sich sofort
	// startTime = 5 -> Ghost bewegt sich nach 5 Sekunden
	// startTime = 10 -> Ghost bewegt sich nach 10 Sekunden
	// usw.
	sf::Time time = startClock.getElapsedTime();
	if (time.asSeconds() >= startTime)
	{
		return true;
	}
	return false;
}

void Ghost::ResetEatableState(float resetTime)
{
	sf::Time time = eatableClock.getElapsedTime();
	if (time.asSeconds() >= resetTime)
	{
		eatable = false;
	}
}

void Ghost::OutOfBounds()
{
	if (ghost.getPosition().x < 0 && eyesBackground.getPosition().x < 0 && pupils.getPosition().x < 0)
	{
		ghost.setPosition(800, ghost.getPosition().y);
		eyesBackground.setPosition(815, eyesBackground.getPosition().y);
		pupils.setPosition(815, pupils.getPosition().y);
	}
	else if (ghost.getPosition().x > 800 && eyesBackground.getPosition().x > 800 && pupils.getPosition().x > 800)
	{
		ghost.setPosition(0, ghost.getPosition().y);
		eyesBackground.setPosition(15, eyesBackground.getPosition().y);
		pupils.setPosition(15, pupils.getPosition().y);
	}
}

void Ghost::Reset()
{
	ghost.setPosition(startPosition);
	eyesBackground.setPosition(ghost.getPosition().x + 15, ghost.getPosition().y + 15);
	pupils.setPosition(eyesBackground.getPosition());
	this->direction = startDirection;
	startClock.restart();
	eatable = false;
}

void Ghost::SetEatable(bool value)
{
	eatable = value;
}

bool Ghost::GetEatable()
{
	return eatable;
}

int Ghost::GetPoints()
{
	return points;
}
