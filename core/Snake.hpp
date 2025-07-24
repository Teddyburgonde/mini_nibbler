#pragma once

#include <deque>
#include <iostream>

/**
 * @brief Structure représentant un point (x, y) sur la grille.
 */
struct Point 
{
	int	x;
	int	y;
};

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
		bool checkCollision(const Point& pos) const;
		const std::deque<Point>& getBody() const;
		void setDirection(Direction newDir);


	private:
		std::deque<Point> body;
		Direction direction;
};