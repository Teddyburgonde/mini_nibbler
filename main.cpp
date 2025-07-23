#include "core/Game.hpp"

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

	IGui* gui = new GuiNcurses();
	gui->init();
	GameState game;

	while (!game.isFinished())
	{
	Input input = gui->getInput();
	game.setDirection(input);
	game.update();
	gui->render(game);
	}
	gui->cleanup();
	delete gui;
	return (0);
}