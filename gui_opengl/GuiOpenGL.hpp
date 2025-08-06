#pragma once
#include "../includes/IGui.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "../core/GameState.hpp"


/**
 * @class GuiOpenGL
 * @brief Implémentation de l'interface graphique du jeu en utilisant la bibliothèque OpenGL.
 * 
 * Cette classe hérite de l'interface IGui et fournit une version OpenGL de l'affichage
 * du jeu Snake. Elle gère l'initialisation de la fenêtre et du contexte OpenGL,
 * le rendu graphique du jeu, la gestion des entrées clavier, l'affichage de messages
 * de fin (victoire ou défaite) et le nettoyage des ressources.
 * 
 * Elle est compilée en bibliothèque dynamique (.so) et chargée à l'exécution.
 */
class GuiOpenGL : public IGui
{
	public:
		void	init(int width, int height) override;
		void	render(const GameState& state) override;
		Input	getInput() override;
		void	showVictory() override;
		void	showGameOver() override;
		void	cleanup() override;
		~GuiOpenGL() override = default;

	private:
		GLFWwindow* _window = nullptr;
		int	_screenWidht;
		int	_screenHeight;
};