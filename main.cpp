/**
 * @file main.cpp
 * @brief Point d'entrée du jeu Nibbler.
 *
 * Ce fichier contient la logique principale du jeu, gère les entrées utilisateur,
 * initialise l'interface graphique et gère le cycle de vie du jeu.
 * Il permet également de charger dynamiquement différentes interfaces graphiques
 * (ncurses, SDL, OpenGL) en fonction des préférences de l'utilisateur.
 */

#include "core/Game.hpp"
#include "includes/IGui.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <dlfcn.h>
#include <locale.h>
#include <unistd.h>
#include <ncurses.h>
#include <SDL2/SDL.h>

/**
 * @brief Charge dynamiquement un module GUI depuis une bibliothèque partagée.
 * 
 * @param path Chemin vers la bibliothèque partagée (.so).
 * @param width Largeur initiale du plateau de jeu.
 * @param height Hauteur initiale du plateau de jeu.
 * @return Pointeur vers l’instance IGui créée.
 * @note Quitte le programme en cas d’échec du chargement.
 */
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
 * @brief Affiche l’écran de fin approprié selon le résultat de la partie.
 * 
 * @param game Référence vers l’état actuel du jeu.
 * @param gui Référence vers le pointeur de l’interface graphique.
 * @param quitByPlayer Indique si le joueur a quitté volontairement.
 */
void	showEndScreen(GameState &game, IGui* &gui, bool quitByPlayer)
{
	if (!quitByPlayer)
	{
		if (game.getScore() >= 200)
			gui->showVictory();
		else
			gui->showGameOver();
	}
}

/**
 * @brief Affiche l’aide/usage du programme.
 * 
 * @param prog Nom du programme (argv[0]).
 */
static void	printUsage(const char* prog) 
{
    std::cout << "Usage: " << prog << " <width> <height> [-o] [-chaos]\n"
              << "  -o       : enable obstacles\n"
              << "  -chaos   : invert directions (chaos mode)\n"
              << "  -h,--help: show this help\n";
}

/**
 * @brief Analyse et valide les arguments passés en ligne de commande.
 * 
 * @param argc Nombre d’arguments.
 * @param argv Tableau des arguments.
 * @param width Référence où stocker la largeur du plateau.
 * @param height Référence où stocker la hauteur du plateau.
 * @param obstaclesEnabled Référence pour indiquer si les obstacles sont activés.
 * @param chaosEnabled Référence pour indiquer si le mode chaos est activé.
 * @return true si l’analyse est réussie, false sinon.
 */
bool parseArguments(int argc, char** argv, int &width, int &height, bool &obstaclesEnabled, bool &chaosEnabled)
{

	if (argc < 3 || argc > 5) 
	{
		printUsage(argv[0]); 
		return false;
	}

	int		w = 0;
	int 	h = 0;
    bool	obstacles = false;
    bool    chaos = false;

    try 
	{
        w = std::stoi(argv[1]);
        h = std::stoi(argv[2]);
    } 
	catch (const std::exception&) 
	{
        std::cout << "Error: width/height must be integers.\n";
        printUsage(argv[0]);
        return false;
    }
    if (w < 10 || h < 10)
	{
        std::cout << "Error: size must be more than 10.\n";
        return false;
    }

    // options
    for (int i = 3; i < argc; ++i) 
	{
        std::string opt = argv[i];
        if (opt == "-o")            
			obstacles = true;
        else if (opt == "-chaos")   
			chaos = true;
        else if (opt == "-h" || opt == "--help") 
		{ 
			printUsage(argv[0]); 
			return false; 
		}
        else 
		{
            std::cout << "Unknown option: " << opt << "\n";
            printUsage(argv[0]);
            return false;
        }
    }

    // Succès: on affecte les sorties
    width = w; 
	height = h;
    obstaclesEnabled = obstacles;
    chaosEnabled = chaos;
    return true;
}

/**
 * @brief Applique la transformation du mode chaos sur la direction du joueur.
 * 
 * @param input Direction actuelle du joueur.
 * @return Nouvelle direction après transformation (ou la même si non applicable).
 */
Input applyChaosMode(Input input)
{
    switch (input)
    {
        case Input::UP:    
			return Input::DOWN;
        case Input::DOWN:  
			return Input::UP;
        case Input::LEFT:  
			return Input::RIGHT;
        case Input::RIGHT: 
			return Input::LEFT;
        default:           
			return input;
    }
}

/**
 * @brief Point d’entrée du jeu Nibbler.
 * 
 * @param argc Nombre d’arguments.
 * @param argv Tableau des arguments.
 * @return Code de sortie.
 */
int main(int argc, char **argv)
{
	int width = 0;
	int	height = 0;
	bool obstaclesEnabled = false;
	bool chaosEnabled = false;
	if (!parseArguments(argc, argv, width, height, obstaclesEnabled, chaosEnabled))
        return 1;
	setlocale(LC_ALL, "");
	IGui* gui = loadGui("./libgui_ncurses.so", width, height);

	GameState game(width, height, obstaclesEnabled);
	bool quitByPlayer = false;

	while (!game.isFinished())
	{
		Input input = gui->getInput();

		if (input == Input::HELP)
			game.toggleHelpMenu();
		if (chaosEnabled)
    		input = applyChaosMode(input);
		// GUI switching
		if (input == Input::SWITCH_TO_1)
		{
			gui->cleanup(); delete gui;
			gui = loadGui("./libgui_sdl.so", width, height);
			usleep(500000); 
			continue;
		}
		else if (input == Input::SWITCH_TO_2)
		{
			gui->cleanup(); delete gui;
			SDL_Quit();  // au cas où SDL n'a pas bien quitté
			system("stty sane");  // restaure le terminal
			system("clear");
			gui = loadGui("./libgui_ncurses.so", width, height);
			continue;
		}
		else if (input == Input::SWITCH_TO_3)
		{
			gui->cleanup(); delete gui;
			gui = loadGui("./libgui_opengl.so", width, height);
			usleep(500000);
			continue;
		}
		if (input == Input::EXIT)
		{
			quitByPlayer = true;
			break;
		}
		if (!game.isHelpMenuActive())
		{
			game.setDirection(input);
			game.update();
		}
		gui->render(game);
		usleep(100000);
	}
	showEndScreen(game, gui, quitByPlayer);
	gui->cleanup();
	delete gui;
	return 0;
}
