/**
 * @file GuiNcursesDraw.hpp
 * @brief Déclaration des fonctions de dessin pour l'interface graphique ncurses du jeu Snake.
 *
 * Ce fichier contient les déclarations des fonctions utilisées pour dessiner les éléments du jeu Snake,
 * tels que les murs, le serpent et la nourriture, dans une interface graphique basée sur ncurses.
 */

#pragma once

#include <deque>
#include "../core/Snake.hpp"


void drawWalls(int width, int height);
void drawTopWall(int width);
void drawBottomWall(int width, int height);
void drawLeftWall(int height);
void drawRightWall(int width, int height);
void drawSnake(const std::deque<Point>& snake);
void drawFood(const Point& food);
