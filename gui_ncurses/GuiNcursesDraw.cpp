/**
 * @file GuiNcursesDraw.cpp
 * @brief Implémentation des fonctions de dessin pour l'interface graphique Ncurses du jeu
 *
 * Ce fichier contient les implémentations des fonctions utilisées pour dessiner les éléments du jeu Snake,
 * tels que les murs, le serpent et la nourriture, dans une interface graphique basée sur Ncurses.
 */

#include <ncurses.h>
#include "GuiNcursesDraw.hpp"

/**
 * @brief Dessine le mur supérieur.
 *
 * Cette fonction dessine une ligne de caractères '#' pour représenter le mur supérieur du cadre de jeu.
 *
 * @param width Largeur du cadre de jeu.
 */
void drawTopWall(int width)
{
	for (int x = 0; x < width; ++x)
		mvaddch(0, x, '#');
}

/**
 * @brief Dessine le mur inférieur.
 *
 * Cette fonction dessine une ligne de caractères '#' pour représenter le mur inférieur du cadre de jeu.
 *
 * @param width Largeur du cadre de jeu.
 * @param height Hauteur du cadre de jeu.
 */
void drawBottomWall(int width, int height)
{
	for (int x = 0; x < width; ++x)
		mvaddch(height - 1, x, '#');
}

/**
 * @brief Dessine le mur gauche.
 *
 * Cette fonction dessine une colonne de caractères '#' pour représenter le mur gauche du cadre de jeu.
 *
 * @param height Hauteur du cadre de jeu.
 */
void drawLeftWall(int height)
{
	for (int y = 0; y < height; ++y)
		mvaddch(y, 0, '#');
}

/**
 * @brief Dessine le mur droit.
 *
 * Cette fonction dessine une colonne de caractères '#' pour représenter le mur droit du cadre de jeu.
 *
 * @param width Largeur du cadre de jeu.
 * @param height Hauteur du cadre de jeu.
 */
void drawRightWall(int width, int height)
{
	for (int y = 0; y < height; ++y)
		mvaddch(y, width - 1, '#');
}

/**
 * @brief Dessine tous les murs du cadre de jeu.
 *
 * Cette fonction appelle les fonctions de dessin des murs supérieur, inférieur, gauche et droit
 * pour dessiner le cadre complet du jeu.
 *
 * @param width Largeur du cadre de jeu.
 * @param height Hauteur du cadre de jeu.
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
 *
 * Cette fonction dessine le serpent en utilisant '@' pour la tête et 'O' pour le corps.
 * La tête est colorée en vert et le corps en blanc.
 *
 * @param snake La deque représentant le corps du serpent, où le premier élément est la tête.
 */
void drawSnake(const std::deque<Point>& snake)
{
	if (snake.empty())
		return;
	attron(COLOR_PAIR(1));
	mvaddch(snake[0].y, snake[0].x, '@');
	attroff(COLOR_PAIR(1));

	for (size_t i = 1; i < snake.size(); ++i)
		mvaddch(snake[i].y, snake[i].x, 'O');
}

/**
 * @brief Dessine la nourriture à l'écran.
 *
 * Cette fonction dessine la nourriture en utilisant le caractère '*'.
 * La nourriture est colorée en rouge.
 *
 * @param food La position de la nourriture dans le jeu, représentée par un Point.
 */
void drawFood(const Point& food)
{
	attron(COLOR_PAIR(2));
	mvaddch(food.y, food.x, '*');
	attroff(COLOR_PAIR(2));
}
