#pragma once
#include "../includes/IGui.hpp"
// #include <SDL2/SDL.h>
#include <SDL.h> // MAC

#include "../core/GameState.hpp"
#include "GuiSDLDraw.hpp"


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
		void showVictory() override;
		void showGameOver() override;
		void	cleanup() override;
		~GuiSDL() override = default;
	private:
		void checkTerminalSize(int requiredWidth, int requiredHeight);
		int	_screenWidth;
		int	_screenHeight;
		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;
};