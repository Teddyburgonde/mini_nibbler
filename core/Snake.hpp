/**
 * @file Snake.hpp
 * @brief Définition de la classe Snake.
 *
 * Gère le serpent du jeu, ses mouvements, sa croissance et les collisions.
 */

#pragma once

#include <deque>
#include <iostream>
#include "../includes/Point.hpp"


/**
 * @brief Enumération des directions possibles du serpent.
 */
enum class Direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

/**
 * @brief Classe représentant le serpent dans le jeu.
 *
 * Gère le déplacement, la croissance, les collisions, et la direction.
 */
class Snake 
{
	public:
		Snake(int startX, int startY);
		~Snake();
		void move();
		void grow();
		bool checkCollision(const Point& pos, bool ignoreHead) const;
		const std::deque<Point>& getBody() const;
		void setDirection(Direction newDir);


	private:
		std::deque<Point> body;	///< Corps du serpent, stocké comme une liste de points.
		Direction direction;	///< Direction actuelle du serpent.
};