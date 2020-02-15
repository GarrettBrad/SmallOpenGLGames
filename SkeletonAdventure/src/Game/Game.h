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

	int InitInter();
	bool ShouldCloseInter();
	void RunInter();

public:
	static void KeyCallBack(GLFWwindow* wnd, int key, int scanecode, int action, int mods);

	static int Init();
	static bool ShouldClose();
	static void Run();
	static Game& Get();

};

#endif /* GAME_H */
