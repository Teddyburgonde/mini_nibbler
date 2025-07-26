#include "GuiSDL.hpp"

/**
 * @brief Vérifie que la taille de la zone de jeu est raisonnable pour l'affichage SDL.
 * 
 * Cette fonction empêche le lancement du jeu si la largeur ou la hauteur demandée
 * est trop petite (moins de 10 cases) ou trop grande (plus de 100 cases).
 * Cela évite d’avoir un affichage illisible ou une fenêtre qui dépasse l’écran.
 *
 * @param requiredWidth Largeur de la zone de jeu (en cases).
 * @param requiredHeight Hauteur de la zone de jeu (en cases).
 */
void GuiSDL::checkTerminalSize(int requiredWidth, int requiredHeight)
{
	const int minSize = 10;
	const int maxSize = 100;

	if (requiredWidth < minSize || requiredHeight < minSize)
	{
		std::cerr << "❌ Game area too small: minimum is "
		          << minSize << "x" << minSize << std::endl;
		SDL_Quit();
		exit(1);
	}
	if (requiredWidth > maxSize || requiredHeight > maxSize)
	{
		std::cerr << "❌ Game area too big: maximum is "
		          << maxSize << "x" << maxSize << std::endl;
		SDL_Quit();
		exit(1);
	}
}

void    GuiSDL::init(int width, int height)
{
    _screenWidth = width;
	_screenHeight = height;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "❌ SDL_Init failed: " << SDL_GetError() << std::endl;
		exit(1);
	}
    checkTerminalSize(width, height);

    _window = SDL_CreateWindow("Nibbler - SDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width * 20, height * 20,
		0);
    if (!_window)
	{
		std::cerr << "❌ SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
	{
		std::cerr << "❌ SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_window);
		SDL_Quit();
		exit(1);
	}
}



// #include <SDL2/SDL.h>

// int main(void)
// {
// 	SDL_Init(SDL_INIT_VIDEO);

// 	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
// 	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

// 	bool running = true;
// 	SDL_Event event;

// 	while (running)
// 	{

// 		while (SDL_PollEvent(&event))
//         {
//             if (event.type == SDL_QUIT)
//                 running = false;
//         }
// 		SDL_SetRenderDrawColor(renderer, 187, 159, 93, 255);
// 		SDL_RenderClear(renderer);
// 		SDL_RenderPresent(renderer);
// 	}

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
// 	SDL_Quit();
// }