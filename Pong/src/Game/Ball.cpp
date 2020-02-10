#include "Ball.h"

// Sets the speed of the ball from 0 to 0.02
void Ball::Start()
{
	this->m_XSpeed += c_InitSpeed;
	this->m_YSpeed += c_InitSpeed;
}

// Moves the ball by its speed
void Ball::Move()
{
	this->m_X += m_XSpeed;
	this->m_Y += m_YSpeed;
}

// Changes the ball from left to going right and vis versa
void Ball::SwapXDirection()
{
	this->m_XSpeed *= -1.0f;
	
	// Gets faster with each hit
	if (this->m_XSpeed > 0)
		this->m_XSpeed += 0.001f;
	else
		this->m_XSpeed -= 0.001f;

}

// Changes the ball from going up to going down
void Ball::SwapYDirection()
{
	this->m_YSpeed *= -1.0f;
}

// increases the y speed
void Ball::ChangeSpeed(const float& ballPos, const float& PaddlePos)
{
	// doesn't change the direction

	float newSpeed = (ballPos - PaddlePos) / 10;

	if (m_YSpeed > 0)
		m_YSpeed += newSpeed;
	else if (m_YSpeed < 0)
		m_YSpeed -= newSpeed;


	if (m_YSpeed > c_MaxSpeed) m_YSpeed = c_MaxSpeed;
}

// Resets the ball to the starting position
void Ball::Reset()
{
	this->m_X = 0.0f;
	this->m_Y = 0.0f;

	this->m_XSpeed = 0.0f;
	this->m_YSpeed = 0.0f;
}