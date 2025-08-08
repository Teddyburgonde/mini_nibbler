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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width * 20, height * 20, "Nibbler - OpenGL", NULL, NULL);
	if (!_window)
	{
		std::cerr << "❌ Failed to create OpenGL window!" << std::endl;
		glfwTerminate();
		exit(1);
	}

	// Rendre le contexte courant
	glfwMakeContextCurrent(_window);

	// Définir la zone de rendu (viewport)
	glViewport(0, 0, width * 20, height * 20);

	// Couleur de fond par défaut (noir)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	glColor3f(0.0f, 1.0f, 0.0f); // Vert
	for (const Point& p : state.getSnake().getBody())
	{
		float x = p.x * 20.0f;
		float y = p.y * 20.0f;
		
		// Dessine une forme a 4 côtés
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + 20.0f, y);
			glVertex2f(x + 20.0f, y + 20.0f);
			glVertex2f(x, y + 20.0f);
		glEnd();
	}

	// 🍎 Dessine la nourriture (rouge)
	Point food = state.getFood();
	float fx = food.x * 20.0f;
	float fy = food.y * 20.0f;

	glColor3f(1.0f, 0.0f, 0.0f); // Rouge
	glBegin(GL_QUADS);
		glVertex2f(fx, fy);
		glVertex2f(fx + 20.0f, fy);
		glVertex2f(fx + 20.0f, fy + 20.0f);
		glVertex2f(fx, fy + 20.0f);
	glEnd();

	// Affiche la frame à l'écran
	glfwSwapBuffers(_window);
}