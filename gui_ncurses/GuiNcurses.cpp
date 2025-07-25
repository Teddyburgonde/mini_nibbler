#include "GuiNcurses.hpp"

/**
 * @brief Vérifie si le terminal est assez grand pour la fenêtre demandée.
 * 
 * Cette fonction compare les dimensions du terminal réel avec les dimensions
 * requises pour le jeu. Si le terminal est trop petit, le programme se ferme
 * proprement avec un message d'erreur explicite.
 *
 * @param requiredWidth Largeur minimale requise pour la fenêtre.
 * @param requiredHeight Hauteur minimale requise pour la fenêtre.
 */
void GuiNcurses::checkTerminalSize(int requiredWidth, int requiredHeight)
{
	int termHeight, termWidth;
	getmaxyx(stdscr, termHeight, termWidth);
	if (requiredHeight > termHeight || requiredWidth > termWidth)
	{
		endwin();
		std::cout << "❌ Terminal too small: resize to at least "
		          << requiredWidth << "x" << requiredHeight << std::endl;
		exit(1);
	}
}

/**
 * @brief Initialise la fenêtre ncurses et les paramètres d'affichage.
 * 
 * Cette fonction configure l'affichage du terminal pour le jeu Snake.
 * Elle vérifie la taille du terminal, désactive l'écho clavier, active
 * les couleurs, la lecture non bloquante, et initialise les paires de couleurs.
 *
 * @param width Largeur de la zone de jeu.
 * @param height Hauteur de la zone de jeu.
 */
void GuiNcurses::init(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;

	WINDOW* win = initscr();
	refresh();
	if (win == nullptr)
	{
		std::cout << "initscr() failed!" << std::endl;
		return;
	}
	checkTerminalSize(width, height); 
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
 * Cette fonction intercepte les séquences de touches pour détecter :
 * - Les flèches directionnelles (haut, bas, gauche, droite) via les séquences ESC [ A/B/C/D
 * - La touche 'q' ou la touche Échap seule pour quitter le jeu
 * 
 * Les flèches sont reconnues en lisant les trois codes successifs :
 * - 27 : ESC
 * - 91 : [
 * - 65–68 : A (haut), B (bas), C (droite), D (gauche)
 *
 * @return Input Enum représentant la direction ou une commande spéciale.
 */
Input GuiNcurses::getInput()
{
	int key = getch();
	if (key == 27)
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
		return Input::EXIT;
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