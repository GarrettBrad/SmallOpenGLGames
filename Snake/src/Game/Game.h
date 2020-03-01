#ifndef GAME_H
#define GAME_H

#include <deque>
#include "Window/Window.h"
#include "Window/Render.h"


class Game
{
private:


	std::deque<Snake> m_Snake = NewSnake();
	Fruit m_CurrentFruit = Fruit();

	Window m_Wnd = Window();
	
	bool m_ShouldClose = false;
	bool m_Moving = false;
	bool m_NewTailAlive = false;

	std::deque<Snake> NewSnake();

	void StartGame();
	void ResetGame();

	void NewFruit();

	void Move();
	void CheckInput();
	void CheckBoundry();
	void CheckColision();
public:
	int Init();

	inline bool ShouldClose() { return m_Wnd.ShouldClose() || m_ShouldClose; }

	void Run();

	
};


#endif /* GAME_H */