#include "core/Game.hpp"
#include "includes/IGui.hpp"
#include "gui_ncurses/GuiNcurses.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <dlfcn.h>
#include <locale.h>
#include <unistd.h>



IGui* loadGui(const std::string& path, int width, int height)
{
	void* handle = dlopen(path.c_str(), RTLD_LAZY);
	if (!handle)
	{
		std::cerr << "❌ Failed to load " << path << ": " << dlerror() << std::endl;
		exit(1);
	}

	using CreateGuiFunc = IGui* (*)();
	CreateGuiFunc create = (CreateGuiFunc)dlsym(handle, "createGui");
	if (!create)
	{
		std::cerr << "❌ Failed to find createGui() in " << path << std::endl;
		dlclose(handle);
		exit(1);
	}

	IGui* gui = create();
	gui->init(width, height);
	return gui;
}

/**
 * @brief Point d'entrée principal du jeu Nibbler.
 * 
 * Ce `main()` initialise la taille du plateau, charge dynamiquement
 * une interface graphique (GUI) via une bibliothèque dynamique `.so`,
 * exécute la boucle principale du jeu, et gère :
 * 
 * - les entrées utilisateur (`q`, flèches, 1/2 pour changer de GUI)
 * - les événements de victoire/défaite
 * - l'affichage dynamique selon la GUI sélectionnée
 * 
 * Le jeu peut basculer dynamiquement entre plusieurs GUIs (ncurses, SDL, etc.)
 * grâce à `dlopen()` et `dlsym()` via la fonction `loadGui()`.
 * 
 * @param argc Nombre d'arguments
 * @param argv Valeurs des arguments (width, height)
 * @return int Code de retour du programme (0 = succès)
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
	setlocale(LC_ALL, ""); // Pour les emojis UTF-8
	
	IGui* gui = loadGui("./gui_ncurses/libgui_ncurses.so", width, height);
	GameState game(width, height);
	bool quitByPlayer = false;

	while (!game.isFinished())
	{
		Input input = gui->getInput();

		// 🎛️ GUI switching
		if (input == Input::SWITCH_TO_1)
		{
			gui->cleanup(); delete gui;
			gui = loadGui("./libgui_ncurses.so", width, height);
			continue;
		}
		else if (input == Input::SWITCH_TO_2)
		{
			gui->cleanup(); delete gui;
			gui = loadGui("./libgui_sdl.so", width, height);
			continue;
		}

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