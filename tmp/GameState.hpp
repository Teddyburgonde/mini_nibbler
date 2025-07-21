gameState():
{
  
}
gameState::~gameState(){}
gameState::gameState(gameState const &cpy)
{
	*this = cpy;
}

gameState const & gameState::operator=(gameState const &rhs)
{
	(void)rhs;
    return *this;
}
