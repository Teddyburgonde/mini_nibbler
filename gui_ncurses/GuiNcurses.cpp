#include "GuiNcurses.hpp"

/**
 * @brief Initialise la fenêtre ncurses sans dépendre de keypad() ni curs_set().
 * 
 * Configure l'affichage pour un fonctionnement non bloquant,
 * sans echo clavier, et active les couleurs pour le rendu.
 * Cette version est compatible avec les environnements où keypad()
 * ou curs_set() provoquent des blocages ou des crashs.
 *
 * @param width Largeur de l'écran de jeu.
 * @param height Hauteur de l'écran de jeu.
 */
// void	GuiNcurses::init(int width, int height)
// {
// 	_screenWidth = width;
// 	_screenHeight = height;

// 	WINDOW* win = initscr();
// 	if (win == nullptr)
// 	{
// 		std::cout << "initscr() failed!" << std::endl;
// 		return;
// 	}
// 	noecho();                  // Ne pas afficher les caractères tapés
// 	nodelay(stdscr, TRUE);     // getch() devient non bloquant
// 	cbreak();                  // Lecture directe sans attendre ENTER
// 	start_color();             // Active les couleurs
// 	init_pair(1, COLOR_GREEN, COLOR_BLACK);
// 	init_pair(2, COLOR_RED, COLOR_BLACK);
// }


void GuiNcurses::init(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;

	WINDOW* win = initscr();
	if (win == nullptr)
	{
		std::cout << "initscr() failed!" << std::endl;
		return;
	}

	// Vérification réelle de la taille ici
	int termHeight, termWidth;
	getmaxyx(stdscr, termHeight, termWidth);
	if (height > termHeight || width > termWidth)
	{
		endwin();
		std::cout << "❌ Terminal too small: resize to at least "
		          << width << "x" << height << std::endl;
		exit(1);
	}

	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
}

/**
 * @brief Dessine tous les éléments du jeu à l'écran.
 * 
 * Appelle les fonctions utilitaires pour dessiner les murs,
 * le serpent et la nourriture, puis rafraîchit l'affichage.
 *
 * @param state État actuel du jeu.
 */
void	GuiNcurses::render(const GameState& state)
{
	clear();
	drawWalls(_screenWidth, _screenHeight);
	drawSnake(state.getSnake().getBody());
	drawFood(state.getFood());
	refresh();
}


/**
 * @brief Récupère l'entrée clavier de l'utilisateur sans utiliser keypad().
 * 
 * Détecte manuellement les séquences de touches pour reconnaître les
 * flèches directionnelles (via les codes ESC [ A, etc.). Gère aussi
 * les touches 'q' et Échap pour quitter le jeu.
 *
 * @return Input représentant la direction ou l'action de l'utilisateur.
 */
Input GuiNcurses::getInput()
{
	int key = getch();
	if (key == 27) // Séquence d'échappement : flèche ?
	{
		int second = getch();
		int third = getch();

		if (second == 91)
		{
			if (third == 65)
				return Input::UP;
			if (third == 66)
				return Input::DOWN;
			if (third == 67)
				return Input::RIGHT;
			if (third == 68)
				return Input::LEFT;
		}
		return Input::EXIT; // touche ESC seule
	}
	if (key == 'q')
		return Input::EXIT;
	return Input::NONE;
}

/**
 * @brief Ferme proprement ncurses et restaure le terminal.
 */
void	GuiNcurses::cleanup()
{
	endwin();
}