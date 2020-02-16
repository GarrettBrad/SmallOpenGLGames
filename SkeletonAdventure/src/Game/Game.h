#ifndef GAME_H
#define GAME_H

#include "Skeleton.h"

// Singleton
class Game
{
private:

	bool m_ShouldClose = false;

	// The Player
	Skeleton m_Skeleton = Skeleton();

	LRESULT CALLBACK WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	int InitInter(HINSTANCE);
	int GetExitCodeInter();
	bool ShouldCloseInter();
	void RunInter();

public:

	static LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	static int Init(HINSTANCE);
	static bool ShouldClose();
	static void Run();
	static int GetExitCode();
	static Game& Get();


	Game();
};

#endif /* GAME_H */
