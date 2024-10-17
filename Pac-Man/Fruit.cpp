#include "Fruit.hpp"

Fruit::Fruit()
{
}

Fruit::Fruit(sf::IntRect rect, int points) : currentState(State::INACTIVE)
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
	canGetEat = false;
	clockTime = 5.0f;
}

Fruit::~Fruit()
{
}

void Fruit::Render(sf::RenderWindow& window)
{
	if (currentState == State::ACTIVE)
	{
		window.draw(sprite);
	}
}

void Fruit::Update(sf::Time deltaTime)
{
	switch (currentState)
	{
		case State::ACTIVE:
		{
			Activate();
			break;
		}
		case State::INACTIVE:
		{
			Deactivate();
			break;
		}
		default:
		{

			break;
		}
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

bool Fruit::GetState()
{
	return canGetEat;
}

void Fruit::SetState(State state)
{
	currentState = state;
}

void Fruit::SetStartTime()
{
	// Setzt die Startzeit für den Ghost
	// startTime = 0 -> Ghost bewegt sich sofort
	// startTime = 5 -> Ghost bewegt sich nach 5 Sekunden
	// startTime = 10 -> Ghost bewegt sich nach 10 Sekunden
	// usw.
	sf::Time time = startClock.getElapsedTime();
	if (time.asSeconds() >= clockTime)
	{
		Deactivate();
	}
}

void Fruit::Activate()
{
	currentState = State::ACTIVE;
	SetStartTime();
}

void Fruit::Deactivate()
{
	startClock.restart();
	currentState = State::INACTIVE;
}
