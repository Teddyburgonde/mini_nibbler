#include "GameState.hpp"


GameState::GameState()
	: snake(5, 10), food(0, 0), _score(0), _finished(false)
{
	std::srand(std::time(nullptr)); // Initialisation pour la génération aléatoire
	generateFood();
}

GameState::GameState(const GameState& copy)
	: snake(copy.snake), food(copy.food), _score(copy._score), _finished(copy._finished)
{}

GameState& GameState::operator=(const GameState& copy)
{
	if (this != &copy)
	{
		snake = copy.snake;
		food = copy.food;
		_score = copy._score;
		_finished = copy._finished;
	}
	return *this;
}

GameState::~GameState() {}

const Snake& GameState::getSnake() const
{
	return snake;
}

const Point& GameState::getFood() const
{
	return food;
}

int GameState::getScore() const
{
	return _score;
}

bool GameState::isFinished() const
{
	return _finished;
}

void GameState::update()
{
	snake.move();

	// Si la tête touche la nourriture
	if (snake.getBody().front().x == food.x && snake.getBody().front().y == food.y)
	{
		snake.grow();
		increaseScore(10);
		generateFood();
	}

	if (_score >= 100)
		_finished = true;
}

void GameState::setDirection(Direction dir)
{
	snake.setDirection(dir);
}

void GameState::generateFood()
{
	int x = std::rand() % 78 + 1;  // éviter les bords
	int y = std::rand() % 22 + 1;
	food = Point(x, y);
}

void GameState::reset()
{
	snake = Snake(5, 10);
	_score = 0;
	_finished = false;
	generateFood();
}

void GameState::increaseScore(int amount)
{
	_score += amount;
}
