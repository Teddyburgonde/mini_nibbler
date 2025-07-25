#include "Game.hpp"

/**
 * @brief Constructeur de la classe Game.
 * Initialise le snake au centre, la position de la nourriture et les dimensions du plateau.
 */
Game::Game(int w, int h)
	: snake(w / 2, h / 2), gameOver(false), width(w), height(h)
{
	std::srand(std::time(nullptr));
	generateRandomFoodPosition();
}

/**
 * @brief Destructeur de la classe Game.
 */
Game::~Game()
{}

/**
 * @brief Boucle principale du jeu.
 * Gère les déplacements, les collisions et la logique du score.
 */
void Game::loop()
{
	while (!gameOver)
	{
		snake.move();

		// Si le snake mange la nourriture
		if (snake.getBody().front().x == food.x && snake.getBody().front().y == food.y)
		{
			snake.grow();
			generateRandomFoodPosition();
		}

		// Collision avec lui-même
		if (snake.checkCollision(snake.getBody().front()))
			gameOver = true;
	}
}

/**
 * @brief Génère une nouvelle position aléatoire pour la nourriture.
 */
void Game::generateRandomFoodPosition()
{
	int x = std::rand() % width;
	int y = std::rand() % height;
	food = Point{x, y};
}
