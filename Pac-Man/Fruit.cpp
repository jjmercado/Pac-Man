#include "Fruit.hpp"

Fruit::Fruit()
{
}

Fruit::Fruit(sf::IntRect rect, int points)
{
	if (!texture.loadFromFile("..\\fruits.png", rect))
	{
		std::cout << "Failed loading fruit" << std::endl;
	}
	else
	{
		sprite.setTexture(texture);
		sprite.setPosition(350, 550);
	}

	this->points = points;
	isActive = false;
	clockTime = 5.0f;
}

Fruit::~Fruit()
{
}

void Fruit::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Fruit::Update(sf::Time deltaTime)
{
	if (isActive)
	{
		if (SetStartTime())
		{
			isActive = false;
		}
	}
	else
	{
		startClock.restart();
	}
}

sf::FloatRect Fruit::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Fruit::Remove()
{
	sprite.setColor(sf::Color::Transparent);
	points = 0;
}

int Fruit::GetPoints()
{
	return points;
}

bool Fruit::SetStartTime()
{
	// Setzt die Startzeit für den Ghost
	// startTime = 0 -> Ghost bewegt sich sofort
	// startTime = 5 -> Ghost bewegt sich nach 5 Sekunden
	// startTime = 10 -> Ghost bewegt sich nach 10 Sekunden
	// usw.
	sf::Time time = startClock.getElapsedTime();
	if (time.asSeconds() >= clockTime)
	{
		return true;
	}
	return false;
}
