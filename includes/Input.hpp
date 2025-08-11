/**
 * @file Input.hpp
 * @brief Définition de l'énumération Input pour les entrées clavier.
 */

#pragma once

/**
 * @brief Enumération des entrées clavier utilisées dans le jeu.
 *
 * Cette énumération représente les différentes directions possibles
 * pour le serpent ainsi que les actions spéciales comme quitter le jeu.
 * Elle est utilisée pour unifier la gestion des entrées utilisateur
 * dans toutes les interfaces graphiques (ncurses, SDL, SFML...).
 */
enum Input 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	EXIT,
	NONE,
	HELP,
	SWITCH_TO_1,
	SWITCH_TO_2,
	SWITCH_TO_3
};