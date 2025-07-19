#include <iostream>
#include "Snake.hpp"

class Game
{
	public:
		Game();
		~Game();
		void	loop();
		void	generateRandomFoodPosition();

	private:
		Snake	snake;
		Point	food;
		bool	gameOver;
		int		width;
		int		height;
};



