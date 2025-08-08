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

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: ./nibbler [width] [height]\n";
		return 1;
	}
	int width = std::atoi(argv[1]);
	int height = std::atoi(argv[2]);

	if (width < 1 || height < 1) 
	{
		std::cout << "Error: size must be positive integers\n";
		return 1;
	}
	setlocale(LC_ALL, "");
	IGui* gui = loadGui("./libgui_ncurses.so", width, height);

	GameState game(width, height);
	bool quitByPlayer = false;

	while (!game.isFinished())
	{
		Input input = gui->getInput();

		// 🎛️ GUI switching
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
			system("stty sane");  // restaure le terminal (important !)
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
		game.setDirection(input);
		game.update();
		gui->render(game);
		usleep(100000);
	}
	if (!quitByPlayer)
	{
		if (game.getScore() >= 50)
			gui->showVictory();
		else
			gui->showGameOver();
	}
	gui->cleanup();
	delete gui;
	return 0;
}
