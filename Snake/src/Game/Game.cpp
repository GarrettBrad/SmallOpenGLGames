#include <thread>
#include <chrono> 
#include <random>

#include "Game.h"

// Inits the window class and creates the window : Also creates the fruit pos on screen
int Game::Init()
{
	int InitWndResult = m_Wnd.Init();

	if (InitWndResult) return -1;

	GLFWwindow* CreateWndResult = m_Wnd.CreateWindow();

	if (!CreateWndResult) return -1;

	glfwMakeContextCurrent(CreateWndResult);

	NewFruit();

	return 0;
}

// Creates a new defualt snake
std::deque<Snake> Game::NewSnake()
{
	return std::deque<Snake> {
		{ 370, 370, Direction::Up, true },
		{ 370, 370 - ((SNAKE_SIZE * 2) * 1), Direction::Up, false },
		{ 370, 370 - ((SNAKE_SIZE * 2) * 2), Direction::Up, false },
		{ 370, 370 - ((SNAKE_SIZE * 2) * 3), Direction::Up, false },
		{ 370, 370 - ((SNAKE_SIZE * 2) * 4), Direction::Up, false } // 5 Snake Pieces
	};
}

// Moves the snake parts by there direction value And does the direction logic for the next snake peices
void Game::Move()
{

	// We loop backwards for changine dir
	for (signed int i = m_Snake.size() - 1; i > -1; i--)
	{
		if (m_Snake[i].dir == Direction::Up)
			m_Snake[i].Y += SNAKE_MOVE_SPEED;
		else if (m_Snake[i].dir == Direction::Down)
			m_Snake[i].Y -= SNAKE_MOVE_SPEED;
		else if (m_Snake[i].dir == Direction::Right)
			m_Snake[i].X += SNAKE_MOVE_SPEED;
		else if (m_Snake[i].dir == Direction::Left)
			m_Snake[i].X -= SNAKE_MOVE_SPEED;

		if (i == 0) continue;

		m_Snake[i].dir = m_Snake[i - 1].dir;
	}

}

// Checks player input
void Game::CheckInput()
{
	GLFWwindow* wnd = m_Wnd.GetWindow();

	// Basic up and own movement with direction checking
	if (glfwGetKey(wnd, GLFW_KEY_UP) && m_Snake[0].dir != Direction::Down)
		m_Snake[0].dir = Direction::Up;
	if (glfwGetKey(wnd, GLFW_KEY_DOWN) && m_Snake[0].dir != Direction::Up)
		m_Snake[0].dir = Direction::Down;
	if (glfwGetKey(wnd, GLFW_KEY_LEFT) && m_Snake[0].dir != Direction::Right)
		m_Snake[0].dir = Direction::Left;
	if (glfwGetKey(wnd, GLFW_KEY_RIGHT) && m_Snake[0].dir != Direction::Left)
		m_Snake[0].dir = Direction::Right;

	// Space starts the game
	if (glfwGetKey(wnd, GLFW_KEY_SPACE))
		StartGame();

	// End Game
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE))
		m_ShouldClose = true;
}

// Starts the game from the starting state
void Game::StartGame()
{
	// Not sure if i want to add more yet
	m_Moving = true;
}

// Resets the game to the starting state
void Game::ResetGame()
{
	m_Moving = false;

	// Clears the old snake
	m_Snake.clear();

	m_Snake = NewSnake();
	
	NewFruit();
}

// Checks End Boundry
void Game::CheckBoundry()
{
	if (m_Snake[0].X < 0)
		ResetGame(); // End the game
	else if (m_Snake[0].X > SNAKE_WND_WIDHT)
		ResetGame();
	else if (m_Snake[0].Y < 0)
		ResetGame();
	else if (m_Snake[0].Y > SNAKE_WND_HEIGHT)
		ResetGame();
}

// Checks colision with the snake
void Game::CheckColision()
{
	// Checks colision with the fruit

	if (m_Snake[0] == m_CurrentFruit)
	{
		Snake& EndSnake = m_Snake[m_Snake.size() - 1];

		// Adds the fruit to the end of the fruit
		if (EndSnake.dir == Direction::Up)
		{
			m_Snake.push_back({ EndSnake.X,
					EndSnake.Y - SNAKE_MOVE_SPEED,
					EndSnake.dir,
					false
				});
		}
		else if (EndSnake.dir == Direction::Down)
		{
			m_Snake.push_back({ EndSnake.X,
					EndSnake.Y + SNAKE_MOVE_SPEED,
					EndSnake.dir,
					false
				});
		}
		else if (EndSnake.dir == Direction::Right)
		{
			m_Snake.push_back({ EndSnake.X - SNAKE_MOVE_SPEED,
					EndSnake.Y,
					EndSnake.dir,
					false
				});
		}
		else if (EndSnake.dir == Direction::Left)
		{
			m_Snake.push_back({ EndSnake.X + SNAKE_MOVE_SPEED,
					EndSnake.Y,
					EndSnake.dir,
					false
				});
		}

		// Put the fruit somewhere else
		NewFruit();
	}


	// Checks if the snake hit its self
	for (const auto& snake : m_Snake)
	{
		// Is the snake the snake head
		if (snake.FirstObject) continue;

		// If the Snake Pos is == to the head of the snake
		if (snake == m_Snake[0])
			ResetGame();
	}
}

// Adds a new peice of fruit to the board
void Game::NewFruit()
{
	/*
	We can't have the new fruit at 112 and 113 because the snake had move at 10 pixel intervals so it would never
	come accross that. so we instead we get 11 as a radom number and times it by SNAKE_MOVE_SPEED to get 110
	which the head could cross. -- I don't know engrish
	*/
	int MaxX = (SNAKE_WND_WIDHT / SNAKE_MOVE_SPEED) - SNAKE_MOVE_SPEED; // the - SNAKE_MOVE_SPEED is so it won't
	int MaxY = (SNAKE_WND_HEIGHT / SNAKE_MOVE_SPEED) - SNAKE_MOVE_SPEED; // be outside the window

	srand((unsigned int) time(NULL));

	int FruitXPoint = (rand() % MaxX) + 1;
	int FruitYPoint = (rand() % MaxY) + 1;
	
	m_CurrentFruit.X = FruitXPoint * SNAKE_MOVE_SPEED;
	m_CurrentFruit.Y = FruitYPoint * SNAKE_MOVE_SPEED;
}

// Runs the games
void Game::Run()
{
	std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();

	// Stop the game from running to fast. around 20 frames a second... I was close to 500 with out this
	time += std::chrono::milliseconds(75);

	m_Wnd.StartRender();

	Render::DrawSnake(m_Snake);
	Render::DrawFruit(m_CurrentFruit);

	if (m_Moving)
	{
		Move();
		CheckBoundry();
		CheckColision();
	}

	CheckInput();

	m_Wnd.EndRender();

	// Makes sure the game didn't take to long running
	if (time > std::chrono::system_clock::now())
		std::this_thread::sleep_until(time);
}
