#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Collision.hpp"
#include "CollisionDetectionRect.hpp"

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
		void CheckCollisionWithWall(const std::vector<Collision*>& collisionRects);
		void ReactToCollision();

	private:
		std::vector<CollisionDetectionRect*> collisionDetectionRects;
		sf::Sprite pacman;
		sf::Vector2f velocity;
		float speed;
		sf::Vector2f direction;
		sf::Texture pacmanTexture;
		sf::Clock clock;
		int currentFrame;
};

