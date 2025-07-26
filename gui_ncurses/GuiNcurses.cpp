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
	curs_set(0);
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
 * @brief Récupère l'entrée clavier de l'utilisateur via ncurses.
 * 
 * Gère les touches suivantes :
 * - Flèches directionnelles (haut, bas, gauche, droite)
 * - Touche ESC ou 'q' pour quitter
 * - Touche '1', '2', '3' pour changer dynamiquement de GUI
 * 
 * @return Input Enum correspondant à l'action détectée.
 */
Input GuiNcurses::getInput()
{
	int key = getch();

	// Flèches directionnelles
	if (key == 27)
	{
		int second = getch();
		int third = getch();

		if (second == 91)
		{
			if (third == 65) return Input::UP;
			if (third == 66) return Input::DOWN;
			if (third == 67) return Input::RIGHT;
			if (third == 68) return Input::LEFT;
		}
		return Input::EXIT;
	}

	if (key == '1')
		return Input::SWITCH_TO_1;
	if (key == '2')
		return Input::SWITCH_TO_2;
	if (key == '3')
		return Input::SWITCH_TO_3;
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


/**
 * @brief Affiche une fenêtre popup indiquant que le joueur a perdu.
 * 
 * Cette fonction crée une petite fenêtre centrée à l'écran, avec un message
 * "GAME OVER". Elle attend que l'utilisateur appuie sur la touche 'q'
 * pour fermer proprement la fenêtre et continuer le nettoyage.
 */
void GuiNcurses::showGameOver()
{
	int winHeight = 5;
	int winWidth = 30;
	int startY = (_screenHeight - winHeight) / 2;
	int startX = (_screenWidth - winWidth) / 2;

	WINDOW* popup = newwin(winHeight, winWidth, startY, startX);
	box(popup, 0, 0); // Dessine un cadre
	mvwprintw(popup, 1, 10, "GAME OVER! 💀");
	mvwprintw(popup, 2, 5, "Press q to exit...");
	wrefresh(popup);

	// Attend q
	int ch;
	while ((ch = getch()) != 'q') {}

	delwin(popup);
}

/**
 * @brief Affiche une fenêtre popup de victoire.
 * 
 * Cette fonction crée une petite fenêtre centrée à l'écran, avec un message
 * "YOU WIN". Elle attend que l'utilisateur appuie sur la touche 'q'
 * pour fermer proprement la fenêtre avant de quitter le jeu.
 */
void GuiNcurses::showVictory()
{
	int winHeight = 5;
	int winWidth = 30;
	int startY = (_screenHeight - winHeight) / 2;
	int startX = (_screenWidth - winWidth) / 2;

	WINDOW* popup = newwin(winHeight, winWidth, startY, startX);
	box(popup, 0, 0); // Dessine un cadre
	mvwprintw(popup, 1, 10, "🎉 YOU WIN!");
	mvwprintw(popup, 2, 5, "Press q to exit...");
	wrefresh(popup);

	int ch;
	while ((ch = getch()) != 'q') {}

	delwin(popup);
}