#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Collision.hpp"
#include "CollisionDetectionRect.hpp"
#include "Ghost.hpp"
#include "Dot.hpp"
#include "PowerPellet.hpp"
#include "Fruit.hpp"

class Pacman
{
	public:
		Pacman();
		~Pacman();
		void Events(sf::Event event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime, const std::vector<Collision*>& collisionRects);
		void Animation(sf::Vector2f direction);
		bool isColliding;
		bool directionChanged;
		void CheckCollisionWithWallColored(const std::vector<Collision*>& collisionRects);
		void ReactToCollision();
		void SetSpeedX();
		void SetSpeedY();
		bool CollisionWith(Ghost& ghost);
		bool CollisionWith(Dot& dot);
		bool CollisionWith(PowerPellet& powerPellet);
		bool CollisionWith(Fruit& fruit);
		void Reset();
		const sf::Texture* GetTexture();


	private:
		std::vector<sf::Vector2f> inputs;
		sf::Sprite pacman;
		Collision* collisionRect;
		sf::Vector2f velocity;
		float speedX;
		float speedY;
		sf::Vector2f direction;
		sf::Texture pacmanTexture;
		sf::Clock clock;
		int currentFrame;
		std::vector<CollisionDetectionRect*> collisionDetectionRects;
		std::vector<bool> isCollisionDetectionRectColliding;
		void OutOfBounds();
		sf::Vector2f nextDirectionLeft;
		sf::Vector2f nextDirectionRight;
		sf::Vector2f nextDirectionUp;
		sf::Vector2f nextDirectionDown;
};

