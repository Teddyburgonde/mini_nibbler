/**
 * @file GuiNcurses.cpp
 * @brief Implémentation de la classe GuiNcurses pour le rendu graphique en mode texte
 *
 * Ce fichier contient les méthodes pour initialiser l'interface Ncurses,
 * dessiner le jeu (serpent, nourriture, score, obstacles), gérer les entrées utilisateur,
 * et afficher les messages de fin de jeu (victoire, défaite).
 */

#include "GuiNcurses.hpp"
#include <iostream> // pour std::cout utilisé dans checkTerminalSize


/**
 * @brief Constructeur par défaut de GuiNcurses.
 *
 * Initialise les dimensions de l'écran à 0.
 */
GuiNcurses::GuiNcurses()
	: _screenWidth(0), _screenHeight(0)
{}

/**
 * @brief Constructeur de copie pour GuiNcurses.
 *
 * Copie les dimensions de l'écran depuis un autre objet GuiNcurses.
 *
 * @param other L'objet GuiNcurses à copier.
 */
GuiNcurses::GuiNcurses(const GuiNcurses& other)
	: _screenWidth(other._screenWidth), _screenHeight(other._screenHeight)
{}

/**
 * @brief Opérateur d'affectation pour GuiNcurses.
 *
 * Permet de copier les dimensions de l'écran depuis un autre objet GuiNcurses.
 *
 * @param other L'objet GuiNcurses à copier.
 * @return Référence à l'objet courant.
 */
GuiNcurses& GuiNcurses::operator=(const GuiNcurses& other)
{
	if (this != &other)
	{
		_screenWidth  = other._screenWidth;
		_screenHeight = other._screenHeight;
	}
	return *this;
}

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
		throw std::runtime_error("Terminal too small");
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
		throw std::runtime_error("Failed to initialize terminal");
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
 * @brief Dessine les obstacles du jeu.
 *
 * Cette fonction dessine les obstacles en utilisant des caractères spéciaux.
 *
 * @param obstacles Vecteur de points représentant les positions des obstacles.
 */
void GuiNcurses::drawObstacles(const std::vector<Point>& obstacles)
{
	for (const Point& p : obstacles)
	{
		mvaddch(p.y, p.x, 'Z'); // caractère obstacle
	}
}


/**
 * @brief Affiche l'état du jeu ou le menu d'aide à l'écran avec Ncurses.
 * 
 * Si le menu d'aide est actif, affiche une liste des touches disponibles
 * pour contrôler le jeu, et met automatiquement la partie en pause.
 * Sinon, dessine l'état de la partie : le score, les murs, le serpent,
 * la nourriture et les obstacles.
 * 
 * @param state État actuel du jeu (serpent, score, menu actif, etc.).
 */
void	GuiNcurses::render(const GameState& state)
{
	if (state.isHelpMenuActive())
	{
		clear();

		mvprintw(2, 5, "CONTROLES");
		mvprintw(4, 7, "[FLECHE DU HAUT] : Monter");
		mvprintw(5, 7, "[FLECHE DU BAS] : Descendre");
		mvprintw(6, 7, "[FLECHE DE GAUCHE]  : Gauche");
		mvprintw(7, 7, "[FLECHE DE DROITE] : Droite");
		mvprintw(8, 7, "h    : Afficher / Cacher ce menu");
		mvprintw(9, 7, "esc / q : Quitter");
		mvprintw(11, 5, "Appuyez sur 'h' pour reprendre la partie...");
		if (refresh() == ERR) {
			throw std::runtime_error("Failed to refresh ncurses window");
		}
		return;
	}
	clear();
	mvprintw(1, 2, "Score: %d", state.getScore());
	drawWalls(_screenWidth, _screenHeight);
	drawSnake(state.getSnake().getBody());
	drawFood(state.getFood());
	drawObstacles(state.getObstacles());
	if (refresh() == ERR) {
		throw std::runtime_error("Failed to refresh ncurses window");
	}
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
	if (key == '1')
		return Input::SWITCH_TO_1;
	if (key == '2')
		return Input::SWITCH_TO_2;
	if (key == '3')
		return Input::SWITCH_TO_3;
	if (key == 'q')
		return Input::EXIT;
	if (key == 'h' || key == 'H')
		return Input::HELP;
	return Input::NONE;
}

/**
 * @brief Ferme proprement ncurses et restaure le terminal.
 */
void	GuiNcurses::cleanup()
{
	auto ret = endwin();
	if (ret == ERR) {
		throw std::runtime_error("Failed to end ncurses mode");
	}

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
	mvwprintw(popup, 1, 10, "GAME OVER!");
	mvwprintw(popup, 2, 5, "Press q to exit...");
	wrefresh(popup);

	// Attend q
	int ch;
	while ((ch = getch()) != 'q') {}

	if (delwin(popup) == ERR) {
		throw std::runtime_error("Failed to delete popup window");
	}
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
	mvwprintw(popup, 1, 10, "YOU WIN!");
	mvwprintw(popup, 2, 5, "Press q to exit...");
	wrefresh(popup);

	int ch;
	while ((ch = getch()) != 'q') {}

	if (delwin(popup) == ERR) {
		throw std::runtime_error("Failed to delete popup window");
	}
}
