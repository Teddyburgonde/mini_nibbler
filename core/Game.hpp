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
		Game(int width, int height);
		~Game();
		void	generateRandomFoodPosition();

	private:
		Snake	snake;
		Point	food;
		int		width;
		int		height;
};


