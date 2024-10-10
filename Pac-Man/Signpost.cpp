#include "Signpost.hpp"

Signpost::Signpost(sf::Vector2f startPos)
{
	std::srand(std::time(0));
	image.create(48, 48, sf::Color::White);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(startPos);
	sprite.setOrigin(-1, -1);
}

Signpost::~Signpost()
{
}

void Signpost::GenerateRandomNumber()
{
	randomNumber = rand() % directions.size();
}

void Signpost::Update(sf::Time deltaTime, Ghost& ghost)
{
	SetObjectDirection(ghost);
}

void Signpost::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Signpost::SetColor(sf::Color color)
{
	sprite.setColor(color);
}

void Signpost::SetDirection(sf::Vector2f direction)
{
	directions.push_back(direction);
}

void Signpost::SetObjectDirection(Ghost& ghost)
{
	if (sprite.getGlobalBounds().left > ghost.GetSprite().getGlobalBounds().left &&
		sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < ghost.GetSprite().getGlobalBounds().left + ghost.GetSprite().getGlobalBounds().width &&
		sprite.getGlobalBounds().top > ghost.GetSprite().getGlobalBounds().top &&
		sprite.getGlobalBounds().top + sprite.getGlobalBounds().height < ghost.GetSprite().getGlobalBounds().top + ghost.GetSprite().getGlobalBounds().height)
	{
		randomDirection = directions[randomNumber];
		ghost.SetDirection(randomDirection);
	}
	else
	{
		GenerateRandomNumber();
	}
}