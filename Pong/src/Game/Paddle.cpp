#include "Paddle.h"

// Gets the player number of the paddle : NOT USED HERE FOR OLD DEBUGGING
const PlayerNumber& Paddle::GetPlayerNumber() const
{
	return this->m_PlayerNumber;
}

// Moves the paddle in the given direction
void Paddle::Move(Direction dir)
{
	if (dir == Direction::UP && (this->m_Y + c_Height) < 1.0f) // Bound Checking
		this->m_Y += c_MoveSpeed;
	else if (dir == Direction::DOWN && (this->m_Y - c_Height) > -1.0f) // Bound Checking
		this->m_Y -= c_MoveSpeed;
	else if (dir == Direction::AI_UP && (this->m_Y + c_Height) < 1.0f)
		this->m_Y += c_AIMoveSpeed;
	else if (dir == Direction::AI_DOWN && (this->m_Y - c_Height) > -1.0f)
		this->m_Y -= c_AIMoveSpeed;
}

Paddle::Paddle(PlayerNumber PNum)
	: m_X(0), m_Y(0), m_PlayerNumber(PNum)
{
	// Sets x Based on player numnber

	if (PNum == PlayerNumber::ONE)
	{
		this->m_X = -0.85f; // X Pos of Player 1
	}
	else // Player two
	{
		this->m_X = 0.85f; // X Pos of player 2
	}
}

Paddle::~Paddle()
{ /* Clean up */ }
