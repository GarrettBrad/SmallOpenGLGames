#ifndef GAME_H
#define GAME_H

#include "Window/Render.h"
#include "Window/Window.h"

class Game
{
private:

	Paddle m_PlayerOne = Paddle(PlayerNumber::ONE);
	Paddle m_PlayerTwo = Paddle(PlayerNumber::TWO);

	Ball m_Ball = Ball();

	Window m_Wnd = Window();
	
	Render render = Render();

	bool m_Close = false;

	short m_NumOfPlayers = 0;


	// Called Every Frame : Checks keyboard input
	void CheckInput(void);

	void GameLogic();
	void AILogic();

	void ColisionHandle(const Paddle& p);
	bool CheckYColison(const Paddle& p);
	bool CheckXColison(const Paddle& p);
	void CheckColison();
public:

	int Init();

	void PlayerSelect();

	// Called every frame
	int ShouldClose();
	void Run();

	Game();

};

#endif /* GAME_H */
