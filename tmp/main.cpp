

// 3. Tu dessines chaque partie du snake

// 4. Tu dessines la nourriture

// 5. Tu rafraîchis avec refresh()


#include "draw.hpp"
#include <deque> // Ajout de l'en-tête deque

int	main()
{
	
	initscr(); // initialisation de la fênetre

	int width = 80; // largeur = colonne
	int height = 24; // longeur = ligne
	
	// 2. Tu dessines les murs
	drawWalls(width, height);

	std::deque<Point> snake; // Utilisation du namespace std

	// Initialisation correcte du snake avec des Points
	snake.push_back(Point(5,10));
	snake.push_back(Point(5,11));
	snake.push_back(Point(5,12));
	snake.push_back(Point(5,13));

	drawSnake(snake);

	refresh(); // rafraichi la fenetre. 
	
	getch(); // Attends qu'une touche soit préssée.

	endwin(); // Netoyage de la fenêtre
}