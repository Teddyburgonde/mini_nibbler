#include "core/Game.hpp"
#include "includes/IGui.hpp"
#include "gui_ncurses/GuiNcurses.hpp"
#include <unistd.h>

/**
 * @file main.cpp
 * @brief Point d'entrée principal du jeu Nibbler.
 *
 * Ce fichier initialise les paramètres de la fenêtre à partir des arguments
 * de la ligne de commande, instancie la GUI et la logique de jeu, puis lance
 * la boucle principale :
 * - Récupère l'input utilisateur
 * - Met à jour l'état du jeu
 * - Affiche le rendu
 * 
 * À la fin, la mémoire est libérée et la fenêtre nettoyée proprement.
 */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./nibbler [width] [height]\n";
		return (1);
	}
	int width = std::atoi(argv[1]);
	int height = std::atoi(argv[2]);

	if (width < 1 || height < 1) 
	{
		std::cout << "Error: size must be positive integers\n";
		return 1;
	}
	bool quitByPlayer = false;
	setlocale(LC_ALL, "");
	IGui* gui = new GuiNcurses();
	gui->init(width, height);
	GameState game(width, height);

	while (!game.isFinished())
	{
		Input input = gui->getInput();
		if (input == Input::EXIT)
		{
			quitByPlayer = true;
			break;
		}
		game.setDirection(input);
		game.update();
		gui->render(game);
		usleep(100000);
	}
	if (!quitByPlayer)
	{
		if (game.getScore() >= 100)
			gui->showVictory();
		else
			gui->showGameOver();
	}
	gui->cleanup();
	delete gui;
	return (0);
}