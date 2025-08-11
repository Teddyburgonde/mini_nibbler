/**
 * @file GuiSDL.cpp
 * @brief Implémentation de la classe GuiSDL pour l'interface graphique du jeu Snake
 *
 * Cette classe utilise la bibliothèque SDL2 pour gérer l'affichage du jeu,
 * les entrées utilisateur et les messages de fin de jeu. Elle implémente
 * l'interface IGui définie dans includes/IGui.hpp.
 */

#include "GuiSDL.hpp"


GuiSDL::GuiSDL()
	: _screenWidth(0), _screenHeight(0), _window(nullptr), _renderer(nullptr)
{}

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
 * @brief Affiche un menu d'aide simplifié dans la fenêtre SDL.
 * 
 * Cette fonction efface l'écran puis dessine un ensemble de rectangles
 * représentant les touches directionnelles (↑ ↓ ← →) sous forme de blocs blancs.
 * 
 * Elle est utilisée lorsque l'utilisateur active le menu avec la touche 'h',
 * et met automatiquement la partie en pause.
 */
void GuiSDL::drawHelpMenu()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); // fond noir
	SDL_RenderClear(_renderer);

	// Affiche des blocs symboliques pour les directions
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // blanc

	// "↑" en haut
	SDL_Rect up = { 180, 60, 40, 40 };
	SDL_RenderFillRect(_renderer, &up);

	// "←" à gauche
	SDL_Rect left = { 120, 120, 40, 40 };
	SDL_RenderFillRect(_renderer, &left);

	// "→" à droite
	SDL_Rect right = { 240, 120, 40, 40 };
	SDL_RenderFillRect(_renderer, &right);

	// "↓" en bas
	SDL_Rect down = { 180, 180, 40, 40 };
	SDL_RenderFillRect(_renderer, &down);

	SDL_RenderPresent(_renderer);
}

/**
 * @brief Affiche l'état actuel du jeu dans la fenêtre SDL.
 * 
 * Si le menu d'aide est activé (touche 'h'), cette fonction appelle
 * drawHelpMenu() pour afficher un écran dédié avec les touches directionnelles.
 * Sinon, elle affiche le jeu normalement :
 * - Serpent (vert)
 * - Nourriture (rouge)
 * - Score (blocs blancs)
 * - Obstacles (gris foncé)
 * 
 * Le rendu final est affiché avec SDL_RenderPresent().
 * 
 * @param state L'état actuel du jeu à afficher.
 */
void	GuiSDL::render(const GameState& state)
{
	if (state.isHelpMenuActive())
	{
		drawHelpMenu();
		return;
	}

	// 🎮 Affichage normal du jeu (quand le menu n'est pas actif)
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

	// Dessine les obstacles
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
	for (const Point& p : state.getObstacles())
	{
		SDL_Rect rect = { p.x * 20, p.y * 20, 20, 20 };
		SDL_RenderFillRect(_renderer, &rect);
	}

	// Affiche la frame finale
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
				case SDLK_h: 
					return Input::HELP; 
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
