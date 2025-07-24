#pragma once

#include <deque>
#include "Point.hpp"
#include "Snake.hpp"

/**
 * @brief Fonctions utilitaires pour dessiner les éléments du jeu Snake avec ncurses.
 * 
 * Ces fonctions permettent de dessiner les murs, le serpent et la nourriture à l'écran.
 * Elles sont utilisées par la classe GuiNcurses pour l'affichage.
 */
void drawWalls(int width, int height);
void drawTopWall(int width);
void drawBottomWall(int width, int height);
void drawLeftWall(int height);
void drawRightWall(int width, int height);
void drawSnake(const std::deque<Point>& snake);
void drawFood(const Point& food);
