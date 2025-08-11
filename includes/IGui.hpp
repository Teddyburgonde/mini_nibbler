/**
 * @file IGui.hpp
 * @brief Interface pour les moteurs graphiques du projet.
 *
 * Cette interface définit les méthodes nécessaires pour initialiser, afficher et gérer les entrées utilisateur dans un moteur graphique.
 */

#pragma once

#include "../core/GameState.hpp"
#include "Input.hpp"

/**
 * @class IGui
 * @brief Interface abstraite pour toutes les interfaces graphiques du projet (ncurses, SFML, SDL…).
 *
 * Cette interface définit un contrat minimal que chaque GUI doit respecter :
 * - Initialiser une fenêtre avec une taille donnée.
 * - Afficher l’état courant du jeu.
 * - Récupérer les entrées utilisateur (clavier).
 * - Libérer proprement les ressources utilisées.
 *
 * Toute classe implémentant cette interface pourra être interchangeable dans le moteur de jeu.
 */
class IGui 
{
	public:
		virtual void init(int width, int height) = 0;
		virtual void render(const GameState& state) = 0;
		virtual Input getInput() = 0;
		virtual void cleanup() = 0;
		virtual void showVictory() = 0;
		virtual void showGameOver() = 0;
		virtual ~IGui(){};
};