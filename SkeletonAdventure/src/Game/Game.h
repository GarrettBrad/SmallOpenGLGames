#ifndef GAME_H
#define GAME_H

#include "Skeleton.h"

// Singleton
class Game
{
private:

	int m_MouseX = 0; 
	int m_MouseY = 0;
	bool m_MouseDown = false;

	bool m_ShouldClose = false;


	// The Player
	Skeleton m_Skeleton = Skeleton();

	LRESULT CALLBACK WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void KeyPressed(WPARAM, LPARAM);
	void KeyReleased(WPARAM, LPARAM);

	int InitInter(HINSTANCE);
	
	bool ShouldCloseInter();
	void RunInter();
	void DrawInter();

	int GetExitCodeInter();

public:

	static LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	static int Init(HINSTANCE);
	
	static bool ShouldClose();
	static void Run();
	static void Draw();
	
	static int GetExitCode();
	static Game& Get();


	Game();
};

#endif /* GAME_H */
