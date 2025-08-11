/**
 * @file GuiSDL.hpp
 * @brief Déclaration de la classe GuiSDL pour l'interface graphique du jeu Snake.
 *
 * Cette classe implémente l'interface IGui et utilise la bibliothèque SDL2 pour
 * gérer l'affichage du jeu, les entrées utilisateur et les messages de fin de jeu.
 */

#pragma once
#include "../includes/IGui.hpp"
#include <SDL2/SDL.h>

#include "../core/GameState.hpp"


/**
 * @class GuiSDL
 * @brief Implémentation de l'interface graphique du jeu en utilisant la bibliothèque SDL2.
 * 
 * Cette classe hérite de l'interface IGui et fournit une version SDL de l'affichage
 * du jeu Snake. Elle gère l'initialisation de la fenêtre, le rendu du jeu, les
 * entrées clavier, l'affichage de messages de fin (victoire ou défaite) et le nettoyage.
 * 
 * Elle est compilée en bibliothèque dynamique (.so) et chargée à l'exécution.
 */
class GuiSDL : public IGui
{
	public:
		void	init(int width, int height) override;
		void	render(const GameState& state) override;
		Input	getInput() override;
		void	showVictory() override;
		void	showGameOver() override;
		void	cleanup() override;
		~GuiSDL() override = default;
	private:
		void checkTerminalSize(int requiredWidth, int requiredHeight);
		int	_screenWidth;					///< Largeur de l'écran en pixels.
		int	_screenHeight;					///< Hauteur de l'écran en pixels.
		SDL_Window* _window = nullptr;		///< Pointeur vers la fenêtre SDL.
		SDL_Renderer* _renderer = nullptr;	///< Pointeur vers le renderer SDL.
		void drawHelpMenu();
};