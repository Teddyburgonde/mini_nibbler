#include "GameState.hpp"

/**
 * @brief Constructeur par défaut du GameState.
 * Initialise le snake, la nourriture, le score et l'état du jeu.
 */
GameState::GameState(int width, int height)
	: snake(width / 2, height / 2),
	  food(),
	  _score(0),
	  finished(false),
	  _width(width),
	  _height(height)
{
	std::srand(std::time(nullptr));
	generateFood();
}

/**
 * @brief Constructeur de copie.
 * @param copy L'autre GameState à copier.
 */
GameState::GameState(const GameState& copy)
	: snake(copy.snake), food(copy.food),
	  _score(copy._score), finished(copy.finished),
	  _width(copy._width), _height(copy._height)
{}

/**
 * @brief Opérateur d'affectation.
 * @param copy L'autre GameState à copier.
 * @return Référence vers l'instance actuelle.
 */
GameState& GameState::operator=(const GameState& copy)
{
	if (this != &copy)
	{
		snake = copy.snake;
		food = copy.food;
		_score = copy._score;
		finished = copy.finished;
		_width = copy._width;
		_height = copy._height;
	}
	return *this;
}

/**
 * @brief Destructeur de GameState.
 */
GameState::~GameState() {}


/**
 * @brief Accès au snake actuel.
 * @return Référence constante vers le snake.
 */
const Snake& GameState::getSnake() const
{
	return snake;
}

/**
 * @brief Accès à la position de la nourriture.
 * @return Référence constante vers l'objet Point représentant la nourriture.
 */
const Point& GameState::getFood() const
{
	return food;
}

/**
 * @brief Accès au score actuel.
 * @return Le score en cours.
 */
int GameState::getScore() const
{
	return _score;
}

/**
 * @brief Indique si la partie est terminée.
 * @return true si terminée, false sinon.
 */
bool GameState::isFinished() const
{
	return finished;
}

/**
 * @brief Met à jour l'état du jeu : déplace le snake, vérifie collisions et score.
 */
void GameState::update()
{
	snake.move();

	Point head = snake.getBody().front();

	// Collision mur
	if (head.x <= 0 || head.x >= _width - 1 || head.y <= 0 || head.y >= _height - 1)
	{
		finished = true;
		return;
	}

	// Collision avec soi-même
	if (snake.checkCollision(head, true))
	{
		finished = true;
		return;
	}

	if (snake.getBody().front().x == food.x && snake.getBody().front().y == food.y)
	{
		snake.grow();
		increaseScore(10);
		generateFood();
	}
	if (_score >= 50)
		finished = true;
}

/**
 * @brief Modifie la direction du snake en fonction de l'input utilisateur.
 * @param input Direction souhaitée (enum Input).
 */
void GameState::setDirection(Input input)
{
	switch (input)
	{
		case Input::UP:
			snake.setDirection(Direction::UP);
			break;
		case Input::DOWN:
		 	snake.setDirection(Direction::DOWN);
			break;
		case Input::LEFT: 
			snake.setDirection(Direction::LEFT);
			break;
		case Input::RIGHT: 
			snake.setDirection(Direction::RIGHT); 
			break;
		default: break;
	}
}

/**
 * @brief Génère une nouvelle position aléatoire pour la nourriture.
 */
void GameState::generateFood()
{
	int x = 1 + std::rand() % (_width - 2);
	int y = 1 + std::rand() % (_height - 2);
	food = Point(x, y);
}


/**
 * @brief Réinitialise le jeu : snake, score, état, et nourriture.
 */
void GameState::reset()
{
	snake = Snake(5, 10);
	_score = 0;
	finished = false;
	generateFood();
}

/**
 * @brief Augmente le score d'un certain montant.
 * @param amount Le montant à ajouter au score actuel.
 */
void GameState::increaseScore(int amount)
{
	_score += amount;
}
