#ifndef GAME_H
#define GAME_H

#include "Skeleton.h"

// Singleton
class Game
{
private:
	// Key Presses

	std::unordered_map<int, bool> m_KeyPressed;
	bool m_KeySpace = false;
private:

	int m_MouseX = 0; 
	int m_MouseY = 0;
	bool m_MouseDown = false;
	bool m_ShouldClose = false;

	// The Player
	Skeleton m_Skeleton = Skeleton();
	D2D1_SIZE_F m_CurrentSkelSize = D2D1_SIZE_F();

	LRESULT CALLBACK WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void KeyPressed(WPARAM, LPARAM);
	void KeyReleased(WPARAM, LPARAM);

	void CheckInput();
	void MoveSkeleton(Direction dir);
	void CheckBoarders();

	int InitInter(HINSTANCE);
	
	bool ShouldCloseInter();
	void RunInter();
	void DrawInter();

	void SetCanJumpInter();

	int GetExitCodeInter();

public:

	static LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	static int Init(HINSTANCE);
	
	static bool ShouldClose();
	static void Run();
	static void Draw();
	
	static void SetCanJump();

	static int GetExitCode();
	static Game& Get();


	Game();
};

#endif /* GAME_H */
