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
		void Update(sf::Time deltaTime);
		void Animation(sf::Vector2f direction);
		bool isColliding;
		bool directionChanged;
		void IsCollidingWithWall(std::vector<Collision*> collisionRects);

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

