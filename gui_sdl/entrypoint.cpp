#include "GuiSDL.hpp"

/**
 * @brief Point d'entrée dynamique pour la GUI SDL.
 * Cette fonction est chargée dynamiquement via dlsym().
 * 
 * @return Un pointeur vers une nouvelle instance de GuiSDL.
 */
extern "C" IGui* createGui() 
{ 
	return new GuiSDL();
}