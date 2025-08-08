#include "GuiOpenGL.hpp"
#include <iostream>

/**
 * @brief Initialise la fenêtre et le contexte OpenGL avec GLFW.
 * 
 * Cette fonction configure la largeur/hauteur de l’affichage,
 * initialise GLFW, crée une fenêtre avec contexte OpenGL,
 * et définit les paramètres OpenGL de base (viewport, couleur de fond).
 *
 * @param width  Largeur en cases du plateau de jeu.
 * @param height Hauteur en cases du plateau de jeu.
 */
void GuiOpenGL::init(int width, int height)
{
	_screenWidth = width;
	_screenHeight = height;

	if (!glfwInit())
	{
		std::cerr << "❌ GLFW init failed!" << std::endl;
		exit(1);
	}

	// Paramètres OpenGL (version 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	_window = glfwCreateWindow(width * 20, height * 20, "Nibbler - OpenGL", NULL, NULL);
	if (!_window)
	{
		std::cerr << "❌ Failed to create OpenGL window!" << std::endl;
		glfwTerminate();
		exit(1);
	}

	// Rendre le contexte courant
	glfwMakeContextCurrent(_window);

	glfwSwapInterval(1); 

	// Définir la zone de rendu (viewport)
	glViewport(0, 0, width * 20, height * 20);

	// Couleur de fond par défaut (noir)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width * 20, height * 20, 0, -1, 1); // coord écran 2D classique (origine en haut à gauche)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * @brief Affiche l'état actuel du jeu à l'écran avec OpenGL.
 * 
 * Cette fonction utilise OpenGL pour :
 * - effacer l'écran et définir la couleur de fond (noir)
 * - dessiner le serpent en vert, case par case
 * - dessiner la nourriture en rouge
 * 
 * Chaque case logique du jeu est représentée par un carré de 20x20 pixels.
 * Le tout est affiché à l'écran en fin de fonction via glfwSwapBuffers().
 * 
 * @param state Référence vers l'état actuel du jeu (serpent, nourriture, etc.).
 */
void GuiOpenGL::render(const GameState& state)
{
	// Efface l'écran avec la couleur de fond (noir)
	glClear(GL_COLOR_BUFFER_BIT);

	// Dessine le serpent (vert)
	glColor3f(0.0f, 0.8f, 1.0f); // Bleu cyan
	for (const Point& p : state.getSnake().getBody())
	{
		float x = p.x * 20.0f;
		float y = p.y * 20.0f;
		
		// Dessine une forme a 4 côtés (juste les points)
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + 20.0f, y);
			glVertex2f(x + 20.0f, y + 20.0f);
			glVertex2f(x, y + 20.0f);
		glEnd();
	}

	// Dessine la nourriture (rouge)
	Point food = state.getFood();
	float fx = food.x * 20.0f;
	float fy = food.y * 20.0f;

	glColor3f(1.0f, 0.6f, 0.0f); // Orange clair
	glBegin(GL_QUADS);
		glVertex2f(fx, fy);
		glVertex2f(fx + 20.0f, fy);
		glVertex2f(fx + 20.0f, fy + 20.0f);
		glVertex2f(fx, fy + 20.0f);
	glEnd();

	// Dessine le score en blocs blancs
	int score = state.getScore();
	int nbBlocks = score / 10;

	glColor3f(1.0f, 1.0f, 1.0f); // blanc

	for (int i = 0; i < nbBlocks; ++i)
	{
		float x = 10.0f + i * 25.0f;
		float y = 10.0f;
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + 20.0f, y);
			glVertex2f(x + 20.0f, y + 20.0f);
			glVertex2f(x, y + 20.0f);
		glEnd();
	}

	// Affiche la frame à l'écran
	glfwSwapBuffers(_window);

}


/**
 * @brief Gère les entrées clavier via GLFW (OpenGL).
 * 
 * Utilise glfwPollEvents() pour détecter :
 * - les flèches directionnelles
 * - les touches '1', '2', '3' pour changer de GUI
 * - les touches 'q' ou Échap pour quitter
 * 
 * @return Input La direction ou l'action détectée par l'utilisateur.
 */
Input GuiOpenGL::getInput()
{
    glfwPollEvents();

    if (glfwWindowShouldClose(_window))
        return Input::EXIT;

    if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
        return Input::UP;
    if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        return Input::DOWN;
    if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
        return Input::LEFT;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        return Input::RIGHT;

    if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS)
        return Input::SWITCH_TO_1;
    if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS)
        return Input::SWITCH_TO_2;
    if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS)
        return Input::SWITCH_TO_3;

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
        return Input::EXIT;

    return Input::NONE;
}

/**
 * @brief Libère les ressources GLFW et réinitialise le terminal.
 * 
 * Détruit la fenêtre GLFW si elle existe, termine GLFW et
 * restaure l'état du terminal avec la commande `stty sane`.
 */
void GuiOpenGL::cleanup()
{
	if (_window)
		glfwDestroyWindow(_window);
	glfwTerminate();
	system("stty sane");
}

/**
 * @brief Affiche une boîte de dialogue système indiquant la victoire (OpenGL).
 * 
 * Utilise la commande système `zenity` pour afficher une fenêtre "You won!".
 */
void GuiOpenGL::showVictory()
{
	system("zenity --info --text='🎉 You won!' --title='Victory'");
}

/**
 * @brief Affiche une boîte de dialogue système indiquant la défaite (OpenGL).
 * 
 * Utilise la commande système `zenity` pour afficher une fenêtre "You lost!".
 */
void GuiOpenGL::showGameOver()
{
	system("zenity --error --text='💀 You lost...' --title='Defeat'");
}
