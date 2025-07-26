#include "GuiNcurses.hpp"

extern "C" IGui* createGui() 
{ 
	return new GuiNcurses();
}