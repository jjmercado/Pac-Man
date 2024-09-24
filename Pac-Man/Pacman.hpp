#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Collision.hpp"
#include <iostream>

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
		std::vector<sf::RectangleShape*> collisionDetectionRects;
		void IsCollidingWithWall(std::vector<Collision*> collisionRects);

	private:
		sf::RectangleShape leftCollisionRect;
		sf::RectangleShape rightCollisionRect;
		sf::RectangleShape upCollisionRect;
		sf::RectangleShape downCollisionRect;
		sf::Sprite pacman;
		sf::Vector2f velocity;
		float speed;
		sf::Vector2f direction;
		sf::Texture pacmanTexture;
		sf::Clock clock;
		int currentFrame;
		void UpdateCollisionRect();
		void SetCollisionRect();
};

