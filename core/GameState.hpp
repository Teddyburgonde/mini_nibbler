#pragma once

#include "Snake.hpp"
#include "../includes/Input.hpp"
#include "../includes/Point.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

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
		GameState(int width, int height, bool obstacles);
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
		void	generateObstacles();
		const std::vector<Point>& getObstacles() const;

	private:
		Snake	snake;
		Point	food;
		std::vector<Point> _obstacles;
		int		_score;
		bool	finished;
		int		_width;
		int		_height;
		bool 	_obstaclesEnabled;

};