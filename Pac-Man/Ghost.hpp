#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CollisionDetectionRect.hpp"

class Ghost
{
	public:
		Ghost();
		Ghost(sf::Color color, sf::Vector2f startPos, float startTime, sf::Vector2f startDirection);
		~Ghost();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects);
		void Animation();
		void SetDirection(sf::Vector2f direction);
		sf::Sprite GetSprite();
		void Reset();
		void SetEatable(bool value);
		bool GetEatable();
		int GetPoints();

	private:
		sf::Texture ghostTexture;
		sf::Sprite ghost;
		sf::Color color;
		sf::Texture eyesBackgroundTexture;
		sf::Sprite eyesBackground;
		sf::Texture pupilsTexture;
		sf::Sprite pupils;
		sf::Clock animationClock;
		sf::Clock startClock;
		sf::Clock eatableClock;
		sf::Vector2f velocity;
		Collision* collisionRect;
		float startTime;
		float speedX;
		float speedY;
		sf::Vector2f direction;
		sf::Vector2f startDirection;
		sf::Vector2f startPosition;
		int currentFrame;
		bool SetStartTime(float startTime);
		void ResetEatableState(float resetTime);
		void OutOfBounds();
		bool eatable;
		int points;
};

