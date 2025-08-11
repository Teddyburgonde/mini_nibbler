/**
 * @file Game.cpp
 * @brief Implémentation de la classe Game.
 *
 * Cette classe gère le plateau du jeu Snake (taille et position de la nourriture).
 */

#include "Game.hpp"

/**
 * @brief Constructeur de la classe Game.
 *
 * Initialise le snake au centre, la position de la nourriture et les dimensions du plateau.
 *
 * @param w Largeur du plateau de jeu.
 * @param h Hauteur du plateau de jeu.
 */
Game::Game(int w, int h)
	: snake(w / 2, h / 2), width(w), height(h)
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
 * @brief Génère une nouvelle position aléatoire pour la nourriture.
 */
void Game::generateRandomFoodPosition()
{
	int x = std::rand() % width;
	int y = std::rand() % height;
	food = Point{x, y};
}
