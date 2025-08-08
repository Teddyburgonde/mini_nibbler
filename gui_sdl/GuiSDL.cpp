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

/**
 * @brief Initialise la fenêtre et le moteur de rendu SDL pour le jeu.
 * 
 * Cette fonction configure la largeur et la hauteur du plateau de jeu,
 * initialise le sous-système vidéo de SDL, vérifie que la taille de la
 * zone de jeu est raisonnable via `checkTerminalSize()`, crée une
 * fenêtre SDL centrée, puis initialise un moteur de rendu matériel
 * accéléré.
 * 
 * En cas d'échec à l'une des étapes, la fonction affiche un message
 * d'erreur sur la sortie standard et termine le programme avec `exit(1)`.
 * 
 * @param width  Largeur du plateau de jeu (en cases).
 * @param height Hauteur du plateau de jeu (en cases).
 */
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

/**
 * @brief Affiche l'état actuel du jeu à l'écran avec SDL.
 * 
 * Cette fonction efface l'écran, puis dessine :
 * - le serpent (en vert, case par case)
 * - la nourriture (en rouge)
 * - le score (via des blocs blancs, 1 bloc = 10 points)
 * 
 * Chaque case logique du jeu est représentée par un carré de 20x20 pixels.
 * Le tout est ensuite affiché via SDL_RenderPresent().
 * 
 * @param state Référence vers l'état actuel du jeu (serpent, nourriture, score, etc.).
 */
void	GuiSDL::render(const GameState& state)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); // fond noir
	SDL_RenderClear(_renderer);

	// Dessine le serpent
	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255); // vert
	for (const Point& p : state.getSnake().getBody())
	{
		SDL_Rect rect = { p.x * 20, p.y * 20, 20, 20 };
		SDL_RenderFillRect(_renderer, &rect);
	}

	// Dessine la nourriture
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255); // rouge
	Point food = state.getFood();
	SDL_Rect foodRect = { food.x * 20, food.y * 20, 20, 20 };
	SDL_RenderFillRect(_renderer, &foodRect);

	// Affiche le score avec des blocs
	int score = state.getScore();
	int nbBlocks = score / 10; // 1 bloc = 10 points
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // blanc
	
	for (int i = 0; i < nbBlocks; ++i)
	{
		SDL_Rect block = { 10 + i * 25, 10, 20, 20 };
		SDL_RenderFillRect(_renderer, &block);
	}

	// Dessine les obstacles (gris foncé)
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);

	for (const Point& p : state.getObstacles())
	{
		SDL_Rect rect = { p.x * 20, p.y * 20, 20, 20 };
		SDL_RenderFillRect(_renderer, &rect);
	}


	// Affiche le rendu à l'écran
	SDL_RenderPresent(_renderer);
}

/**
 * @brief Gère les entrées clavier via SDL.
 * 
 * Utilise SDL_PollEvent() pour détecter :
 * - les flèches directionnelles (SDLK_UP, etc.)
 * - les touches 'q' ou Échap pour quitter
 * - les touches '1', '2', '3' pour changer dynamiquement de GUI
 * - les événements SDL_QUIT (fermeture fenêtre)
 * 
 * Retourne un Input correspondant à l'action utilisateur.
 * 
 * @return Input La direction ou l'action détectée par l'utilisateur.
 */
Input	GuiSDL::getInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return Input::EXIT;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					return Input::UP;
				case SDLK_DOWN:
					return Input::DOWN;
				case SDLK_LEFT:
					return Input::LEFT;
				case SDLK_RIGHT:
					return Input::RIGHT;
				case SDLK_1: 
					return Input::SWITCH_TO_1;
				case SDLK_2: 
					return Input::SWITCH_TO_2;
				case SDLK_3: 
					return Input::SWITCH_TO_3;
				case SDLK_ESCAPE:
				case SDLK_q:     
					return Input::EXIT;
			}
		}
	}
	return Input::NONE;
}

/**
 * @brief Libère les ressources SDL et réinitialise le terminal.
 * 
 * Détruit le renderer et la fenêtre s'ils existent, quitte SDL
 * et restaure l'état du terminal avec la commande `stty sane`.
 */
void GuiSDL::cleanup() 
{
	if (_renderer) 
		SDL_DestroyRenderer(_renderer);
	if (_window) 
		SDL_DestroyWindow(_window);
	SDL_Quit();
	system("stty sane");
}

/**
 * @brief Affiche une boîte de dialogue SDL indiquant la défaite.
 * 
 * Utilise SDL_ShowSimpleMessageBox avec une icône d'erreur et le message "You lost!".
 */
void GuiSDL::showGameOver()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Over", "You lost!", _window);
}

/**
 * @brief Affiche une boîte de dialogue SDL indiquant la victoire.
 * 
 * Utilise SDL_ShowSimpleMessageBox avec une icône d'information et le message "You won!".
 */
void GuiSDL::showVictory()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory!", "You won!", _window);
}
