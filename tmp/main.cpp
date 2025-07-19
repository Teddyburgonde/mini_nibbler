

// 3. Tu dessines chaque partie du snake

// 4. Tu dessines la nourriture

// 5. Tu rafraîchis avec refresh()


#include "draw.hpp"

int	main()
{
	
	initscr(); // initialisation de la fênetre

	int width = 80; // largeur = colonne
	int height = 24; // longeur = ligne
	
	// 2. Tu dessines les murs
	drawWalls(width, height);

	
	refresh(); // rafraichi la fenetre. 
	
	getch(); // Attends qu'une touche soit préssée.

	endwin(); // Netoyage de la fenêtre
}