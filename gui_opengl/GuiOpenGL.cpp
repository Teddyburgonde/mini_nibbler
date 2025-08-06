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
