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
		void	init(int width, int height) override;
		void	render(const GameState& state) override;
		Input	getInput() override;
		void	cleanup() override;
		~GuiNcurses() override = default;
	private:
		void checkTerminalSize(int requiredWidth, int requiredHeight);
		int	_screenWidth;
		int	_screenHeight;
};