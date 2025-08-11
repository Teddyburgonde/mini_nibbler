/**
 * @file entrypoint.cpp
 * @brief Point d'entrée pour la GUI SDL.
 *
 * Ce fichier contient la fonction d'entrée pour la bibliothèque GUI SDL,
 * permettant de créer une instance de GuiSDL.
 */

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