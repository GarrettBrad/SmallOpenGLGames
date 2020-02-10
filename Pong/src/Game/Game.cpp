#include "Game.h"

#include <iostream>
#include <string>

// Inits GLFW and creates a window
int Game::Init()
{
	int result = m_Wnd.Init();

	if (result) return result;

	GLFWwindow* WndResult = m_Wnd.CreateWindow();

	if (!WndResult) return -2;

	glfwMakeContextCurrent(WndResult);

	return 0;
}

// returns true if the application should close
int Game::ShouldClose()
{
	if (m_Close) return true;

	return m_Wnd.ShouldClose();
}

// Runs the game logic and rendering : CALLED EVERY FRAME
void Game::Run()
{
	this->CheckInput();

	this->GameLogic();

	m_Wnd.StartRender();

	// Draws Pong
	render.RenderPaddle(m_PlayerOne);
	render.RenderPaddle(m_PlayerTwo);
	render.RenderBall(m_Ball);

	m_Wnd.EndRender();

}

// Checks player input : CALLED EVERY FRAME
void Game::CheckInput(void)
{
	auto* wnd = glfwGetCurrentContext(); // Gets the current window 

	// The Ai takes over w and s if the player count is only 1
	if (this->m_NumOfPlayers > 1)
	{
		if (glfwGetKey(wnd, GLFW_KEY_W))
			m_PlayerOne.Move(Direction::UP);
		if (glfwGetKey(wnd, GLFW_KEY_S))
			m_PlayerOne.Move(Direction::DOWN);
	}

	if (glfwGetKey(wnd, GLFW_KEY_UP))
		m_PlayerTwo.Move(Direction::UP);
	if (glfwGetKey(wnd, GLFW_KEY_DOWN))
		m_PlayerTwo.Move(Direction::DOWN);

	// Hold space for more speed
	if (glfwGetKey(wnd, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Ball.Start(); // Start Game

	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE)) {
		glfwTerminate();
		this->m_Close = true;
	}
}

void Game::AILogic()
{
	if (m_Ball.GetXSpeed() > 0)
	{
		if (m_PlayerOne.GetY() > 0)
			m_PlayerOne.Move(Direction::DOWN);
		if (m_PlayerOne.GetY() < 0)
			m_PlayerOne.Move(Direction::UP);
	}
	else
	{
		if (m_PlayerOne.GetY() > m_Ball.GetY())
			m_PlayerOne.Move(Direction::AI_DOWN);
		if (m_PlayerOne.GetY() < m_Ball.GetY())
			m_PlayerOne.Move(Direction::AI_UP);
	}
}

// Runs Every Frame : Runs the game logic such as moving the ball and checking colison
void Game::GameLogic()
{
	m_Ball.Move();

	if (m_NumOfPlayers == 1)
		AILogic();

	this->CheckColison();
}

// Checks for Colision with paddles and handles it
void Game::ColisionHandle(const Paddle& player)
{
	// Checks the colision and handles it
	if (this->CheckXColison(player) && this->CheckYColison(player))
	{
		// Checks that we haven't already switched the direction

		if (player.GetPlayerNumber() == PlayerNumber::ONE)
		{
			if (m_Ball.GetXSpeed() < 0) {
				m_Ball.SwapXDirection();

				m_Ball.ChangeSpeed(m_Ball.GetX(), player.GetX());
			}
		}
		else {
			if (m_Ball.GetXSpeed() > 0) {
				m_Ball.SwapXDirection();

				m_Ball.ChangeSpeed(m_Ball.GetX(), player.GetX());
			}
		}
	}
}

// Checks if the Ball is hiting the paddle in the y cord
bool Game::CheckYColison(const Paddle& player)
{
	// Is the top part of the ball higher than the lower part of the paddle
	if ((m_Ball.GetY() + m_Ball.c_Radius) > player.GetY() - player.c_Height)
		// Is the lower part of the ball lower than the highest part of the paddle
		return ((m_Ball.GetY() - m_Ball.c_Radius) < player.GetY() + player.c_Height);

	return false;
}

// Checks if the Ball is hiting the paddle in the x cord
bool Game::CheckXColison(const Paddle& player)
{

	// is the left side of ball left to the Right side of paddle
	if (m_Ball.GetX() - m_Ball.c_Radius < player.GetX() + player.c_Width)
	{
		// is the Right side of ball right to the left side of paddle
		return (m_Ball.GetX() + m_Ball.c_Radius > player.GetX() - player.c_Width);
	}

	return false;
}

// Checks the ball with paddles and the edges
void Game::CheckColison()
{
	// Checks the balls colison with the paddles
	ColisionHandle(m_PlayerOne);
	ColisionHandle(m_PlayerTwo);

	if ((m_Ball.GetY() + m_Ball.c_Radius) > 1.0f)
		m_Ball.SwapYDirection();
	else if ((m_Ball.GetY() - m_Ball.c_Radius) < -1.0f)
		m_Ball.SwapYDirection();


	if (((m_Ball.GetX() - m_Ball.c_Radius) > 1.0f) || ((m_Ball.GetX() + m_Ball.c_Radius) < -1.0f))
		m_Ball.Reset();	
}

void Game::PlayerSelect()
{

	std::cout << "How many players. One or two?" << std::endl;

	std::cin >> m_NumOfPlayers;

	if (m_NumOfPlayers > 0 && m_NumOfPlayers < 3) return;

	while (true)
	{
		std::cout << "That is not a valid input.\nInput he number of players please." << std::endl;

		std::cin >> m_NumOfPlayers;

		if (m_NumOfPlayers > 0 && m_NumOfPlayers < 3) return;
	}

}

Game::Game()
{
}
