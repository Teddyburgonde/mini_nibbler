/**
 * @file Game.hpp
 * @brief Déclaration de la classe Game qui gère la logique du jeu Snake.
 *
 * Cette classe est responsable de la gestion du serpent, de la nourriture,
 * et de la logique de jeu.
 */

#pragma once

#include "Snake.hpp"
#include <cstdlib>
#include <ctime>

/**
 * @brief Classe principale qui gère la boucle du jeu Snake.
 *
 * Gère le serpent, la nourriture, la détection de fin de jeu, 
 * et la logique de mise à jour.
 */
class Game
{
	public:
		Game();
		Game(int width, int height);
		Game(const Game& other);
		Game& operator=(const Game& other);
		~Game();
		void	generateRandomFoodPosition();

	private:
		Snake	snake;	///< Le serpent du jeu.
		Point	food;	///< La position de la nourriture.
		int		width;	///< Largeur du plateau de jeu.
		int		height; ///< Hauteur du plateau de jeu.
};


