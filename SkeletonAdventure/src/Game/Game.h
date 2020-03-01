#ifndef GAME_H
#define GAME_H

#include "Game/Logic/Logic.h"

// Singleton
class Game
{
private:

	bool m_ShouldClose = false;

	LRESULT CALLBACK WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int InitInter(HINSTANCE);
	
	bool ShouldCloseInter();
	void RunInter();
	void DrawInter();

	int GetExitCodeInter();

	Game();

public:

	static LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	static int Init(HINSTANCE);
	
	static bool ShouldClose();
	static void Run();
	static void Draw();

	static int GetExitCode();
	
	Game(const Game& game) = delete;

	static Game& Get();
};

#endif /* GAME_H */
