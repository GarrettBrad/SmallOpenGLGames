#ifndef GAME_H
#define GAME_H

#include "Entity/Skeleton.h"

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
	D2D1_SIZE_F m_SkelSize = D2D1_SIZE_F();

	LRESULT CALLBACK WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void CheckInput();
	void MoveSkeleton(Direction dir);
	void CheckObjectColison();


	int InitInter(HINSTANCE);
	
	bool ShouldCloseInter();
	void RunInter();
	void DrawInter();

	void SetCanJumpInter();

	int GetExitCodeInter();

	Game();

public:

	static LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma);

	static int Init(HINSTANCE);
	
	static bool ShouldClose();
	static void Run();
	static void Draw();
	
	static void SetCanJump();

	static int GetExitCode();
	static Game& Get();
};

#endif /* GAME_H */
