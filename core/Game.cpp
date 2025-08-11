/**
 * @file Game.cpp
 * @brief Implémentation de la classe Game.
 *
 * Cette classe gère le plateau du jeu Snake (taille et position de la nourriture).
 */

#include "Game.hpp"

/**
 * @brief Constructeur par défaut de la classe Game.
 *
 * Initialise un jeu vide avec une taille de plateau nulle.
 */
Game::Game()
	: snake(0, 0), food{0, 0}, width(0), height(0)
{
	std::srand(std::time(nullptr));
}

/**
 * @brief Constructeur avec paramètres de la classe Game.
 *
 * Initialise le snake au centre, la position de la nourriture et les dimensions du plateau.
 *
 * @param w Largeur du plateau de jeu.
 * @param h Hauteur du plateau de jeu.
 */
Game::Game(int w, int h)
	: snake(w / 2, h / 2), food{0, 0}, width(w), height(h)
{
	std::srand(std::time(nullptr));
	generateRandomFoodPosition();
}

/**
 * @brief Constructeur de copie.
 *
 * Copie toutes les données du jeu.
 *
 * @param other Autre instance de Game à copier.
 */
Game::Game(const Game& other)
	: snake(other.snake), food(other.food), width(other.width), height(other.height)
{}

/**
 * @brief Opérateur d'affectation.
 *
 * Copie toutes les données d'une autre instance dans celle-ci.
 *
 * @param other Autre instance de Game à copier.
 * @return Référence vers l'objet courant.
 */
Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		snake = other.snake;
		food = other.food;
		width = other.width;
		height = other.height;
	}
	return *this;
}

/**
 * @brief Destructeur de la classe Game.
 */
Game::~Game()
{}

/**
 * @brief Génère une nouvelle position aléatoire pour la nourriture.
 */
void Game::generateRandomFoodPosition()
{
	int x = std::rand() % width;
	int y = std::rand() % height;
	food = Point{x, y};
}

