#include <SDL2/SDL.h>

int main(void)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;
	SDL_Event event;

	while (running)
	{

		while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
		SDL_SetRenderDrawColor(renderer, 187, 159, 93, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}