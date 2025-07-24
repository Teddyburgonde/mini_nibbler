#pragma once

#include "Snake.hpp"
#include "../includes/Input.hpp"
#include <cstdlib>
#include <ctime>

/**
 * @class GameState
 * @brief Représente l'état actuel du jeu Snake.
 *
 * Cette classe contient les informations essentielles pour faire évoluer
 * le jeu : le serpent, la nourriture, le score et l'état de fin.
 * Elle permet de mettre à jour la logique du jeu, de modifier la direction,
 * de générer de la nourriture et de gérer le score.
 */
class GameState
{
	public:
		GameState();
		GameState(const GameState& copy);
		GameState& operator=(const GameState& copy);
		~GameState();

		const	Snake& getSnake() const;
		const	Point& getFood() const;
		int		getScore() const;
		bool	isFinished() const;

		void	update();
		void	setDirection(Input input);
		void	generateFood();
		void	reset();
		void	increaseScore(int amount);

	private:
		Snake	snake;
		Point	food;
		int		_score;
		bool	finished;
};