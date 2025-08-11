/**
 * @file GuiNcurses.hpp
 * @brief Classe d’interface graphique Ncurses pour le jeu Snake.
 *
 * Cette classe implémente l’interface IGui pour fournir une interface utilisateur en mode texte
 * utilisant la bibliothèque Ncurses. Elle gère l’affichage du jeu, la récupération des entrées utilisateur,
 * et les messages de fin de jeu.
 */

#pragma once
#include "../includes/IGui.hpp"
#include <ncurses.h>
#include "../core/GameState.hpp"
#include "GuiNcursesDraw.hpp"

/**
 * @brief Implémentation Ncurses de l’interface IGui.
 * 
 * Cette classe fournit l’affichage en terminal du jeu Snake en utilisant la bibliothèque Ncurses.
 * Elle respecte le contrat défini dans IGui : init, render, getInput, cleanup.
 */
class GuiNcurses : public IGui
{
	public:
		GuiNcurses();
		GuiNcurses(const GuiNcurses& other);
		GuiNcurses& operator=(const GuiNcurses& other);
		~GuiNcurses() override = default;

		void	init(int width, int height) override;
		void	render(const GameState& state) override;
		Input	getInput() override;
		void	checkTerminalSize(int requiredWidth, int requiredHeight);
		void	showVictory() override;
		void	showGameOver() override;
		void	cleanup() override;
		void	drawObstacles(const std::vector<Point>& obstacles);

	private:
		int	_screenWidth;	///< Largeur de l'écran en caractères
		int	_screenHeight;	///< Hauteur de l'écran en caractères
};
