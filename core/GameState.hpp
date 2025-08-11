/**
 * @file GameState.hpp
 * @brief Déclaration de la classe GameState pour le jeu Snake.
 *
 * Cette classe gère l'état du jeu, y compris le serpent, la nourriture,
 * le score et les obstacles. Elle permet de mettre à jour le jeu et de
 * gérer les interactions du joueur.
 */

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
		const	std::vector<Point>& getObstacles() const;
		void	toggleHelpMenu();
		bool	isHelpMenuActive() const;

	private:
		Snake	snake;					///< Le serpent du jeu.
		Point	food;					///< La position de la nourriture.
		std::vector<Point> _obstacles;	///< Liste des obstacles du jeu.
		int		_score;					///< Le score actuel du joueur.
		bool	finished;				///< Indique si le jeu est terminé.
		int		_width;					///< Largeur du plateau de jeu.
		int		_height;				///< Hauteur du plateau de jeu.
		bool 	_obstaclesEnabled;		///< Indique si les obstacles sont activés.
		bool	_helpMenuActive;		///< Indique si le menu d'aide est actif.

};