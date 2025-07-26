#include "GuiNcurses.hpp"

/**
 * @brief Point d'entrée utilisé par dlsym() pour créer dynamiquement l'objet GUI.
 *
 * Cette fonction est exportée sans nom mangling grâce à `extern "C"`,
 * ce qui permet à `dlsym()` de la retrouver dans la bibliothèque partagée (.so).
 *
 * @return Un pointeur vers un objet GuiNcurses qui implémente l'interface IGui.
 */
extern "C" IGui* createGui() 
{ 
	return new GuiNcurses();
}