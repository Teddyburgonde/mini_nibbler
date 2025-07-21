#pragma once

#include "Snake.hpp"
#include <cstdlib>
#include <ctime>

class GameState {
	
	public:
		GameState();
		GameState(const GameState& copy);
		GameState& operator=(const GameState& copy);
		~GameState();

		const Snake& getSnake() const;
		const Point& getFood() const;
		int getScore() const;
		bool isFinished() const;

		void update();
		void setDirection(Direction dir);
		void generateFood();
		void reset();
		void increaseScore(int amount);

	private:
		Snake snake;
		Point food;
		int _score;
		bool _finished;
};