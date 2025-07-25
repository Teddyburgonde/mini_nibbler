#include <ncurses.h>
#include "GuiNcursesDraw.hpp"

/**
 * @brief Dessine le mur supérieur.
 */
void drawTopWall(int width)
{
	for (int x = 0; x < width; ++x)
		mvaddch(0, x, '#');
}

/**
 * @brief Dessine le mur inférieur.
 */
void drawBottomWall(int width, int height)
{
	for (int x = 0; x < width; ++x)
		mvaddch(height - 1, x, '#');
}

/**
 * @brief Dessine le mur gauche.
 */
void drawLeftWall(int height)
{
	for (int y = 0; y < height; ++y)
		mvaddch(y, 0, '#');
}

/**
 * @brief Dessine le mur droit.
 */
void drawRightWall(int width, int height)
{
	for (int y = 0; y < height; ++y)
		mvaddch(y, width - 1, '#');
}

/**
 * @brief Dessine tous les murs du cadre de jeu.
 */
void drawWalls(int width, int height)
{
	drawTopWall(width);
	drawBottomWall(width, height);
	drawLeftWall(height);
	drawRightWall(width, height);
}

/**
 * @brief Dessine le serpent à l'écran.
 */
void drawSnake(const std::deque<Point>& snake)
{
	if (snake.empty())
		return;
	attron(COLOR_PAIR(1));
	mvaddch(snake[0].y, snake[0].x, '@'); // Tête
	attroff(COLOR_PAIR(1));

	for (size_t i = 1; i < snake.size(); ++i)
		mvaddch(snake[i].y, snake[i].x, 'O'); // Corps
}

/**
 * @brief Dessine la nourriture à l'écran.
 */
void drawFood(const Point& food)
{
	attron(COLOR_PAIR(2));
	mvaddch(food.y, food.x, '*');
	attroff(COLOR_PAIR(2));
}
