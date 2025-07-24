#include "GuiNcurses.hpp"

/**
 * @brief Initialise la fenêtre ncurses et les paramètres d'affichage.
 * 
 * Configure la taille de l'écran, active la gestion des couleurs,
 * désactive l'affichage des touches tapées et cache le curseur.
 * Active aussi les touches directionnelles et la lecture non bloquante.
 *
 * @param width Largeur de la fenêtre de jeu.
 * @param height Hauteur de la fenêtre de jeu.
 */
void	GuiNcurses::init(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
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
	drawWalls(_screenWidth, _screenHeight);
	drawSnake(state.getSnake().getBody());
	drawFood(state.getFood());
	refresh();
}


/**
 * @brief Récupère l'entrée clavier de l'utilisateur.
 * 
 * Traduit les flèches directionnelles et les touches spécifiques
 * (ex: 'q' ou Échap) en valeurs de l'énumération Input.
 *
 * @return Input représentant la touche appuyée.
 */
Input GuiNcurses::getInput()
{
	int	key = getch();

	if (key == KEY_UP)
		return Input::UP;
	if (key == KEY_DOWN)
		return Input::DOWN;
	if (key == KEY_LEFT)
		return Input::LEFT;
	if (key == KEY_RIGHT)
		return Input::RIGHT;
	if (key == 'q' || key == 27)
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